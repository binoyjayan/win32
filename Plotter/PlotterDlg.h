// PlotterDlg.h : header file
//

#if !defined(AFX_PLOTTERDLG_H__35EA474D_37B8_4485_8885_B9D27A14D1DD__INCLUDED_)
#define AFX_PLOTTERDLG_H__35EA474D_37B8_4485_8885_B9D27A14D1DD__INCLUDED_

#include "PlotFrame.h"	// Added by ClassView
#include "Parse.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPlotterDlg dialog

class CPlotterDlg : public CDialog
{
// Construction
public:
	CParse p;
	CPlotFrame *w;
	CPlotterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPlotterDlg)
	enum { IDD = IDD_PLOTTER_DIALOG };
	CString	m_Formula;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPlotterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlot();
	afx_msg void OnSin();
	afx_msg void OnCos();
	afx_msg void OnTan();
	afx_msg void OnPlus();
	afx_msg void OnVariableX();
	afx_msg void OnNo7();
	afx_msg void OnNo8();
	afx_msg void OnNo9();
	afx_msg void OnSinh();
	afx_msg void OnAbs();
	afx_msg void OnCosh();
	afx_msg void OnDivide();
	afx_msg void OnExp();
	afx_msg void OnLeftparen();
	afx_msg void OnLog();
	afx_msg void OnMinus();
	afx_msg void OnNo0();
	afx_msg void OnNo1();
	afx_msg void OnNo2();
	afx_msg void OnNo3();
	afx_msg void OnNo4();
	afx_msg void OnNo5();
	afx_msg void OnNo6();
	afx_msg void OnPeriod();
	afx_msg void OnPower();
	afx_msg void OnRightparen();
	afx_msg void OnSqrt();
	afx_msg void OnStar();
	afx_msg void OnTanh();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTTERDLG_H__35EA474D_37B8_4485_8885_B9D27A14D1DD__INCLUDED_)
