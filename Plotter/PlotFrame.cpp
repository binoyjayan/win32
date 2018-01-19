// PlotFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Plotter.h"
#include "PlotFrame.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlotFrame

IMPLEMENT_DYNCREATE(CPlotFrame, CFrameWnd)

CPlotFrame::CPlotFrame()
{
	CString wndclass;
	HBRUSH mybrush=::CreateSolidBrush(RGB(0,0,0));
	wndclass=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,mybrush,0);
	Create(wndclass,"Expression Evaluator and Plotter",WS_OVERLAPPEDWINDOW,rectDefault,0,0/*MAKEINTRESOURCE(IDR_MENU1)*/);
	busy = 0;
}

CPlotFrame::~CPlotFrame()
{
}


BEGIN_MESSAGE_MAP(CPlotFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CPlotFrame)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotFrame message handlers

int CPlotFrame::PlotGraph(CDC *pdc)
{
	InitializeScreen(pdc);
	int px,py;
	double x,y;
	for(x=sc.low;x<sc.up;x+=sc.sharp)
	{
		y = p.Evaluate(x);
		px = int(x * cos(sc.xrad)*sc.zoom * sc.freq)+sc.xshift;
		py = int(y * cos(sc.yrad)*sc.zoom * sc.ampl)+sc.yshift;
		pdc->SetPixel(px,py,RGB(255,0,0));
	}
	return 1;	
}
void CPlotFrame::OnClose()
{
	ShowWindow(SW_HIDE);
}
void CPlotFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	PlotGraph(&dc);
}
int CPlotFrame::Plot(CParse par)
{
	p = par;
	ResetValues();
	Invalidate();
	return 1;
}
void CPlotFrame::InitializeScreen(CDC *pdc)
{
	int i;
	CRect r;
	CPen pen;
	GetClientRect(&r);

	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	pdc->SelectObject(&pen);
	for(i = m_Origin.x;i<r.right;i+=36)
	{
		pdc->MoveTo(i,0);
		pdc->LineTo(i,r.bottom);
	}
	for(i = m_Origin.x;i>r.left;i-=36)
	{
		pdc->MoveTo(i,0);
		pdc->LineTo(i,r.bottom);
	}
	for(i = m_Origin.y;i<r.bottom;i+=36)
	{
		pdc->MoveTo(0,i);
		pdc->LineTo(r.right,i);
	}
	for(i = m_Origin.y;i>r.top;i-=36)
	{
		pdc->MoveTo(0,i);
		pdc->LineTo(r.right,i);
	}

	pdc->SelectStockObject(WHITE_PEN);
	
	pdc->SetBkMode(TRANSPARENT);
	pdc->SetTextColor(RGB(0,255,255));
	pdc->TextOut(10,10,"Scale x : 1 division = 1 unit");	

	pdc->MoveTo(0,m_Origin.y);
	pdc->LineTo(r.right,m_Origin.y);
	pdc->MoveTo(m_Origin.x,0);
	pdc->LineTo(m_Origin.x,r.bottom);
	pdc->SetMapMode(MM_LOMETRIC);
	pdc->SetViewportOrg(m_Origin.x,m_Origin.y);//Change origin to this position
	pen.DeleteObject();
}
void CPlotFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CPlotRangeDlg dlg(this);
	if(busy)
		return;
	switch(nChar)
	{
	default:
		busy = 0;
		return;
	case 0x52:
		dlg.SetPlotRange(sc.low,sc.up);
		if(dlg.DoModal() == IDOK)
			dlg.GetPlotRange(sc.low,sc.up);
		break;
	case VK_DELETE:
		if(GetKeyState(VK_CONTROL)<0)
			sc.ampl--;
		else
			sc.ampl -= 0.1;
		break;
	case VK_INSERT:
		if(GetKeyState(VK_CONTROL)<0)
			sc.ampl++;
		else
			sc.ampl += 0.1;
		break;
	case VK_ESCAPE:
		ResetValues();
		break;
	case VK_LEFT:
		if(GetKeyState(VK_CONTROL)<0)
			sc.xshift-=15;
		else
			sc.xshift--;
		break;
	case VK_RIGHT:
		if(GetKeyState(VK_CONTROL)<0)
			sc.xshift+=15;
		else
			sc.xshift++;
		break;
	case VK_UP:
		if(GetKeyState(VK_CONTROL)<0)
			sc.yshift+=10;
		else
			sc.yshift++;
		break;
	case VK_DOWN:
		if(GetKeyState(VK_CONTROL)<0)
			sc.yshift-=10;
		else
			sc.yshift--;
		break;
	case VK_HOME:
		if(GetKeyState(VK_CONTROL)<0)
			sc.zoom+=10;
		else
			sc.zoom++;
		break;
	case VK_END:
		if(GetKeyState(VK_CONTROL)<0)
			sc.zoom-=10;
		else
			sc.zoom--;
		break;
	case VK_NEXT:
		if(GetKeyState(VK_CONTROL)<0)
			sc.freq+=0.1;
		else
			sc.freq+=0.01;
		break;
	case VK_PRIOR:
		if(GetKeyState(VK_CONTROL)<0)
			sc.freq-=0.1;
		else
			sc.freq-=0.01;
		break;
	case 221:  //']'			
		if(sc.sharp <= 0.00001 && MessageBox("Going beyond that would be so time consuming. Do you wannt to continue?","Warning!",MB_YESNO)==IDNO)
			return;
		if(GetKeyState(VK_CONTROL)<0)
			sc.sharp/=5;
		else
			sc.sharp/=1.2;
		break;
	case 219:  //'['
		if(sc.sharp > 2)
			return;
		if(GetKeyState(VK_CONTROL)<0)
			sc.sharp*=5;
		else
			sc.sharp*=1.2;
		break;
	case 0x58: //Rotate over x axis
		if(GetKeyState(VK_CONTROL)<0)
			sc.yrad+=0.1;
		else
			sc.yrad+=0.01;
		break;
	case 0x59: //Rotate over y axis
		if(GetKeyState(VK_CONTROL)<0)
			sc.xrad+=0.1;
		else
			sc.xrad+=0.01;
		break;
	}
	Invalidate();
	busy = 0;
}
void CPlotFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
}
void CPlotFrame::ResetValues()
{
	sc.ampl   = 1;
	sc.sharp  = 0.0007;
	sc.xshift = 0;
	sc.yshift = 0;
	sc.zoom   = 112;
	sc.freq   = 1;
	sc.ampl   = 1;
	sc.low    = -10;
	sc.up     = 10;
	sc.xrad	  = 0;
	sc.yrad   = 0;
}

void CPlotFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(nFlags & MK_LBUTTON)
	{

	}
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CPlotFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CPlotFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_Origin.x = point.x;
	m_Origin.y = point.y;
	Invalidate();
}

int CPlotFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CRect r;
	GetClientRect(&r);
	m_Origin.x = (r.right - r.left)/2;
	m_Origin.y = (r.bottom - r.top)/2;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CPlotFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(zDelta < 0)
	{
		if(GetKeyState(VK_CONTROL)<0)
			sc.zoom+=15;
		else
			sc.zoom+=2;
	}
	else
	{
		if(GetKeyState(VK_CONTROL)<0)
			sc.zoom-=15;
		else
			sc.zoom-=2;
	}
	Invalidate();
	return CFrameWnd::OnMouseWheel(nFlags, zDelta, pt);
}
