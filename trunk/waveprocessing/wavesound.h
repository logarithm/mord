#ifndef WAVESOUND_H__INCLUDED
#define WAVESOUND_H__INCLUDED

#include "file.h"
#include "sound.h"

#define STRI(x) (*((unsigned*)(x)))

class WaveSound : public Sound
{
	MFile *file;
	int full_length;
	int available;

public:

	struct WavRiffHead{
		unsigned riff;
		unsigned size;
		unsigned wave;
	};

	struct WavChunkHead{
		unsigned type;
		unsigned size;
	};

	struct WavFormatHead{
		short format;
		short channels;
		unsigned rate;
		unsigned AvgBytesPS;
		short align;
		short BPS;
	};

	WaveSound(){
		file = NULL;
	}
	virtual void Create(){}
	virtual void Destroy()
	{
		Unload();
	}

	virtual int Load(char* fn)
	{
		file = mOpenFile(fn,"rb");

		{
			WavRiffHead h;
			if(!file->Read(&h))return 0;
			if(h.riff != STRI("RIFF")) return 0;
			if(h.wave != STRI("WAVE")) return 0;
		}
		
		int format_read = 0;

		while(1)
		{
			WavChunkHead ch;
			if(!file->Read(&ch))return 0;

			if(ch.type == STRI("fmt "))
			{
				WavFormatHead f;
				if(!file->Read(&f))return 0;

				if(f.format != 1)
				{
					printf("\r[ERR ] Can't read compessed wave file\r\n");
					return 0;
				}
				this->chan = f.channels;
				this->bps = f.BPS;
				this->rate = f.rate;

				format_read = 1;

				file->Seek(ch.size - sizeof(WavFormatHead),SEEK_CUR);
			}else
			if(ch.type == STRI("data"))
			{
				if(!format_read) 
				{
					printf("\r[ERR ] Misplaced 'data' section\r\n");
					return 0;
				}

				//number of data samples available
				full_length = available = ch.size / (bps>>3);

				return 1;
			}else
			{
				file->Seek(ch.size,SEEK_CUR);
			}
		}
	}
	
	virtual void Unload()
	{
		if(file)delete file;
		file = NULL;

		available = 0;
	}

    virtual int ReadFlt(float *target,int count)
    {
        if(!file || file->eof) return 0;
        if(this->bps == 8)
        {
            if(count > available) count = available;
            
            unsigned char b[256];
            int r=0, realcount=0;
            while(count)
            {
                if(!available) return realcount;

                if(count > 256) r = file->Read(b,256);
                else r = file->Read(b,count);

                if(!r) return realcount;
                count -= r;
                available -= r;
                realcount += r;

                for(register int i=0; i<r; i++)
                {
                    *target++ = (float)((int)(b[i]) - 128) / 128.0f;
                }
            }
            return realcount;
        }else if(bps == 16){
            if(count > available) count = available;
            
            signed short b[256];
            int r=0, realcount=0;
            while(count)
            {
                if(!available) return realcount;

                if(count > 256) r = file->Read(b,256*sizeof(short));
                else r = file->Read(b,count*sizeof(short));

                if(!r) return realcount;
                r = r / sizeof(short);
                count -= r;
                available -= r;
                realcount += r;

                for(register int i=0; i<r; i++)
                {
                    *target++ = (float)( (int)(b[i]) ) / 32768.0f;
                }
            }
            return realcount;
        }else{
            return 0;
        }
    }


	virtual int Read(void *target,int bps,int count)
	{
		if(!file || file->eof) return 0;

		return 0; //### todo
	}

	virtual float GetLength()
	{
	  	return ((float)full_length) / ((float)rate) / ((float)chan);
	}

	int getAvialible(){
		return available;
	}
};

#endif