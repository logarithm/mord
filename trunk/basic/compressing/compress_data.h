#ifndef COMPRESS_DATA_H
#define COMPRESS_DATA_H

#ifndef byte
#define byte unsigned char
#endif

#include <cstring>

struct Frame {
	unsigned short* maxs;
	byte* quant_values;
	int R;
	int N;
	int J;

	Frame(int R, int N, unsigned short* maxs, byte* quant_values) {
		this->R = R;
		this->N = N;
		J = 2*(N/(2*R)) + 2;
		this->maxs = new unsigned short[R];
		this->quant_values = new byte[R*J];
		memcpy(this->maxs, maxs, sizeof(unsigned short) * R);
		memcpy(this->quant_values, quant_values, sizeof(byte) * R * J);
	}

	~Frame() {
		delete maxs;
		delete quant_values;
	}

	void write(FILE* file) {
	}
};

void save_compress_file(char* compress_path, unsigned int source_length, byte source_bps,
						byte Rp, byte Np, byte Rs, byte Ns, unsigned short bps, 
						int pause_segmen_count, unsigned short* pause_map, 
						int frame_count, Frame* frames) {
	FILE* out = fopen(compress_path, "wb");

	fwrite((int) 0, sizeof(int), 1, out);
	fwrite(source_length, sizeof(unsigned int), 1, out);
	fwrite(source_bps, sizeof(byte), 1, out);
	fwrite(Rp, sizeof(byte), 1, out);
	fwrite(Np, sizeof(byte), 1, out);
	fwrite(Rs, sizeof(byte), 1, out);
	fwrite(Ns, sizeof(byte), 1, out);
	fwrite(bps, sizeof(unsigned short), 1, out);
	
	fwrite(pause_segmen_count, sizeof(int), 1, out);
	fwrite(pause_map, sizeof(unsigned short), pause_segmen_count*2, out);

	for (int i = 0; i < frame_count; i++) {
		frames[i].write(out);
	}

	fclose(out);
}

#endif