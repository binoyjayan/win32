// Crawler.h : main header file for the CRAWLER application
//

#if !defined(AFX_CRAWLER_H__E243D6F9_E65F_4BA2_8A7B_B2E9544275CE__INCLUDED_)
#define AFX_CRAWLER_H__E243D6F9_E65F_4BA2_8A7B_B2E9544275CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCrawlerApp:
// See Crawler.cpp for the implementation of this class
//

class CCrawlerApp : public CWinApp
{
public:
	CCrawlerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrawlerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CCrawlerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRAWLER_H__E243D6F9_E65F_4BA2_8A7B_B2E9544275CE__INCLUDED_)
