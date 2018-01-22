; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Crawler.h"
LastPage=0

ClassCount=5
Class1=CCrawlerApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class2=CChildView
Resource2=IDR_MAINFRAME
Class5=CCrawlerDlg
Resource3=IDD_CRAWLING

[CLS:CCrawlerApp]
Type=0
HeaderFile=Crawler.h
ImplementationFile=Crawler.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=C
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_CRAWLERSTATUS




[CLS:CAboutDlg]
Type=0
HeaderFile=Crawler.cpp
ImplementationFile=Crawler.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_STARTCRAWLER
Command2=ID_FILE_STOP_CRAWLING
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_STARTCRAWLER
Command2=ID_FILE_STOP_CRAWLING
Command3=ID_CRAWLERSTATUS
Command4=ID_APP_ABOUT
CommandCount=4

[DLG:IDD_CRAWLING]
Type=1
Class=CCrawlerDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC1,static,1342308352
Control3=IDC_STATIC2,static,1342308352
Control4=IDC_STATIC,button,1342177287

[CLS:CCrawlerDlg]
Type=0
HeaderFile=CrawlerDlg.h
ImplementationFile=CrawlerDlg.cpp
BaseClass=CDialog
Filter=C
VirtualFilter=dWC

