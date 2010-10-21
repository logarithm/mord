#ifndef FRAME_H
#define FRAME_H

#include <cstring>
using namespace std;

#include "types.h"
#include "utils.h"

struct Frame {
	float* maxs;
	USHORT* quantValues;
	bool* sign;
	BYTE bps;
	int R;
	int N;
	int J;

	Frame() {
		this->maxs = new float[0];
		this->quantValues = new unsigned short[0];
		this->sign = new bool[0];
	}

	Frame(int R, int N, BYTE bps, float* maxs, unsigned short* quantValues, bool* sign) {
		this->R = R;
		this->N = N;
		J = 2*(N/(2*R)) + 2;
		this->bps = bps;
		this->maxs = new float[R];
		this->quantValues = new USHORT[R*J];
		this->sign = new bool[R*J];
		memcpy(this->maxs, maxs, sizeof(float) * R);
		memcpy(this->quantValues, quantValues, sizeof(USHORT) * R * J);
		memcpy(this->sign, sign, sizeof(bool) * R * J);
	}

	Frame(const Frame &frame)
	{
		this->R = frame.R;
		this->N = frame.N;
		J = 2*(N/(2*R)) + 2;
		this->bps = frame.bps;
		this->maxs = new float[R];
		this->quantValues = new USHORT[R*J];
		this->sign = new bool[R*J];
		memcpy(this->maxs, frame.maxs, sizeof(float) * R);
		memcpy(this->quantValues, frame.quantValues, sizeof(USHORT) * R * J);
		memcpy(this->sign, frame.sign, sizeof(bool) * R * J);
	}

	Frame& operator=(const Frame & frame)
	{
		if (this == &frame) return *this;

		delete this->maxs;
		delete this->quantValues;
		delete this->sign;

		this->R = frame.R;
		this->N = frame.N;
		this->J = 2*(this->N/(2*this->R)) + 2;
		this->bps = frame.bps;
		this->maxs = new float[this->R];
        this->quantValues = new unsigned short[this->R*this->J];
		this->sign = new bool[this->R*this->J];
		memcpy(this->maxs, frame.maxs, sizeof(float) * this->R);
        memcpy(this->quantValues, frame.quantValues, sizeof(short) * this->R * this->J);
		memcpy(this->sign, frame.sign, sizeof(bool) * this->R * this->J);

		return *this;
	}

	~Frame() {
		delete [] maxs;
        delete [] quantValues;
		delete [] sign;
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

	int WriteData(BYTE* buffer) {
		if (frameCount < 1) return 0;

		USHORT R = frames[0].R;
		USHORT J = frames[0].J;
		USHORT bps = frames[0].bps;

		UINT maxFrameDataSize = ceil((R*J*(bps + 1))/8.0);
		UINT maxFrameSize = sizeof(short)*R + maxFrameDataSize;

		BYTE* _tmp_buffer = new BYTE[maxFrameSize*(frameCount)];
		memset(_tmp_buffer, 0, sizeof(BYTE)*maxFrameSize*frameCount);
		UINT _tmp_buffer_pointer = 0;

		BYTE* dest = new BYTE[maxFrameDataSize];

		for(int frameIndex = 0; frameIndex < frameCount; frameIndex++) {
			for (USHORT maxIndex = 0; maxIndex < R; maxIndex++) {
				short dataVal = (short)( frames[frameIndex].maxs[maxIndex] * 32768.0f );
				_tmp_buffer[_tmp_buffer_pointer++] = (BYTE)(dataVal & 0xFF);
				_tmp_buffer[_tmp_buffer_pointer++] = (BYTE)((dataVal >> 8) & 0xFF);
			}

			memset(dest, 0, sizeof(BYTE)*maxFrameDataSize);
			int byteIndex = 0, bitIndex = 0;
			for (USHORT quantIndex = 0; quantIndex < (R*J); quantIndex++) {
				for(USHORT bpsIndex = 0; bpsIndex < bps; bpsIndex++) {
					if (Utils::getBit(frames[frameIndex].quantValues[quantIndex], bpsIndex)) {
						Utils::setBit((int&) dest[byteIndex], bitIndex);
					}

					if (bpsIndex + 1 < bps) {
						if (bitIndex + 1 > 7) 
							byteIndex++;
						bitIndex = (++bitIndex) % 8;
					}
				}
				//Запись знака
				if (frames[frameIndex].quantValues[quantIndex] != 0) {
					if (bitIndex + 1 > 7) byteIndex++;
					bitIndex = (++bitIndex) % 8;

					if (frames[frameIndex].sign[quantIndex]) {
						Utils::setBit((int&) dest[byteIndex], bitIndex);
					}

					if (quantIndex + 1 < (R*J)) {
						if (bitIndex + 1 > 7) 
							byteIndex++;
						bitIndex = (++bitIndex) % 8;
					}
				} else if (quantIndex + 1 < (R*J)) {
					if (bitIndex + 1 > 7) 
							byteIndex++;
						bitIndex = (++bitIndex) % 8;
				}
			}

			memcpy(_tmp_buffer + _tmp_buffer_pointer, dest, sizeof(BYTE)*(byteIndex+1));
			_tmp_buffer_pointer += (byteIndex+1);
		};

		memcpy(buffer, _tmp_buffer, sizeof(BYTE)*_tmp_buffer_pointer);

		delete [] dest;
		delete [] _tmp_buffer;

		return _tmp_buffer_pointer;
	}

	void ReadData(BYTE* data, UINT dataSize, USHORT R, USHORT N, BYTE bps) {
		short J = 2*(N/(2*R)) + 2;

		USHORT* quantVal = new USHORT[R*J];
		float* maxs = new float[R];
		bool* sign = new bool[R*J];

		unsigned byteIndex = 0;
		int fc = 0;
		for (int frameIndex = 0; frameIndex < frameCount; frameIndex++) {
			memset(quantVal, 0, sizeof(short)*R*J);
			memset(maxs, 0, sizeof(float)*R);
			memset(sign, 0, sizeof(bool)*R*J);

			for (int maxIndex = 0; maxIndex < R; maxIndex++) {
				unsigned short dataVal = (((short)data[byteIndex+1] & 0xFFFF) << 8) | ((short)data[byteIndex] & 0xFF);
				maxs[maxIndex] = (float)( (int)(dataVal) ) / 32768.0f;
				byteIndex += 2;
			}

			BYTE bitIndex = 0;
			for (int quantIndex = 0; quantIndex < R*J; quantIndex++) {
				USHORT val = 0;
				for(int bpsIndex = 0; bpsIndex < bps; bpsIndex++) {
					if (Utils::getBit(data[byteIndex], bitIndex) > 0) {
						Utils::setBit((int&) val, bpsIndex);
					}

					if (bpsIndex + 1 < bps) {
						if (bitIndex + 1 > 7) 
							byteIndex++;
						bitIndex = (++bitIndex) % 8;
					}
				}
				//Считывание знака
				if (val != 0) {
					if (bitIndex + 1 > 7) byteIndex++;
					bitIndex = (++bitIndex) % 8;

					sign[quantIndex] = Utils::getBit(data[byteIndex], bitIndex) ? true : false;

					if (quantIndex + 1 < (R*J)) {
						if (bitIndex + 1 > 7) 
							byteIndex++;
						bitIndex = (++bitIndex) % 8;
					}
				} else if (quantIndex + 1 < (R*J)) {
					if (bitIndex + 1 > 7) 
							byteIndex++;
						bitIndex = (++bitIndex) % 8;
				}
				quantVal[quantIndex] = val;
			}

			frames[frameIndex] = Frame(R, N, bps, maxs, quantVal, sign);
			fc++;

			byteIndex++;
			if ((byteIndex + 1) >= dataSize) break;
		}

		this->frameCount = fc;
	}

	~FrameContainer() {
		delete [] frames;
	}
};

#endif //FRAME_H
