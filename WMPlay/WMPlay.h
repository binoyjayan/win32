// WMPlay.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CWMPlayApp:
// See WMPlay.cpp for the implementation of this class
//

class CWMPlayApp : public CWinApp
{
public:
	CWMPlayApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileExit();
};

extern CWMPlayApp theApp;