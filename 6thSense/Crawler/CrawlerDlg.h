#if !defined(AFX_CRAWLERDLG_H__22E0A992_2577_4744_BA38_A952B89CF0B4__INCLUDED_)
#define AFX_CRAWLERDLG_H__22E0A992_2577_4744_BA38_A952B89CF0B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrawlerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCrawlerDlg dialog

class CCrawlerDlg : public CDialog
{
// Construction
public:
	void UpdateLink(char *lpszLink);
	void UpdateURL(char *URL);
	CCrawlerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCrawlerDlg)
	enum { IDD = IDD_CRAWLING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrawlerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCrawlerDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRAWLERDLG_H__22E0A992_2577_4744_BA38_A952B89CF0B4__INCLUDED_)
