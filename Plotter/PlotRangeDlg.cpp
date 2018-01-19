// PlotRangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Plotter.h"
#include "PlotRangeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlotRangeDlg dialog


CPlotRangeDlg::CPlotRangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlotRangeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlotRangeDlg)
	m_Low = _T("");
	m_High = _T("");
	//}}AFX_DATA_INIT
}


void CPlotRangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlotRangeDlg)
	DDX_Text(pDX, IDC_LOWERRANGE, m_Low);
	DDX_Text(pDX, IDC_UPPERRANGE, m_High);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlotRangeDlg, CDialog)
	//{{AFX_MSG_MAP(CPlotRangeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotRangeDlg message handlers

void CPlotRangeDlg::OnOK() 
{
	UpdateData(true);

	low  = atoi(m_Low);
	high = atoi(m_High);
	
	if((high - low) < 3 || high - low > 100)
	{
		MessageBox("Inconsistent entry. Choose a range between something like -10 to +10 or 0 to 20","Error in input!",MB_ICONINFORMATION);
		return;
	}
	CDialog::OnOK();
}
void CPlotRangeDlg::GetPlotRange(int &l, int &h)
{
	l = low;
	h = high;
}
void CPlotRangeDlg::SetPlotRange(int &l, int &h)
{
	m_Low.Format("%d",l);
	m_High.Format("%d",h);
}
