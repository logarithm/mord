#ifndef SOUND_H__INCLUDED
#define SOUND_H__INCLUDED

typedef unsigned char byte;

class Sound
{
public:
	virtual void Create(char* file, float* data, int size, short channels, unsigned rate, short BPS)=0;
	virtual void Destroy()=0;
	virtual int Load(char* file)=0;
	virtual void Unload()=0;
	virtual int Read(void *target,int bps,int count)=0;
	virtual int ReadFlt(float *target,int count)=0;
	virtual float GetLength()=0;

protected:
	int chan;
	int bps;
	int rate;

public:
	int getChannels(){
		return this->chan;
	}

	int getBPS(){
		return this->bps;
	}
	int getRate(){
		return this->rate;
	}
};

#endif