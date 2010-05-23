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
	swpm->SetCompressParams(60, 10, 5, 0, 128, 20, 3);
	swpm->matrixDir = "d:/svn/trunk/basic/files/matrix/";

	swpm->LoadSignalFile("d:/svn/trunk/basic/files/wav/lec02_03_8000.wav");
	//swpm->LoadSignalFile("d:/svn/trunk/basic/files/wav/source.wav");
	swpm->FullCompressData();
	swpm->SaveCompressedFile("d:/svn/trunk/basic/files/wav/destination.cwf");

	swpm->LoadCompressedFile("d:/svn/trunk/basic/files/wav/destination.cwf");
	swpm->FullDecompressData();
	swpm->SaveSignalData("d:/svn/trunk/basic/files/wav/destination.wav");

	delete swpm;

	return 0;
}
