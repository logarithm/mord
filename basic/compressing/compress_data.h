#ifndef COMPRESS_DATA_H
#define COMPRESS_DATA_H

#ifndef byte
#define byte unsigned char
#endif

#include <cstring>

byte getBit(int data, int bitIndex) {
	return (byte) ((data >> bitIndex) & 0x01);
}

void setBit(int& data, int bitIndex) {
	data |= (0x1 << bitIndex);
}

void clearBit(int& data, int bitIndex) {
	data &= ~(0x1 << bitIndex);
}


struct Frame {
	float* maxs;
	unsigned short* quant_values;
	bool* sign;
	unsigned short bps;
	int R;
	int N;
	int J;

	Frame() {
		this->maxs = new float[0];
		this->quant_values = new unsigned short[0];
		this->sign = new bool[0];
	}

	Frame(int R, int N, unsigned short bps, float* maxs, unsigned short* quant_values, bool* sign) {
		this->R = R;
		this->N = N;
		J = 2*(N/(2*R)) + 2;
		this->bps = bps;
		this->maxs = new float[R];
		this->quant_values = new unsigned short[R*J];
		this->sign = new bool[R*J];
		memcpy(this->maxs, maxs, sizeof(float) * R);
		memcpy(this->quant_values, quant_values, sizeof(short) * R * J);
		memcpy(this->sign, sign, sizeof(bool) * R * J);
	}

	Frame(const Frame &frame)
	{
		this->R = frame.R;
		this->N = frame.N;
		J = 2*(N/(2*R)) + 2;
		this->bps = frame.bps;
		this->maxs = new float[R];
		this->quant_values = new unsigned short[R*J];
		this->sign = new bool[R*J];
		memcpy(this->maxs, frame.maxs, sizeof(float) * R);
		memcpy(this->quant_values, frame.quant_values, sizeof(short) * R * J);
		memcpy(this->sign, frame.sign, sizeof(bool) * R * J);
	}

	Frame& operator=(const Frame & frame)
	{
		if (this == &frame) return *this;

		delete this->maxs;
		delete this->quant_values;
		delete this->sign;

		this->R = frame.R;
		this->N = frame.N;
		this->J = 2*(this->N/(2*this->R)) + 2;
		this->bps = frame.bps;
		this->maxs = new float[this->R];
		this->quant_values = new unsigned short[this->R*this->J];
		this->sign = new bool[this->R*this->J];
		memcpy(this->maxs, frame.maxs, sizeof(float) * this->R);
		memcpy(this->quant_values, frame.quant_values, sizeof(short) * this->R * this->J);
		memcpy(this->sign, frame.sign, sizeof(bool) * this->R * this->J);

		return *this;
	}

	~Frame() {
		delete maxs;
		delete quant_values;
		delete sign;
	}
};

struct FrameContainer {
	unsigned frameCount;
	Frame* frames;

	FrameContainer(unsigned count) {
		this->frameCount = count;
		this->frames = new Frame[this->frameCount];
	}

	FrameContainer(Frame* frames, unsigned count) {
		this->frameCount = count;
		this->frames = new Frame[this->frameCount];
		memcpy(this->frames, frames, sizeof(Frame)*this->frameCount);
	}

	void write(FILE* file) {
		for(int frameIndex = 0; frameIndex < frameCount; frameIndex++) {
			for (int maxIndex = 0; maxIndex < frames[frameIndex].R; maxIndex++) {
				short data_val = (short)( frames[frameIndex].maxs[maxIndex] * 32768.0f );
				fwrite(&data_val, sizeof(short), 1, file);
			}
			int bytesCount = ceil((frames[frameIndex].R*frames[frameIndex].J*(frames[frameIndex].bps + 1))/8.0);
			byte* dest = new byte[bytesCount];
			memset(dest, 0, sizeof(byte)*bytesCount);
			int byteIndex = 0, bitIndex = 0;
			for (int quantIndex = 0; quantIndex < (frames[frameIndex].R*frames[frameIndex].J); quantIndex++) {
				for(int bpsIndex = 0; bpsIndex < frames[frameIndex].bps; bpsIndex++) {
					if (getBit(frames[frameIndex].quant_values[quantIndex], bpsIndex)) {
						setBit((int&) dest[byteIndex], bitIndex);
					}

					if (bitIndex + 1 > 7) byteIndex++;
					bitIndex = (++bitIndex) % 8;
				}
				//Запись знака
				if (frames[frameIndex].quant_values[quantIndex] != 0) {
					if (frames[frameIndex].sign[quantIndex]) {
						setBit((int&) dest[byteIndex], bitIndex);
					}
					if (bitIndex + 1 > 7) byteIndex++;
					bitIndex = (++bitIndex) % 8;
				}
			}

			fwrite(dest, sizeof(byte), byteIndex+1, file);
		};
	}

	void read(byte* data, unsigned dataSize, short R, short N, byte bps) {
		short J = 2*(N/(2*R)) + 2;

		unsigned short* quant_val = new unsigned short[R*J];
		float* maxs = new float[R];
		bool* sign = new bool[R*J];

		unsigned byteIndex = 0;
		int fc = 0;
		for (int frameIndex = 0; frameIndex < frameCount; frameIndex++) {
			memset(quant_val, 0, sizeof(short)*R*J);
			memset(maxs, 0, sizeof(float)*R);
			memset(sign, 0, sizeof(bool)*R*J);

			for (int maxIndex = 0; maxIndex < R; maxIndex++) {
				unsigned short data_val = (((short)data[byteIndex+1] & 0xFFFF) << 8) | ((short)data[byteIndex] & 0xFF);
				maxs[maxIndex] = (float)( (int)(data_val) ) / 32768.0f;
				byteIndex += 2;
			}

			byte bitIndex = 0;
			for (int quantIndex = 0; quantIndex < R*J; quantIndex++) {
				unsigned short val = 0;
				for(int bpsIndex = 0; bpsIndex < bps; bpsIndex++) {
					if (getBit(data[byteIndex], bitIndex) > 0) {
						setBit((int&) val, bpsIndex);
					}

					if (bitIndex + 1 > 7) byteIndex++;
					bitIndex = (++bitIndex) % 8;
				}
				quant_val[quantIndex] = val;
				//Считывание знака
				if (val != 0) {
					sign[quantIndex] = getBit(data[byteIndex], bitIndex) ? true : false;

					if (bitIndex + 1 > 7) byteIndex++;
					bitIndex = (++bitIndex) % 8;
				}
			}

			frames[frameIndex] = Frame(R, N, bps, maxs, quant_val, sign);
			fc++;

			byteIndex++;
			if ((byteIndex + 1) >= dataSize) break;
		}

		this->frameCount = fc;
	}
};

void saveCompressFile(char* compressPath, unsigned int sourceLength, byte sourceBps,
						short Rp, short Np, short Rs, short Ns, byte bps, 
						int pauseSegmentCount, unsigned short* pauseMap, 
						FrameContainer frames) {
	FILE* out = fopen(compressPath, "wb");

	fwrite("KNIT", sizeof(int), 1, out);
	fwrite(&sourceLength, sizeof(int), 1, out);
	fwrite(&sourceBps, sizeof(byte), 1, out);
	fwrite(&Rp, sizeof(short), 1, out);
	fwrite(&Np, sizeof(short), 1, out);
	fwrite(&Rs, sizeof(short), 1, out);
	fwrite(&Ns, sizeof(short), 1, out);
	fwrite(&bps, sizeof(byte), 1, out);
	
	fwrite(&pauseSegmentCount, sizeof(int), 1, out);
	fwrite(pauseMap, sizeof(short), pauseSegmentCount*2, out);

	frames.write(out);

	fclose(out);
}

void readCompressFile(char* compressPath) {
	FILE* in = fopen(compressPath, "rb");

	fseek(in, SEEK_SET, SEEK_END);
	long fsize = ftell(in);
	fseek(in, SEEK_SET, 0);

	unsigned knit;
	fread(&knit, sizeof(int), 1, in);
	unsigned sourceLegth;
	fread(&sourceLegth, sizeof(int), 1, in);
	byte sourceBps;
	fread(&sourceBps, sizeof(byte), 1, in);
	short Rp;
	fread(&Rp, sizeof(short), 1, in);
	short Np;
	fread(&Np, sizeof(short), 1, in);
	short Rs;
	fread(&Rs, sizeof(short), 1, in);
	short Ns;
	fread(&Ns, sizeof(short), 1, in);
	byte bps;
	fread(&bps, sizeof(byte), 1, in);

	int pauseSegmentCount;
	fread(&pauseSegmentCount, sizeof(int), 1, in);
	unsigned short* pauseMap = new unsigned short[pauseSegmentCount*2];
	fread(pauseMap, sizeof(short), pauseSegmentCount*2, in);

	long withoutDataSize = sizeof(int)*3 + sizeof(short)*4 + sizeof(byte)*2 + (pauseSegmentCount*2*sizeof(short));
	long dataSize = fsize - withoutDataSize;

	byte* data = new byte[dataSize];
	fread(data, sizeof(byte), dataSize, in);

	int Js = 2*(Ns/(2*Rs)) + 2;
	unsigned minFrameSize = Rs*sizeof(short) + ceil((bps)*(Rs*Js) / 8.0);
	unsigned maxFrameCount = ceil(dataSize/(float) minFrameSize);

	FrameContainer frames(maxFrameCount);
	frames.read(data, dataSize, Rs, Ns, bps);

	fclose(in);
}

#endif