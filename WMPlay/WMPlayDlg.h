// WMPlayDlg.h : header file
//

#pragma once
#include "wmplayer.h"


// CWMPlayDlg dialog
class CWMPlayDlg : public CDialog
{
// Construction
public:
	LRESULT OnMessage77Play(WPARAM w, LPARAM l);
	CWMPlayDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WMPLAY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()

// The player's variable to be used by user
	CWmplayer m_Player;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnOpen();
	afx_msg void OnHelpAbout();
};
