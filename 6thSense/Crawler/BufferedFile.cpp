// BufferedFile.cpp: implementation of the CBufferedFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Crawler.h"
#include "BufferedFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CBufferedFile::CBufferedFile()
{
	bufferstring = new char[BUFFERSIZE];
}

CBufferedFile::~CBufferedFile()
{
	delete[] bufferstring;
}
void CBufferedFile::Init(CHttpFile *httpfile)
{
	file = httpfile;
	bufferpos = 0;
	validdata = 0;
}

char CBufferedFile::Get()
{
	char t;
	if(bufferpos >= validdata)
	{
		validdata = file->Read(bufferstring, BUFFERSIZE);
		bufferpos = 0;
	}
	if(validdata == 0)
	{
		return EOF;
	}
	t = bufferstring[bufferpos];
	bufferpos++;
	return t;
}
char CBufferedFile::Peek()
{
	char t;
	if(bufferpos >= validdata)
	{
		validdata = file->Read(bufferstring, BUFFERSIZE);
		bufferpos = 0;
	}
	if(validdata == 0)
	{
		return EOF;
	}
	t = bufferstring[bufferpos];
	return t;
}
unsigned int CBufferedFile::Read(void *s, unsigned int nChars)
{
	unsigned int valid;
	valid = validdata - bufferpos;

	if(valid >= nChars)//if data available in buffer
	{
		memcpy(s, bufferstring + bufferpos, nChars);
		bufferpos += nChars;
		return nChars;
	}
	unsigned int copied = 0;
	memcpy(s, bufferstring + bufferpos, valid);
	bufferpos += valid;
	copied = valid + file->Read((char*)s + valid, nChars - valid);
	return copied;	
}


int CBufferedFile::GetValidData()
{
	return validdata;
}

char* CBufferedFile::GetBuffer()
{
	Peek();//Fill in the buffer if empty
	return bufferstring;
}
