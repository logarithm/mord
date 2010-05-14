#include <stdio.h>
#include <stdlib.h>
#include <cstring>

//#undef STRICT
//#define WIN32_LEAN_AND_MEAN     1
//#include <windows.h>

#include <cmath>
using namespace std;

#include "compressing/SWPM.h"

int main(int argc, char** argv) {
	SWPM* swpm = new SWPM;
	swpm->SetCompressParams(60, 10, 5, 0, 60, 10, 7);
	swpm->matrixDir = "files/matrix/";


	swpm->LoadSignalFile("files/wav/lec02_03_8000.wav");
	//swpm->LoadSignalFile("files/wav/source.wav");
	swpm->DeletePause();
	swpm->CompressData();
	swpm->SaveCompressedFile("files/wav/destination.cwf");

	swpm->LoadCompressedFile("files/wav/destination.cwf");
	swpm->DecompressData();
	swpm->RecoveryPause();
	swpm->SaveSignalData("files/wav/destination.wav", 8000, 16);

	delete swpm;

	return 0;
}
