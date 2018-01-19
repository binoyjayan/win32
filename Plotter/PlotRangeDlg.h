#if !defined(AFX_PLOTRANGEDLG_H__4E672DC8_D24F_4B09_91E6_D90B6D140E51__INCLUDED_)
#define AFX_PLOTRANGEDLG_H__4E672DC8_D24F_4B09_91E6_D90B6D140E51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlotRangeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlotRangeDlg dialog

class CPlotRangeDlg : public CDialog
{
// Construction
public:
	void SetPlotRange(int &l, int &h);
	void GetPlotRange(int &low, int &high);
	int low;
	int high;
	CPlotRangeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlotRangeDlg)
	enum { IDD = IDD_PLOTRANGE };
	CString	m_Low;
	CString	m_High;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotRangeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlotRangeDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTRANGEDLG_H__4E672DC8_D24F_4B09_91E6_D90B6D140E51__INCLUDED_)
