// CrawlerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Crawler.h"
#include "CrawlerDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCrawlerDlg dialog


CCrawlerDlg::CCrawlerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCrawlerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCrawlerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCrawlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCrawlerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCrawlerDlg, CDialog)
	//{{AFX_MSG_MAP(CCrawlerDlg)		
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCrawlerDlg message handlers

void CCrawlerDlg::UpdateURL(char *URL)
{	
	SetDlgItemText(IDC_STATIC1, URL);

}

void CCrawlerDlg::UpdateLink(char *lpszLink)
{
	SetDlgItemText(IDC_STATIC2, lpszLink);
}

void CCrawlerDlg::OnOK() 
{
	CMainFrame *w = (CMainFrame*)((CCrawlerApp*) AfxGetApp())->m_pMainWnd;
	w->Stop();
	CDialog::OnOK();
}
