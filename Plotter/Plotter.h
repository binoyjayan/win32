// Plotter.h : main header file for the PLOTTER application
//

#if !defined(AFX_PLOTTER_H__21AFB6E6_E10A_4D46_AC27_85EC1F5AFE0D__INCLUDED_)
#define AFX_PLOTTER_H__21AFB6E6_E10A_4D46_AC27_85EC1F5AFE0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlotterApp:
// See Plotter.cpp for the implementation of this class
//

class CPlotterApp : public CWinApp
{
public:
	CPlotterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPlotterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTTER_H__21AFB6E6_E10A_4D46_AC27_85EC1F5AFE0D__INCLUDED_)
