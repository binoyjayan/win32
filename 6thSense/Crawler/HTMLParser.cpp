// HTMLParser.cpp: implementation of the HTMLParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Crawler.h"
#include "HTMLParser.h"
#include <shlwapi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HTMLParser::HTMLParser(CHttpFile *httpfile)
{
	m_lpszMeta = new char[512];
	m_Buf.Init(httpfile);
}

HTMLParser::~HTMLParser()
{
	delete[] m_lpszMeta;
}


#define		TAG_AHREF			1
#define		TAG_IMGSRC			2
#define		TAG_FRAMESRC		3
#define		TAG_EMBEDSRC		4
#define		TAG_OBJECTDATA		5

int HTMLParser::MetaInfoFound(char *description, char *meta)
{
	int i, j;
	char temp[50];
	i = m_MetaCount = 0;
	while(meta[i] != '\0')
	{
		j = 0;
		while(meta[i] != ' ' && meta[i] != ',' && meta[i] != '\0' )
		{
			temp[j] = meta[i];
		}
		temp[j] = '\0';

		if(strstr(description, temp))
			m_MetaCount++;
		//skip spaces
		while(meta[i] == ' ' || meta[i] == ',');
	}
	return m_MetaCount;
}

int HTMLParser::GetNextTag(char *tag, char *attr, char *value, char *content, char * descript, int *desflag)
{
	int desindex;
	int processingtag;
	int index1, index2, tagtype = 0, flag;
	int ttag, tattr;
	char ch, temp;
	char tempstr[100];
	
	//count = m_Buf.Read(str, 1024);

	descript[0] = '\0';
start:
	processingtag = 0;
	while((ch = m_Buf.Get()) != EOF)
	{
		index1 = 0;
		if(ch == '<')
		{
			processingtag = 1;
			
			if(m_Buf.Peek() == '/')
			{
				processingtag = 0;
				continue;
			}
		}
		else if(*desflag == 1 && !processingtag)	//if body surpassed go for description
		{
			if(ch != '>')
			{
				descript[0] = ch;
				desindex = 1;
			}
			while(m_Buf.Peek() != EOF && m_Buf.Peek() != '<' && m_Buf.Peek() != '>')	//peek
			{
				descript[desindex] = m_Buf.Get();
				if(descript[desindex] == '.' || desindex > 240)
				{
					//check meta content validation
					temp = descript[desindex];
					descript[desindex] = '\0';
					if(!MetaInfoFound(descript, m_lpszMeta))
					{
						descript[0] = '\0';
					}
					break;
				}
				desindex++;
			}
			switch(m_Buf.Peek())
			{ 
			case '<':
				goto start;
			case EOF:
				return 0;
			}
			continue;
		}	
		else
			continue;

//proceedtotag:
	

		while((temp = m_Buf.Get()) != EOF)
		{
			tag[index1] = temp;
			if(temp == ' ' || temp == '\t' || temp == '\n' || temp == '\r' || temp == '=' || temp == '>' || index1 > 6)
			{				
				tag[index1] = '\0';
				ttag = 0;
				if(stricmp(tag, "a") == 0)
				{
					ttag = 1;					
				}
				else if(stricmp(tag, "img") == 0)
				{
					ttag = 2;
				}
				else if(stricmp(tag, "frame") == 0)
				{
					ttag = 3;						
				}
				else if(stricmp(tag, "embed") == 0)
				{
					ttag = 4;						
				}
				else if(stricmp(tag, "object") == 0)
				{
					ttag = 5;					
				}
				else if(stricmp(tag, "meta") == 0)
				{
					ttag = 6;
				}
				else 
				{
					if(stricmp(tag, "body") == 0)
						*desflag = 1; //set that body tag is surpassed

					if(temp != '>')		//complete the tag
					{
						while(m_Buf.Peek() != EOF && m_Buf.Peek() != '<')
							m_Buf.Get();
					}

					goto start;
				}					
				goto get_attribute;
			}
			index1++;
		}
	}
	if(ch == EOF)
			return 0;

get_attribute:	
	index2 = 0;

	//Now get attributes

	while((attr[index2] = m_Buf.Get()) != EOF && index2 < 249)
	{
		if(attr[index2] == ' ' || attr[index2] == '\t' || attr[index2] == '\n' || attr[index2] == '\r' || attr[index2] == '=')
		{
			if(index2 == 0)
				continue;
			else
			{				
				attr[index2] = '\0';
			}
			if(stricmp(attr, "href") == 0)
			{
				tattr = 1;
				break;
			}
			else if(stricmp(attr, "src") ==0)
			{
				tattr = 2;
				break;
			}
			else if(stricmp(attr, "data") ==0)	
			{
				tattr = 3;
				break;
			}
			else if(stricmp(attr, "content") ==0)	
			{
				tattr = 4;
				break;
			}
			else
				index2 = 0;
		}
		else
		{
			if(index2 > 6)
				index2 = 0;
			index2++;
		}
	}
	
	flag = 0;
	while((value[0] = m_Buf.Get()) != EOF)
	{
		if(value[0] == '\"')
			flag = 1;
		if(value[0] != '\"' && value[0] != ' ' && value[0] != '\t' && value[0] != '\n' && value[0] != '\r')
			break;
	}

	index1 = 1;
	while((value[index1] = m_Buf.Get()) != EOF)
	{
		if(flag == 1)
		{
			if(value[index1] == '>' || value[index1] == '\"' || index1 > 149)
			{
				value[index1] = '\0';
				break;
			}
			index1++;
		}
		else
		{
			if(value[index1] == '>' || value[index1] == ' ' || value[index1] == '\t' || value[index1] == '\r' || value[index1] == '\n' || value[index1] == '\"' || index1 > 149)
			{
				value[index1] = '\0';
				break;
			}
			index1++;
		}
	}
	
	if(value[0] == '>' || index1 > 149) //Bad attribute. Go back to get new tag
		goto start;		
	
	if(ttag == 6 && tattr == 4) //<meta content>
	{
		index2 = 0;
		while((tempstr[index2] = m_Buf.Get()) != EOF)
		{
			if(tempstr[index2] == '>')
			{
				tempstr[index2] = '\0';
				break;
			}
			index2++;
		}
		if(strstr(tempstr, "keywords") == NULL)
		{
			//Skip meta tag and take up next tag
			goto start;
		}
		else
		{
			strcpy(m_lpszMeta, value);//Set meta information
		}
	}
	else
	{
		//Skip till '>'
		if(value[index1] != '>') while((temp = m_Buf.Get()) != EOF) if(temp == '>') break;
		if(temp == EOF) return 0;
	}


	//Now get the content between <a> & </a>

	index2 = 0;
	content[index2] = '\0';

	while(m_Buf.Peek() != EOF)
	{
		if(m_Buf.Peek() == '<')
		{
			content[index2] = '\0';
			break;					//end while AND END FUNCTION
		}
		content[index2] = m_Buf.Get();

		if(content[index2] == '\t' || content[index2] == '\n' || content[index2] == '\r')
			content[index2] = ' ';
		index2++;
	}
		
	StrTrim(content, " \t\n\r");	//remove \t, \n and space

	if(attr[index2] == EOF)
		return 0;
	return 1;
}

int HTMLParser::FindInBuffer(char *pattern)
{
	char * buf = m_Buf.GetBuffer();
	if(strstr(buf,pattern) != NULL)
	{
		return TRUE;
	}
	else
	{		
		return FALSE;
	}
}

int HTMLParser::GetMetaCount()
{
	return m_MetaCount;
}

int HTMLParser::IsEOF()
{
	return m_Buf.Peek() == EOF ? 1 : 0;
}

char * HTMLParser::GetMetaString()
{
	return m_lpszMeta;
}

