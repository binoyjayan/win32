; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPlotRangeDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Plotter.h"

ClassCount=5
Class1=CPlotterApp
Class2=CPlotterDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CPlotFrame
Resource3=IDD_PLOTTER_DIALOG
Class5=CPlotRangeDlg
Resource4=IDD_PLOTRANGE

[CLS:CPlotterApp]
Type=0
HeaderFile=Plotter.h
ImplementationFile=Plotter.cpp
Filter=N

[CLS:CPlotterDlg]
Type=0
HeaderFile=PlotterDlg.h
ImplementationFile=PlotterDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_VARX

[CLS:CAboutDlg]
Type=0
HeaderFile=PlotterDlg.h
ImplementationFile=PlotterDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[DLG:IDD_PLOTTER_DIALOG]
Type=1
Class=CPlotterDlg
ControlCount=31
Control1=IDC_FORMULA,edit,1350631552
Control2=IDC_PLOT,button,1342242817
Control3=IDC_SIN,button,1342242816
Control4=IDC_COS,button,1342242816
Control5=IDC_TAN,button,1342242816
Control6=IDC_SINH,button,1342242816
Control7=IDC_COSH,button,1342242816
Control8=IDC_TANH,button,1342242816
Control9=IDC_LOG,button,1342242816
Control10=IDC_ABS,button,1342242816
Control11=IDC_SQRT,button,1342242816
Control12=IDC_NO0,button,1342242816
Control13=IDC_NO1,button,1342242816
Control14=IDC_NO2,button,1342242816
Control15=IDC_NO3,button,1342242816
Control16=IDC_NO4,button,1342242816
Control17=IDC_NO5,button,1342242816
Control18=IDC_NO6,button,1342242816
Control19=IDC_NO7,button,1342242816
Control20=IDC_NO8,button,1342242816
Control21=IDC_NO9,button,1342242816
Control22=IDC_PERIOD,button,1342242816
Control23=IDC_PLUS,button,1342242816
Control24=IDC_MINUS,button,1342242816
Control25=IDC_STAR,button,1342242816
Control26=IDC_DIVIDE,button,1342242816
Control27=IDC_VARX,button,1342242816
Control28=IDC_LEFTPAREN,button,1342242816
Control29=IDC_RIGHTPAREN,button,1342242816
Control30=IDC_POWER,button,1342242816
Control31=IDC_EXP,button,1342242816

[CLS:CPlotFrame]
Type=0
HeaderFile=PlotFrame.h
ImplementationFile=PlotFrame.cpp
BaseClass=CFrameWnd
Filter=T
VirtualFilter=fWC
LastObject=CPlotFrame

[DLG:IDD_PLOTRANGE]
Type=1
Class=CPlotRangeDlg
ControlCount=7
Control1=IDC_LOWERRANGE,edit,1350631552
Control2=IDC_UPPERRANGE,edit,1350639744
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287

[CLS:CPlotRangeDlg]
Type=0
HeaderFile=PlotRangeDlg.h
ImplementationFile=PlotRangeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPlotRangeDlg
VirtualFilter=dWC

