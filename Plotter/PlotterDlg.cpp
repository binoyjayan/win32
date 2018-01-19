// PlotterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Plotter.h"
#include "PlotterDlg.h"
#include "Parse.h"
#include "symbol.h"
#include "PlotFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotterDlg dialog

CPlotterDlg::CPlotterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlotterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlotterDlg)
	m_Formula = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	w = new CPlotFrame();
}

void CPlotterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlotterDlg)
	DDX_Text(pDX, IDC_FORMULA, m_Formula);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPlotterDlg, CDialog)
	//{{AFX_MSG_MAP(CPlotterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLOT, OnPlot)
	ON_BN_CLICKED(IDC_SIN, OnSin)
	ON_BN_CLICKED(IDC_COS, OnCos)
	ON_BN_CLICKED(IDC_TAN, OnTan)
	ON_BN_CLICKED(IDC_PLUS, OnPlus)
	ON_BN_CLICKED(IDC_VARX, OnVariableX)
	ON_BN_CLICKED(IDC_NO7, OnNo7)
	ON_BN_CLICKED(IDC_NO8, OnNo8)
	ON_BN_CLICKED(IDC_NO9, OnNo9)
	ON_BN_CLICKED(IDC_SINH, OnSinh)
	ON_BN_CLICKED(IDC_ABS, OnAbs)
	ON_BN_CLICKED(IDC_COSH, OnCosh)
	ON_BN_CLICKED(IDC_DIVIDE, OnDivide)
	ON_BN_CLICKED(IDC_EXP, OnExp)
	ON_BN_CLICKED(IDC_LEFTPAREN, OnLeftparen)
	ON_BN_CLICKED(IDC_LOG, OnLog)
	ON_BN_CLICKED(IDC_MINUS, OnMinus)
	ON_BN_CLICKED(IDC_NO0, OnNo0)
	ON_BN_CLICKED(IDC_NO1, OnNo1)
	ON_BN_CLICKED(IDC_NO2, OnNo2)
	ON_BN_CLICKED(IDC_NO3, OnNo3)
	ON_BN_CLICKED(IDC_NO4, OnNo4)
	ON_BN_CLICKED(IDC_NO5, OnNo5)
	ON_BN_CLICKED(IDC_NO6, OnNo6)
	ON_BN_CLICKED(IDC_PERIOD, OnPeriod)
	ON_BN_CLICKED(IDC_POWER, OnPower)
	ON_BN_CLICKED(IDC_RIGHTPAREN, OnRightparen)
	ON_BN_CLICKED(IDC_SQRT, OnSqrt)
	ON_BN_CLICKED(IDC_STAR, OnStar)
	ON_BN_CLICKED(IDC_TANH, OnTanh)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotterDlg message handlers

BOOL CPlotterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlotterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlotterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPlotterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CPlotterDlg::OnPlot() 
{
	UpdateData(true);
	switch(p.InfixToPostfix(m_Formula))
	{
	case TOKENERROR:
		m_Formula.Format("Undefined symbol at character position %d",p.GetErrorCode());
		break;
	case UNBALANCED_PARENTHESIS:
		m_Formula.Format("Unbalanced parenthesis specification at token no: %d",p.GetErrorCode());
		break;
	case UNHANDLED_ERROR:
		m_Formula.Format("Error at possible location %d",p.GetErrorCode());
		break;
	case PARSE_SUCCESS:
		w->SetWindowText("Plotting y = " + m_Formula);
		w->ShowWindow(SW_NORMAL);
		w->Plot(p);	
	}
	UpdateData(false);

}
void CPlotterDlg::OnSin() 
{
	UpdateData(true);
	m_Formula += "SIN(";
	UpdateData(false);
}
void CPlotterDlg::OnCos() 
{
	UpdateData(true);
	m_Formula += "COS(";
	UpdateData(false);
}

void CPlotterDlg::OnTan() 
{
	UpdateData(true);
	m_Formula += "TAN(";
	UpdateData(false);
}

void CPlotterDlg::OnPlus() 
{
	UpdateData(true);
	m_Formula += '+';
	UpdateData(false);
}

void CPlotterDlg::OnVariableX() 
{
	UpdateData(true);
	m_Formula += 'x';
	UpdateData(false);

}
void CPlotterDlg::OnNo7() 
{
	UpdateData(true);
	m_Formula += '7';
	UpdateData(false);
}

void CPlotterDlg::OnNo8() 
{
	UpdateData(true);
	m_Formula += '8';
	UpdateData(false);
}
void CPlotterDlg::OnNo9() 
{
	UpdateData(true);
	m_Formula += '9';
	UpdateData(false);
}

void CPlotterDlg::OnSinh() 
{
	UpdateData(true);
	m_Formula += "SINH(";
	UpdateData(false);
}

void CPlotterDlg::OnAbs() 
{
	UpdateData(true);
	m_Formula += "ABS(";
	UpdateData(false);
}

void CPlotterDlg::OnCosh() 
{
	UpdateData(true);
	m_Formula += "COSH(";
	UpdateData(false);	 

}

void CPlotterDlg::OnDivide() 
{
	UpdateData(true);
	m_Formula += '/';
	UpdateData(false);
}

void CPlotterDlg::OnExp() 
{
	UpdateData(true);
	m_Formula += "EXP(";
	UpdateData(false);
	
}

void CPlotterDlg::OnLeftparen() 
{
	UpdateData(true);
	m_Formula += '(';
	UpdateData(false);
}

void CPlotterDlg::OnLog() 
{
	UpdateData(true);
	m_Formula += "LOG(";
	UpdateData(false);
	
}

void CPlotterDlg::OnMinus() 
{
	UpdateData(true);
	m_Formula += '-';
	UpdateData(false);
}

void CPlotterDlg::OnNo0() 
{	
	UpdateData(true);
	m_Formula += '0';
	UpdateData(false);
}

void CPlotterDlg::OnNo1() 
{
	UpdateData(true);
	m_Formula += '1';
	UpdateData(false);
}

void CPlotterDlg::OnNo2() 
{
	UpdateData(true);
	m_Formula += '2';
	UpdateData(false);
}

void CPlotterDlg::OnNo3() 
{
	UpdateData(true);
	m_Formula += '3';
	UpdateData(false);
}

void CPlotterDlg::OnNo4() 
{
	UpdateData(true);
	m_Formula += '4';
	UpdateData(false);
}

void CPlotterDlg::OnNo5() 
{
	UpdateData(true);
	m_Formula += '5';
	UpdateData(false);
}

void CPlotterDlg::OnNo6() 
{
	UpdateData(true);
	m_Formula += '6';
	UpdateData(false);
}

void CPlotterDlg::OnPeriod() 
{
	UpdateData(true);
	m_Formula += '.';
	UpdateData(false);
}

void CPlotterDlg::OnPower() 
{	
	UpdateData(true);
	m_Formula += '^';
	UpdateData(false);
}

void CPlotterDlg::OnRightparen() 
{
	UpdateData(true);
	m_Formula += ')';
	UpdateData(false);
}

void CPlotterDlg::OnSqrt() 
{
	UpdateData(true);
	m_Formula += "SQRT(";
	UpdateData(false);
}

void CPlotterDlg::OnStar() 
{
	UpdateData(true);
	m_Formula += '*';
	UpdateData(false);
}

void CPlotterDlg::OnTanh() 
{
	UpdateData(true);
	m_Formula += "TANH(";
	UpdateData(false);
}

void CPlotterDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDialog::OnKeyDown(nChar, nRepCnt,nFlags);
}
