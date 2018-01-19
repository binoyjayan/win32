// Lex.h: interface for the CLex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEX_H__9CD686FC_49F9_4019_A560_8790963A618B__INCLUDED_)
#define AFX_LEX_H__9CD686FC_49F9_4019_A560_8790963A618B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLex  
{
	int m_index;
	char prev;
public:
	char t[50];
	int Lex(double&);
	char* s;
	CLex(char *);
	virtual ~CLex();

};

#endif // !defined(AFX_LEX_H__9CD686FC_49F9_4019_A560_8790963A618B__INCLUDED_)
