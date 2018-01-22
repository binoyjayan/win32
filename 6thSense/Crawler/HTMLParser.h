// HTMLParser.h: interface for the HTMLParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLPARSER_H__D3AEF2FA_9D38_4782_86A8_30D7BE1117D8__INCLUDED_)
#define AFX_HTMLPARSER_H__D3AEF2FA_9D38_4782_86A8_30D7BE1117D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferedFile.h"

class HTMLParser
{
	CBufferedFile m_Buf;
	char *m_lpszMeta;

public:	
	char * GetMetaString();
	int IsEOF();
	int GetMetaCount();

	int FindInBuffer(char *pattern);
	int MetaInfoFound(char *description, char *content);
	int GetNextTag(char *tag, char *attr, char *value, char *content, char * descript, int *desflag);
	HTMLParser(CHttpFile *httpfile);
	~HTMLParser();
private:
	int m_MetaCount;
};

#endif // !defined(AFX_HTMLPARSER_H__D3AEF2FA_9D38_4782_86A8_30D7BE1117D8__INCLUDED_)
