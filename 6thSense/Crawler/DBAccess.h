// DBAccess.h: interface for the CDBAccess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBACCESS_H__886B7245_B8C7_4CB2_9199_40FD5BE257EC__INCLUDED_)
#define AFX_DBACCESS_H__886B7245_B8C7_4CB2_9199_40FD5BE257EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDBAccess  
{
public:
	CDatabase m_DataBase;
	void Close();
	int ExecuteUpdate(CString query);
	CRecordset * ExecuteQuery(CString query);
	CRecordset * m_pRS;
	BOOL Open();
	CString m_Driver;
	CDBAccess();
	virtual ~CDBAccess();

};

#endif // !defined(AFX_DBACCESS_H__886B7245_B8C7_4CB2_9199_40FD5BE257EC__INCLUDED_)
