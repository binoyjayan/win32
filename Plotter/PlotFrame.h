#if !defined(AFX_PLOTFRAME_H__D6931003_28CC_4395_AE09_7108C7EFA97E__INCLUDED_)
#define AFX_PLOTFRAME_H__D6931003_28CC_4395_AE09_7108C7EFA97E__INCLUDED_

#include "Parse.h"	// Added by ClassView
#include "PlotRangeDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlotFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlotFrame frame
struct SCALE
{
	double sharp;
	double xrad,yrad;
	double ampl,freq;//stretch along x/y directions
	int xshift,yshift;
	int low,up;
	int zoom;
	SCALE()
	{
		ampl = 1;
		sharp = 0.0007;
		xshift = yshift = 0;
		freq = ampl = 1;
		low = -10;
		up  = 10;
		zoom = 112;
		xrad = 0;
		yrad = 0;
	}
};
class CPlotFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPlotFrame)
public:
	CPlotFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CParse p;
	CPoint m_Origin;
	SCALE sc;
	int busy;
// Operations
public:

	void ResetValues();
	void InitializeScreen(CDC *pdc);
	int Plot(CParse p);
	int PlotGraph(CDC *);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlotFrame();

	// Generated message map functions
	//{{AFX_MSG(CPlotFrame)
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTFRAME_H__D6931003_28CC_4395_AE09_7108C7EFA97E__INCLUDED_)
