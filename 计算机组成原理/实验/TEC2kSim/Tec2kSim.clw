; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSaveDataDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tec2kSim.h"
LastPage=0

ClassCount=7
Class1=CTec2kSimApp
Class2=CTec2kSimDoc
Class3=CTec2kSimView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDD_START_ADDRESS_DIALOG
Resource3=IDD_PROPPAGE_MEDIUM (English (U.S.))
Resource4=IDD_PROPPAGE_SMALL (English (U.S.))
Class6=CStartAddressDlg
Resource5=IDR_MAINFRAME
Class7=CSaveDataDlg
Resource6=IDD_SAVE_DATA

[CLS:CTec2kSimApp]
Type=0
HeaderFile=Tec2kSim.h
ImplementationFile=Tec2kSim.cpp
Filter=N

[CLS:CTec2kSimDoc]
Type=0
HeaderFile=Tec2kSimDoc.h
ImplementationFile=Tec2kSimDoc.cpp
Filter=N

[CLS:CTec2kSimView]
Type=0
HeaderFile=Tec2kSimView.h
ImplementationFile=Tec2kSimView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CTec2kSimView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_FILE_STOP




[CLS:CAboutDlg]
Type=0
HeaderFile=Tec2kSim.cpp
ImplementationFile=Tec2kSim.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_TEC16
Command2=ID_FILE_TEC8
Command3=ID_FILE_START_MONITOR
Command4=ID_FILE_LOAD_PROGRAM
Command5=ID_FILE_RUN_PROGRAM
Command6=ID_FILE_STOP
Command7=ID_FILE_LOAD_DATA
Command8=ID_FILE_SAVE_DATA
Command9=ID_APP_EXIT
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_TEC16
Command2=ID_FILE_TEC8
Command3=ID_FILE_LOAD_PROGRAM
Command4=ID_FILE_RUN_PROGRAM
Command5=ID_FILE_START_MONITOR
Command6=ID_FILE_STOP
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_TEC16
Command2=ID_FILE_TEC8
Command3=ID_FILE_START_MONITOR
Command4=ID_FILE_LOAD_PROGRAM
Command5=ID_FILE_RUN_PROGRAM
Command6=ID_FILE_STOP
Command7=ID_FILE_LOAD_DATA
Command8=ID_FILE_SAVE_DATA
Command9=ID_APP_ABOUT
CommandCount=9

[DLG:IDD_PROPPAGE_MEDIUM (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_SMALL (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_START_ADDRESS_DIALOG]
Type=1
Class=CStartAddressDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_ADDRESS_EDIT,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[CLS:CStartAddressDlg]
Type=0
HeaderFile=StartAddressDlg.h
ImplementationFile=StartAddressDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_ADDRESS_EDIT

[DLG:IDD_SAVE_DATA]
Type=1
Class=CSaveDataDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,button,1342177287
Control3=IDC_SAVE_DATA_DEFAULT,button,1342373897
Control4=IDC_SAVE_DATA_RESET,button,1342242825
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SAVE_START_EDIT,edit,1350633600
Control7=IDC_STATIC,static,1342308352
Control8=IDC_SAVE_LEN_EDIT,edit,1350633600
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816

[CLS:CSaveDataDlg]
Type=0
HeaderFile=SaveDataDlg.h
ImplementationFile=SaveDataDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSaveDataDlg
VirtualFilter=dWC

