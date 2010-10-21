#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

#include "SWPM_GUI/compressing/SWPM.h"

int main(int argc, char** argv) {
	int Rp = 0;
	int Np = 0;
	int Rs = 0;
	int Ns = 0;
	int P = 0;
	int p = 0;
	unsigned short BPS = 0;

	char* action;

	char* wav_name;
	char* compressed_name;
	char* matrix_a_path;

	if (argc == 2 && strcmp(argv[1], "-help") == 0) {
		printf("Using: ");
		printf("basic.exe command \n\t\t-wav path_to_wav_file \n\t\t-compressed path_to_cwf_file \n\t\t-mtr path_to_matrix_AA_files\n");
		printf("\t\t[-Rp number] \n\t\t[-Np number] \n\t\t[-P number] \n\t\t[-p number] \n\t\t[-BPS number]\n\n");
		printf("\t> command - Now supported only -c (compress), -d (decompress)\n");
		printf("\t> -Rp number - Count of pause frequency bands\n");
		printf("\t> -Np number - The size of the pause frame\n");
		printf("\t> -Rs number - Count of signal frequency bands\n");
		printf("\t> -Ns number - The size of the signal frame\n");
		printf("\t> -P number - The number of samples from the beginning of the file, which are considered a pause\n");
		printf("\t> -p number - The number of samples from the beginning of the file to start of pause\n");
		printf("\t> -BPS number - Bits per sample in compressed file\n");
		return 0;
	}

	if (argc < 6) {
		printf("Command line arguments error. Use '-help'\n");
		return 0;
	}
	else {
		action = argv[1];
		for (int i = 2; i < argc; i+=2) {
			if (strcmp(argv[i], "-wav") == 0)
				wav_name = argv[i+1];
			else if (strcmp(argv[i], "-compressed") == 0)
				compressed_name = argv[i+1];
			else if (strcmp(argv[i], "-mtr") == 0)
				matrix_a_path = argv[i+1];
			else if (strcmp(argv[i], "-Np") == 0)
				Np = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-Rp") == 0)
				Rp = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-Ns") == 0)
				Ns = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-Rs") == 0)
				Rs = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-P") == 0)
				P = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-p") == 0)
				p = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-BPS") == 0)
				BPS = atoi(argv[i+1]);
		}
	}

	SWPM* swpm = new SWPM;
	swpm->SetCompressParams(Np, Rp, P, p, Ns, Rs, BPS);
	swpm->matrixDir = matrix_a_path;

	if (strcmp(action, "-c") == 0) {
		swpm->LoadSignalFile(wav_name);
		swpm->FullCompressData();
		swpm->SaveCompressedFile(compressed_name);
	} else if (strcmp(action, "-d") == 0) {
		swpm->LoadCompressedFile(compressed_name);
		swpm->FullDecompressData();
		swpm->SaveSignalData(wav_name);
	}

	delete swpm;

	return 0;
}