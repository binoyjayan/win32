// WMPlay.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WMPlay.h"
#include "WMPlayDlg.h"
#include ".\wmplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWMPlayApp

BEGIN_MESSAGE_MAP(CWMPlayApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
END_MESSAGE_MAP()


// CWMPlayApp construction

CWMPlayApp::CWMPlayApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CWMPlayApp object

CWMPlayApp theApp;


// CWMPlayApp initialization

BOOL CWMPlayApp::InitInstance()
{	
	CWnd * check = CFrameWnd::FindWindow("#32770", "WMPlay");
	if(check)
	{
		check->SetForegroundWindow();
		check->ShowWindow(SW_NORMAL);
		
		if(__argc == 2)//new file is being opened
		{
				if (!OpenClipboard(NULL))
					return 0; //exit
				if(!EmptyClipboard())
					return 0; //exit
				HANDLE hData;
				hData = GlobalAlloc(GHND, 240);
				char *s = (char*) GlobalLock(hData);//fix memory
				strcpy(s, __argv[1]);				
				GlobalUnlock(hData);//unfix memory

				if(::SetClipboardData(CF_TEXT, hData ) == NULL )
				{
					CloseClipboard();
					return 0;
				}
				GlobalFree(hData);
				CloseClipboard();
				SendMessage(check->m_hWnd, WM_USER + 77, 0, 0);
		}
		return 0;
	}
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	CWMPlayDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();	
	return FALSE;
}


void CWMPlayApp::OnFileExit()
{
	exit(0);
}

