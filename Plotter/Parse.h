// Parse.h: interface for the CParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSE_H__ECA265BF_3C9D_4F83_9C9D_4FE3035DBD9F__INCLUDED_)
#define AFX_PARSE_H__ECA265BF_3C9D_4F83_9C9D_4FE3035DBD9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct POSTFIX
{
	int Status;
	union
	{
		int op;
		double value;
	};
};

class CParse  
{
public:
	int GetErrorCode();
	int Precedence(int oper);
	int nErrorCode;
	int m_PostFixSize;
	POSTFIX post[100];
	CString m_OrgString;
	int InfixToPostfix(CString str);
	double Evaluate(double);
	CParse();
	virtual ~CParse();

};

#endif // !defined(AFX_PARSE_H__ECA265BF_3C9D_4F83_9C9D_4FE3035DBD9F__INCLUDED_)
