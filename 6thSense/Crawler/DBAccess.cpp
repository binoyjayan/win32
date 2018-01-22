// DBAccess.cpp: implementation of the CDBAccess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Crawler.h"
#include "DBAccess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBAccess::CDBAccess()
{
	m_Driver = "MICROSOFT ACCESS DRIVER (*.MDB)";
	m_pRS = new CRecordset ( &m_DataBase );
}

CDBAccess::~CDBAccess()
{
	delete m_pRS;
}

BOOL CDBAccess::Open()
{	
	CString conn;
	try
	{
		conn.Format ( "DRIVER={%s};DSN='';READONLY=FALSE;DBQ=6thSense.mdb", m_Driver);
		return m_DataBase.OpenEx(conn, CDatabase::noOdbcDialog );
	}
	catch(...)
	{
		return FALSE;
	}
}

CRecordset* CDBAccess::ExecuteQuery(CString sql)
{
	m_pRS->Open(CRecordset::snapshot, sql, CRecordset::none);
	return m_pRS;
}

int CDBAccess::ExecuteUpdate(CString sql)
{
	try
	{
		m_DataBase.ExecuteSQL(sql);
	}
	catch(CDBException e)	
	{
		return FALSE;
	}
	return TRUE;
}

void CDBAccess::Close()
{
	m_DataBase.Close();
}
