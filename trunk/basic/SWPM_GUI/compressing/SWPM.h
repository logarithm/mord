#ifndef SWPM_H
#define SWPM_H

/**
 * SWPM (Supband wav processing method).
 * This method develop on the faculty of Computer Sciense and Telecommunication in Belgorod State University
 *
 * @author Logvinenko Maksim (mlogvinenko@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
using namespace std;

#include "types.h"
#include "file.h"
#include "wavesound.h"
#include "matrixprocessing.h"
#include "frame.h"

class SWPM {
private:
	static const USHORT HEAD_SIZE = sizeof(UINT)*3 + sizeof(USHORT)*5 + sizeof(BYTE)*2;
	static const USHORT PAUSE_BOUNDARY = 20;

    float* signal;
	ULONG signalLength;
	BYTE signalBps;
	USHORT signalRate;

    float* signalWithoutPause;
    ULONG signalWithoutPauseLength;

	BYTE* compressedData;
	ULONG compressedDataLength;
	BYTE compressedBps;

	UINT pauseSegmentCount;
	USHORT* pauseMap;

	USHORT Np;
	USHORT Rp;
	USHORT Jp;
	USHORT P;
	USHORT p;

	USHORT Ns;
	USHORT Rs;
	USHORT Js;

	//Private methods

	void _ClearAll() {
		Np	= 0;
		Rp	= 0;
		Jp	= 0;
		P	= 10;
		p	= 0;

		Ns	= 0;
		Rs	= 0;
		Js	= 0;		

		compressedBps				= 0;
		_ClearPointers();
	}

	void _ClearPointers() {
		signalLength				= 0;
		signalBps					= 0;
		signalRate					= 0;
		signalWithoutPauseLength	= 0;
		compressedDataLength		= 0;
		pauseSegmentCount			= 0;

		if (signal != NULL)				{ delete [] signal; signal = NULL; }
		if (signalWithoutPause != NULL)	{ delete [] signalWithoutPause; signalWithoutPause = NULL; }
		if (compressedData != NULL)		{ delete [] compressedData; compressedData = NULL; }
		if (pauseMap != NULL)			{ delete [] pauseMap; pauseMap = NULL; }
	}

	void _Copy(const SWPM &_swpm) {
		signalLength				= _swpm.signalLength;
		signalBps					= _swpm.signalBps;
		signalRate					= _swpm.signalRate;
		signalWithoutPauseLength	= _swpm.signalWithoutPauseLength;
		compressedDataLength		= _swpm.compressedDataLength;
		compressedBps				= _swpm.compressedBps;
		pauseSegmentCount			= _swpm.pauseSegmentCount;

		Np	= _swpm.Np;
		Rp	= _swpm.Rp;
		Jp	= _swpm.Jp;
		P	= _swpm.P;
		p	= _swpm.p;

		Ns	= _swpm.Ns;
		Rs	= _swpm.Rs;
		Js	= _swpm.Js;

		if (_swpm.signal != NULL) {
			signal = new float[signalLength];
			memcpy(signal, _swpm.signal, sizeof(float)*signalLength);
		} else signal = NULL;

		if (_swpm.signalWithoutPause != NULL) {
			signalWithoutPause = new float[signalWithoutPauseLength];
			memcpy(signalWithoutPause, _swpm.signalWithoutPause, sizeof(float)*signalWithoutPauseLength);
		} else signalWithoutPause = NULL;

		if (_swpm.compressedData != NULL) {
			compressedData = new BYTE[compressedDataLength];
			memcpy(compressedData, _swpm.compressedData, sizeof(BYTE)*compressedDataLength);
		} else compressedData = NULL;

		if (_swpm.pauseMap != NULL) {
			pauseMap = new USHORT[pauseSegmentCount];
			memcpy(pauseMap, _swpm.pauseMap, sizeof(USHORT)*pauseSegmentCount);
		} else pauseMap = NULL;
	}

	void _SetSignal(float* _signal, ULONG _signalLength) {
		if (signal != NULL) delete [] signal;

		signalLength = _signalLength;
		signal = new float[signalLength];
		memcpy(signal, _signal, sizeof(float)*signalLength);
	}

	void _SetSignalWithoutPause(float* _signalWithoutPause, ULONG _signalWithoutPauseLength) {
		if (signalWithoutPause != NULL) delete [] signalWithoutPause;

		signalWithoutPauseLength = _signalWithoutPauseLength;
		signalWithoutPause = new float[signalWithoutPauseLength];
		memcpy(signalWithoutPause, _signalWithoutPause, sizeof(float)*signalWithoutPauseLength);
	}

	void _SetCompressedData(BYTE* _compressedData, ULONG _compressedDataLength) {
		if (compressedData!= NULL) delete [] compressedData;

		compressedDataLength = _compressedDataLength;
		compressedData = new BYTE[compressedDataLength];
		memcpy(compressedData, _compressedData, sizeof(BYTE)*compressedDataLength);
	}

	void _LoadMatrix(float** matrix, USHORT N, USHORT R) {
		char matrixPath[1000];
		strcpy(matrixPath, matrixDir);
		strcat(matrixPath, "/AA_");
		char cR[10]; sprintf(cR, "%d", R);
		strcat(matrixPath,cR);
		strcat(matrixPath, "_");
		char cN[10]; sprintf(cN, "%d", N);
		strcat(matrixPath, cN);
		strcat(matrixPath, ".mtr");

		USHORT J = 2*(N/(2*R)) + 2;
		MatrixProcessing::matrix_read(matrixPath, R*J, N, matrix);
	}

public:
	char * matrixDir;

	SWPM() {
		signal				= NULL;
		signalWithoutPause	= NULL;
		compressedData		= NULL;
		pauseMap			= NULL;

		_ClearAll();
    }
	SWPM(const SWPM &_swpm) { _Copy(_swpm); }
	SWPM& operator=(const SWPM &_swpm) {
		if (this == &_swpm) return *this;

		_ClearAll();
		_Copy(_swpm);

		return *this;
	}

    ~SWPM() {
		_ClearAll();
	}

	/**
	 * @param _Np The size of the pause frame
	 * @param _Rp Count of pause frequency bands
	 * @param _P The number of samples from the beginning of the file, which are considered a pause
	 * @param _p The number of samples from the beginning of the file to start of pause
	 * @param _Ns The size of the signal frame
	 * @param _Rs Count of signal frequency bands
	 */
	void SetCompressParams(USHORT _Np, USHORT _Rp, USHORT _P, USHORT _p, USHORT _Ns, USHORT _Rs, BYTE _compressedBps) {
		SetPauseParams(_Np, _Rp, _P, _p);
		SetSignalParams(_Ns, _Rs, _compressedBps);
	}

	/**
	 * @param _Np The size of the pause frame
	 * @param _Rp Count of pause frequency bands
	 * @param _P The number of samples from the beginning of the file, which are considered a pause
	 * @param _p The number of samples from the beginning of the file to start of pause
	 */
	void SetPauseParams(USHORT _Np, USHORT _Rp, USHORT _P, USHORT _p) {
		Np = _Np;
		Rp = _Rp;
		Jp = 2*(Np/(2*Rp)) + 2;

		P = _P;
		p = _p;
	}

	/**
	 * @param _Ns The size of the signal frame
	 * @param _Rs Count of signal frequency bands
	 */
	void SetSignalParams(USHORT _Ns, USHORT _Rs, BYTE _compressedBps) {
		Ns = _Ns;
		Rs = _Rs;
		Js = 2*(Ns/(2*Rs)) + 2;

		compressedBps = _compressedBps;
	}

	/**
	 * Copy signal into user buffer
	 * @param _signalDst User buffer
	 */
	void GetSignal(float* _signalDst)							{ memcpy(_signalDst, signal, sizeof(float)*GetSignalLenght()); }
	ULONG GetSignalLenght()										{ return signalLength;			}

	/**
	 * Copy signal without pauses into user buffer
	 * @param _signalDst User buffer
	 */
	void GetSignalWithoutPause(float* _signalWithoutPauseDst)	{ memcpy(_signalWithoutPauseDst, signalWithoutPause, sizeof(float)*GetSignalWithoutPauseLenght()); }
	ULONG GetSignalWithoutPauseLenght()							{ return signalWithoutPauseLength;	}

	/**
	 * Copy compressed data into user buffer
	 * @param _signalDst User buffer
	 */
	void GetCompressedData(float* _compressedDataDst)			{ memcpy(_compressedDataDst, compressedData, sizeof(float)*GetCompressedDataLenght()); }
	ULONG GetCompressedDataLenght()								{ return compressedDataLength;	}

	BYTE GetSignalBps()		{ return signalBps; }
	USHORT GetSignalRate()	{ return signalRate; }

	BYTE GetCompressedBps() { return compressedBps; }
	USHORT GetNp() { return Np; }
	USHORT GetRp() { return Rp; }
	USHORT GetNs() { return Ns; }
	USHORT GetRs() { return Rs; }

	void LoadSignalFile(char *fileName) {
		_ClearPointers();

		WaveSound* signalFile = new WaveSound();
		signalFile->Load(fileName);

		signalLength = signalFile->getAvialible();
		signalBps = signalFile->getBPS();
		signalRate = signalFile->getRate();

		signal = new float[signalLength];
		signalFile->ReadFlt(signal, signalLength);

		signalFile->Unload();
		delete signalFile;
	}

	void SaveSignalData(char* fileName) {
		WaveSound* signalFile = new WaveSound();

		signalFile->Create(fileName, signal, signalLength, 1, signalRate, signalBps);

		signalFile->Unload();
		delete signalFile;
	}

	void SaveSignalWithoutPauseData(char* fileName) {
		WaveSound* signalFile = new WaveSound();

		signalFile->Create(fileName, signalWithoutPause, signalWithoutPauseLength, 1, signalRate, signalBps);

		signalFile->Unload();
		delete signalFile;
	}

	void LoadCompressedFile(char *fileName) {
		_ClearPointers();

		MFile* compressedFile = mOpenFile(fileName, "rb");

		compressedFile->Seek(SEEK_SET, SEEK_END);
		ULONG fileSize = compressedFile->Tell();
		compressedFile->Seek(SEEK_SET, 0);

		UINT head;
		compressedFile->Read(&head);

		compressedFile->Read(&signalLength, sizeof(UINT));
		compressedFile->Read(&signalRate);
		compressedFile->Read(&signalBps);

		compressedFile->Read(&Rp);
		compressedFile->Read(&Np);

		compressedFile->Read(&Rs);
		compressedFile->Read(&Ns);

		compressedFile->Read(&compressedBps);

		SetCompressParams(Np, Rp, P, p, Ns, Rs, compressedBps);

		compressedFile->Read(&pauseSegmentCount);
		pauseMap = new USHORT[pauseSegmentCount*2];
		if (pauseSegmentCount > 0) compressedFile->Read(pauseMap, sizeof(USHORT) * pauseSegmentCount * 2);

		compressedDataLength = fileSize - (HEAD_SIZE + (sizeof(USHORT) * pauseSegmentCount * 2));

		compressedData = new BYTE[compressedDataLength];
		compressedFile->Read(compressedData, compressedDataLength);

		compressedFile->Close();
	}

	void SaveCompressedFile(char* fileName) {
		MFile* compressedFile = mOpenFile(fileName, "wb");

		UINT swpm = (UINT)"SWPM";
		compressedFile->Write(&swpm, sizeof(UINT));
		compressedFile->Write(&signalLength, sizeof(UINT));
		compressedFile->Write(&signalRate);
		compressedFile->Write(&signalBps);
		compressedFile->Write(&Rp);
		compressedFile->Write(&Np);
		compressedFile->Write(&Rs);
		compressedFile->Write(&Ns);
		compressedFile->Write(&compressedBps);

		compressedFile->Write(&pauseSegmentCount);
		if (pauseSegmentCount > 0) compressedFile->Write(pauseMap, sizeof(USHORT)*pauseSegmentCount*2);

		compressedFile->Write(compressedData, sizeof(BYTE)*compressedDataLength);

		compressedFile->Close();
	}

	void DeletePause() {
		if (signal == NULL) return;

		float** AAp = new float*[Rp*Jp];
		for (USHORT i = 0; i < Rp*Jp; i++)
			AAp[i] = new float[Np];

		_LoadMatrix(AAp, Np, Rp);

		//===================== Pause Energy ======================= //
		float* pausePower = new float[Rp];
		memset(pausePower, 0, sizeof(float) * Rp);

		for (USHORT currPauseArea = 0; currPauseArea < P; currPauseArea++) {
			float* pauseData = new float[Np];
			memcpy(pauseData, signal + p + currPauseArea*Np, sizeof(float)*Np);

			float pauseMean = MatrixProcessing::matrix_mean(&pauseData, 1, 60);

			for (UINT i = 0; i < Np; i++)
					pauseData[i] = pauseData[i] - pauseMean;

			float* pauseYY = new float[Rp*Jp];
			MatrixProcessing::matrix_mult_trans(&pauseData, AAp, 1, 60, 80, &pauseYY);

			for (UINT i = 0; i < Rp; i++) {
				for (UINT j = 0; j < Jp; j++) {
					pausePower[i] += pow(pauseYY[i*Jp + j], 2);
				}
			}

			delete [] pauseData;
			delete [] pauseYY;
		}

		for (USHORT i = 0; i < Rp; i++)
			pausePower[i] /= (float)P;

		//===================== Pause Energy END ======================= //

		UINT areaCount = (int)ceil(signalLength / (float)Np);

		UINT signalAreaCount = 0;
		UINT resultLength = 0;
		UINT pauseAreaCount = 0;
		UINT _pauseSegmentCount = 0;

		float* resultData = new float[signalLength];			//signal without pause

		unsigned short* _pauseMap = new unsigned short[(int) (ceil(areaCount/2.0) * 2)];
		bool lastPause = false;
		UINT pauseSectionLength = 0;
		UINT signalSectionLength = 0;

		//===================== Pause finding ======================= //
		for (UINT currArea = 0; currArea < areaCount; currArea++) {
			int areaLength = (currArea + 1)*Np > signalLength ? signalLength - (currArea)*Np : Np;

			float* areaData = new float[areaLength];			//sample
			memcpy(areaData, signal+(currArea*Np), sizeof(float)*areaLength);

			float areaMean = MatrixProcessing::matrix_mean(&areaData, 1, areaLength);

			for (UINT i = 0; i < areaLength; i++)
				areaData[i] = areaData[i] - areaMean;

			//signal power calculation
			float* areaPower = new float[Rp];
			memset(areaPower, 0, sizeof(float) * Rp);

			float* areaYY = new float[Rp*Jp];
			MatrixProcessing::matrix_mult_trans(&areaData, AAp, 1, areaLength, Rp*Jp, &areaYY);

			for (USHORT i = 0; i < Rp; i++) {
				for (USHORT j = 0; j < Jp; j++) {
					areaPower[i] += pow(areaYY[i*Jp + j], 2);
				}
			}

			float decisionFunction;
			for (USHORT i = 0; i < Rp; i++) {
				areaPower[i] /= (float) pausePower[i];
				decisionFunction = (i == 0 || areaPower[i] > decisionFunction) ? areaPower[i] : decisionFunction;
			}

			if (decisionFunction > PAUSE_BOUNDARY) {		//Signal
				signalAreaCount++;

				memcpy(resultData + resultLength, areaData, sizeof(float)*areaLength); //Copy data to destination buffer
				resultLength += areaLength;

				if (lastPause) {
					_pauseMap[(_pauseSegmentCount - 1) * 2] = signalSectionLength;
					_pauseMap[(_pauseSegmentCount - 1)*2 + 1] = pauseSectionLength;

					signalSectionLength = 0;
				}

				signalSectionLength++;
				lastPause = false;
			}
			else {											//Pause
				pauseAreaCount++;

				if (!lastPause) {
					pauseSectionLength = 0;
					_pauseSegmentCount++;
				}


				pauseSectionLength++;
				lastPause = true;
			}

			delete [] areaYY;
			delete [] areaData;
			delete [] areaPower;
		}

		if (lastPause) {
			_pauseMap[(_pauseSegmentCount - 1)*2] = signalSectionLength;
			_pauseMap[(_pauseSegmentCount - 1)*2 + 1] = pauseSectionLength;
		}

		pauseSegmentCount = _pauseSegmentCount;
		if (pauseMap != NULL) { delete pauseMap; }
		pauseMap = new USHORT[pauseSegmentCount*2];
		memcpy(pauseMap, _pauseMap, sizeof(USHORT)*pauseSegmentCount*2);

		signalWithoutPauseLength = resultLength;
		if (signalWithoutPause != NULL) { delete signalWithoutPause; }
		signalWithoutPause = new float[signalWithoutPauseLength];
		memcpy(signalWithoutPause, resultData, sizeof(float)*signalWithoutPauseLength);

		for (USHORT i = 0; i < Rp*Jp; i++)
			delete [] AAp[i];
		delete [] AAp;

		delete [] pausePower;
		delete [] resultData;
		delete [] _pauseMap;
	}

	void RecoveryPause() {
		if (signal != NULL) delete [] signal;
		signal = new float[signalLength + Ns + Np];
		memset(signal, 0, sizeof(float)*(signalLength + Ns + Np));

		unsigned int wavShift = 0;
		unsigned int resultShift = 0;

		for (int pauseIndex = 0; pauseIndex < pauseSegmentCount; pauseIndex++) {
			int pauseMapIndex = pauseIndex * 2;

			float* pauseData = new float[Np*pauseMap[pauseMapIndex +1]];
			memset(pauseData, 0, sizeof(float)*(Np*pauseMap[pauseMapIndex +1]));

			memcpy(signal + resultShift, signalWithoutPause + wavShift, sizeof(float) * (Np*pauseMap[pauseMapIndex]));
			resultShift += (Np*pauseMap[pauseMapIndex]);
			wavShift += (Np*pauseMap[pauseMapIndex]);
			memcpy(signal + resultShift, pauseData, sizeof(float) * (Np*pauseMap[pauseMapIndex +1]));
			resultShift += Np*pauseMap[pauseMapIndex +1];

			delete [] pauseData;
		}
	}

	void CompressData() {
		if (signalWithoutPause == NULL && signal == NULL) {
			return;
		}

		float* _signal = signalWithoutPause == NULL ? signal : signalWithoutPause;
		UINT _signalLength = signalWithoutPause == NULL ? signalLength : signalWithoutPauseLength;

		float** AAs = new float*[Rs*Js];
		for (USHORT i = 0; i < Rs*Js; i++)
			AAs[i] = new float[Ns];

		_LoadMatrix(AAs, Ns, Rs);

		UINT areaCount = (int)ceil(_signalLength / (float)Ns);

		USHORT* quantRes = new USHORT[Rs*Js];
		float* RsMax = new float[Rs];
		bool* sSign = new bool[Rs*Js];

		Frame* frames = new Frame[areaCount];

		for (UINT currArea = 0; currArea < areaCount; currArea++) {
			UINT areaLength = (currArea + 1)*Ns > _signalLength ? _signalLength - (currArea)*Ns : Ns;

			float* areaData = new float[areaLength];			//Семпл
			memcpy(areaData, _signal+(currArea*Ns), sizeof(float)*areaLength);

			float area_mean = MatrixProcessing::matrix_mean(&areaData, 1, areaLength);

			//Сигнал минус среднее
			for (int i = 0; i < areaLength; i++)
				areaData[i] = areaData[i] - area_mean;

			float* areaYY = new float[Rs*Js]; //Субполосный вектор
			MatrixProcessing::matrix_mult_trans(&areaData, AAs, 1, areaLength, Rs*Js, &areaYY);

			//Квантование
			memset(quantRes, 0, sizeof(USHORT)*Rs*Js);
			memset(RsMax, 0, sizeof(float)*Rs);
			memset(sSign, 0, sizeof(bool)*Rs*Js);

			USHORT quantLvlCnt = pow(2.0, compressedBps);

			for (USHORT i = 0; i < Rs; i++) {
				float max = abs(areaYY[i*Js]);
				//Вычисление максимума для частотного интервала и знаков числа
				for (USHORT j = 0; j < Js; j++) {
					int mIndex = i*Js + j;
					if (areaYY[mIndex] < 0) sSign[mIndex] = true;

					areaYY[mIndex] = abs(areaYY[mIndex]);
					if (areaYY[mIndex] > max) {
						max = areaYY[mIndex];
					}
				}

				float delta = max / (quantLvlCnt - 1);
				for (USHORT j = 0; j < Js; j++) {
					int mIndex = i*Js + j;
					quantRes[mIndex] = floor((areaYY[mIndex] / delta) + 0.5);
				}
				RsMax[i] = max;
			}

			frames[currArea] = Frame(Rs, Ns, compressedBps, RsMax, quantRes, sSign);

			delete [] areaYY;
			delete [] areaData;
		}

		for (USHORT i = 0; i < Rs*Js; i++)
			delete [] AAs[i];
		delete [] AAs;

		delete [] RsMax;
		delete [] sSign;
		delete [] quantRes;

		FrameContainer frameContainer(frames, areaCount);

		UINT maxFrameSize = Rs*sizeof(short) + ceil((compressedBps + 1)*(Rs*Js) / 8.0);
		
		BYTE* _compressedData = new BYTE[maxFrameSize * areaCount];
		compressedDataLength = frameContainer.WriteData(_compressedData);

		if (compressedData != NULL)
			delete [] compressedData;

		compressedData = new BYTE[compressedDataLength];
		memcpy(compressedData, _compressedData, sizeof(BYTE)*compressedDataLength);
	}

	void DecompressData() {
		if (compressedData == NULL) return;

		float** AAs = new float*[Rs*Js];
		for (USHORT i = 0; i < Rs*Js; i++)
			AAs[i] = new float[Ns];

		_LoadMatrix(AAs, Ns, Rs);

		UINT minFrameSize = Rs*sizeof(USHORT) + ceil((compressedBps)*(Rs*Js) / 8.0);
		UINT maxFrameCount = ceil(compressedDataLength/(float) minFrameSize);

		FrameContainer frames(maxFrameCount);
		frames.ReadData(compressedData, compressedDataLength, Rs, Ns, compressedBps);

		float* recoveryData = new float[signalLength];
		memset(recoveryData, 0, sizeof(float)*signalLength);

		int recoveryLength = 0;

		for (int frameIndex = 0; frameIndex < frames.frameCount; frameIndex++) {
			int quantLvlCnt = pow(2.0, frames.frames[frameIndex].bps);

			float* areaYY = new float[Rs*Js];
			memset(areaYY, 0, sizeof(float)*Rs*Js);

			float* areaData = new float[Ns];
			memset(areaData, 0, sizeof(float)*Ns);

			for (int i = 0; i < Rs; i++) {
				float max = frames.frames[frameIndex].maxs[i];
				float delta = max / (quantLvlCnt - 1);

				for (int j = 0; j < Js; j++) {
					int m_index = i*Js + j;
					float val = frames.frames[frameIndex].quantValues[m_index] * delta;
					if (frames.frames[frameIndex].sign[m_index]) val *= -1;

					areaYY[m_index] = val;
				}
			}

			MatrixProcessing::matrix_mult(&areaYY, AAs, 1, Rs*Js, Ns, &areaData);
			memcpy(recoveryData + (frameIndex*Ns), areaData, sizeof(float)*Ns);
			recoveryLength += Ns;

			delete [] areaYY;
			delete [] areaData;
		}

		signalWithoutPauseLength = recoveryLength;
		if (signalWithoutPause != NULL) delete signalWithoutPause;
		signalWithoutPause = new float[signalWithoutPauseLength];

		memcpy(signalWithoutPause, recoveryData, sizeof(float)*signalWithoutPauseLength);

		for (USHORT i = 0; i < Rs*Js; i++)
			delete [] AAs[i];
		delete [] AAs;

		delete [] recoveryData;
	}

	void FullCompressData() {
		DeletePause();
		CompressData();
	}

	void FullDecompressData() {
		DecompressData();
		RecoveryPause();
	}
};

#endif // SWPM_H
