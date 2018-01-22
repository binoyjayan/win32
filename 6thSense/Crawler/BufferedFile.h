// BufferedFile.h: interface for the CBufferedFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFEREDFILE_H__F71B34A1_6C92_42A2_8C0F_1F2769D32AED__INCLUDED_)
#define AFX_BUFFEREDFILE_H__F71B34A1_6C92_42A2_8C0F_1F2769D32AED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<afxinet.h>


#define BUFFERSIZE 1024
class CBufferedFile
{
private:	
	CHttpFile *file;
	char *bufferstring;
	int bufferpos;
	int validdata;
public:
	char* GetBuffer();
	int GetValidData();
	void Init(CHttpFile *httpfile);
	char Peek();
	CBufferedFile();
	~CBufferedFile();	
	unsigned int Read(void *s, unsigned int nChars);
	char Get();
	
};

#endif // !defined(AFX_BUFFEREDFILE_H__F71B34A1_6C92_42A2_8C0F_1F2769D32AED__INCLUDED_)
