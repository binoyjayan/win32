
#include<afxwin.h>
#include <shlwapi.h>

#define BUFFERSIZE 1024

class CBuffer
{
private:	
	CFile file;
	int fileopenflag;
	char bufferstring[1024];
	int bufferpos;
	int validdata;
public:
	char Peek();
	CBuffer();
	~CBuffer();
	int Open(char *s);
	void Close();
	unsigned int Read(void *s, unsigned int nChars);
	char Get();
	
};

CBuffer::~CBuffer()
{
	if(fileopenflag)
	{
		fileopenflag = 0;
		//puts("Closing file\n");
		file.Close();
	}
	
}

CBuffer::CBuffer()
{
	fileopenflag = 0;
	bufferpos = 0;
	validdata = 0;
}

int CBuffer::Open(char *s)
{
	int temp;
	if((temp = file.Open(s, CFile::modeRead)) > 0)
		 fileopenflag = 1;
	return temp;
	
}

void CBuffer::Close()
{
	if(fileopenflag)
	{
		fileopenflag = 0;
		file.Close();
		//puts("close.......................");
	}
}
char CBuffer::Peek()
{
	char t;
	if(bufferpos >= validdata)
	{
		validdata = file.Read(bufferstring, BUFFERSIZE);
		bufferpos = 0;
	}
	if(validdata == 0)
	{
		return EOF;
	}
	t = bufferstring[bufferpos];
	return t;
}

char CBuffer::Get()//fgetc
{
	char t;
	if(bufferpos >= validdata)
	{
		validdata = file.Read(bufferstring, BUFFERSIZE);
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

unsigned int CBuffer::Read(void *s, unsigned int nChars)//fread
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
	copied = valid + file.Read((char*)s + valid, nChars - valid);
	return copied;	
}

class Parser
{
	CBuffer buf;
public:	
	int MetaInfoFound(char *description, char *content);
	void CleanUp();
	int GetNextTag(char *tag, char *attr, char *value, char *content, char * descript, int *desflag);
	int Init();
	Parser();
	~Parser();
};

Parser::Parser()
{
}

Parser::~Parser()
{

}
void Parser::CleanUp()
{
	buf.Close();
}

int Parser::Init()
{
	if(buf.Open("oracle.htm") <= 0)
	{
		//puts("Error in opening file");
		return 0;
	}
	return 1;
}

#define		TAG_AHREF			1
#define		TAG_IMGSRC			2
#define		TAG_FRAMESRC		3
#define		TAG_EMBEDSRC		4
#define		TAG_OBJECTDATA		5

int Parser::GetNextTag(char *tag, char *attr, char *value, char *content, char * descript, int *desflag)
{
	int desindex;
	int processingtag;
	int index1, index2, tagtype = 0, flag;
	int ttag, tattr;
	char ch, temp;
	char tempstr[100];
	
	//count = buf.Read(str, 1024);

	descript[0] = '\0';
start:
	processingtag = 0;
	while((ch = buf.Get()) != EOF)
	{
		index1 = 0;
		if(ch == '<')
		{
			processingtag = 1;
			
			if(buf.Peek() == '/')
			{
				processingtag = 0;
				continue;
			}
		}
		else if(*desflag == 1 && !processingtag)	//if body surpassed
		{
			if(ch != '>')
			{
				descript[0] = ch;
				desindex = 1;
			}
			while(buf.Peek() != EOF && buf.Peek() != '<')	//change to peek
			{
				descript[desindex] = buf.Get();
				if(descript[desindex] == '.' || desindex > 240)
				{
					//check meta content validation
					temp = descript[desindex];
					descript[desindex] = '\0';
					if(MetaInfoFound(descript, content))
					{
						printf("Meta paragraph : %s\n", descript);
						getchar();
						//*desflag = 2; //finished
					}
					else
					{
						descript[0] = '\0';
					}
					break;
				}
				desindex++;
			}
			switch(buf.Peek())
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
	
		//printf("character =%c%c$\n", temp, tag[index1-1]);

		while((temp = buf.Get()) != EOF)
		{
			tag[index1] = temp;
			if(temp == ' ' || temp == '\t' || temp == '\n' || temp == '\r' || temp == '=' || temp == '>' || index1 > 6)
			{				
				tag[index1] = '\0';
				//printf("$%s$", tag);
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
						while(buf.Peek() != EOF && buf.Peek() != '<')
							buf.Get();
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

	while((attr[index2] = buf.Get()) != EOF)
	{
		if(attr[index2] == ' ' || attr[index2] == '\t' || attr[index2] == '\n' || attr[index2] == '\r' || attr[index2] == '=')
		{
			if(index2 == 0)
				continue;
			else
			{				
				attr[index2] = '\0';
				//printf("attr = %s\n", attr);
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
	while((value[0] = buf.Get()) != EOF)
	{
		if(value[0] == '\"')
			flag = 1;
		if(value[0] != '\"' && value[0] != ' ' && value[0] != '\t' && value[0] != '\n' && value[0] != '\r')
			break;
	}

	index1 = 1;
	while((value[index1] = buf.Get()) != EOF)
	{
		if(flag == 1)
		{
			if(value[index1] == '>' || value[index1] == '\"' || index1 > 149)
			{
				value[index1] = '\0';
				break;
			}
			//if(value[index1] != ' ' && value[index1] != '\t' && value[index1] != '\n' && value[index1] != '\r')
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
		while((tempstr[index2] = buf.Get()) != EOF)
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
	}
	else
	{
		//Skip till '>'
		if(value[index1] != '>') while((temp = buf.Get()) != EOF) if(temp == '>') break;
		if(temp == EOF) return 0;
	}


	//Now get the content between <a> & </a>

	index2 = 0;
	content[index2] = '\0';

	while(buf.Peek() != EOF)
	{
		if(buf.Peek() == '<')
		{
			content[index2] = '\0';
			break;		//end while AND END FUNCTION
		}
		content[index2] = buf.Get();

		if(content[index2] == '\t' || content[index2] == '\n' || content[index2] == '\r')
			content[index2] = ' ';
		index2++;
	}
	
	StrTrim(content, " \t\n\r");	//remove \t, \n and space

	printf("<%s %s = \'%s\'>%s</%s>\n", tag, attr, value, content, tag);

	if(attr[index2] == EOF)
		return 0;
	return 1;
}
int Parser::MetaInfoFound(char *description, char *content)
{
	return 1;
}


main()
{
	Parser p;
	int desflag = 0;
	char tag[12], attr[12], value[150], content[100];
	char descript[250];
	if(!p.Init())
	{
		puts("Could not open file");
		getchar();
		return 0;
	}
	while(p.GetNextTag(tag, attr, value, content, descript, &desflag));
	p.CleanUp();
	return 0;
}



