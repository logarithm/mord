#ifndef _MGSP_FILE_
#define _MGSP_FILE_

#include <stdio.h>

class MFile
{
public:
	int		eof;
	virtual int Read(void *target,int size)=0;
	virtual int Write(void *source,int size)=0;
	virtual int Seek(int offset,int mode)=0;
	virtual int Tell()=0;
        virtual void Close()=0;
	virtual ~MFile(){};

	template<class T> __inline int Read(T *target)
	{ return (Read((void*)target,sizeof(T))==sizeof(T))?1:0; }
	template<class T> __inline int Write(T *target)
	{ return (Write((void*)target,sizeof(T))==sizeof(T))?1:0; }
};

class MAnsiFile: public MFile
{
	FILE *f;
	bool noclose;
	MAnsiFile(MAnsiFile& file){	f=file.f;	noclose=true;	}
	MAnsiFile& operator=(MAnsiFile& file){	f=file.f;	noclose=true;	}
public:
	MAnsiFile(FILE *fu){ eof=0; f=fu; }
	virtual int Read(void *target,int size)
	{
		if(!f)return -1;
		int res=fread(target,1,size,f);
		eof=feof(f);
		return res;
	}
	virtual int Write(void *source,int size)
	{	if(!f)return -1;	return fwrite(source,1,size,f); }
	virtual int Seek(int offset,int mode)
	{	if(!f)return -1;	return fseek(f,(long)offset,mode);	}
	virtual int Tell()
	{	if(!f)return -1;	return ftell(f);	}
        virtual void Close()
        {
            if(f)fclose(f);     }
	virtual ~MAnsiFile()
        {	Close();	}
};

__inline MFile* mOpenFile(char *filename,char *mode)
{
	FILE* file=fopen(filename,mode);
	MAnsiFile* fobj=new MAnsiFile(file);
	return (MFile*)fobj;
}

#endif
