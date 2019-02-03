// SaveDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tec2kSim.h"
#include "SaveDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveDataDlg dialog


CSaveDataDlg::CSaveDataDlg(CString& StartStr, CString& LenStr, CWnd* pParent)
	: CDialog(CSaveDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveDataDlg)
	//}}AFX_DATA_INIT
	m_DefaultStartStr = StartStr;
	m_DefaultLenStr = LenStr;
}


void CSaveDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveDataDlg)
	DDX_Control(pDX, IDC_SAVE_DATA_DEFAULT, m_SaveDataDefault);
	DDX_Control(pDX, IDC_SAVE_DATA_RESET, m_SaveDataReset);
	DDX_Control(pDX, IDC_SAVE_START_EDIT, m_SaveStartEdit);
	DDX_Control(pDX, IDC_SAVE_LEN_EDIT, m_SaveLenEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveDataDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveDataDlg)
	ON_BN_CLICKED(IDC_SAVE_DATA_DEFAULT, OnBnClickedSaveDataDefault)
	ON_BN_CLICKED(IDC_SAVE_DATA_RESET, OnBnClickedSaveDataReset)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveDataDlg message handlers

void CSaveDataDlg::OnBnClickedSaveDataDefault()
{
	m_SaveStartEdit.GetWindowText(m_StartStr);
	m_SaveLenEdit.GetWindowText(m_LenStr);
	m_SaveStartEdit.SetWindowText(m_DefaultStartStr);
	m_SaveLenEdit.SetWindowText(m_DefaultLenStr);
	m_SaveStartEdit.SetReadOnly();
	m_SaveLenEdit.SetReadOnly();
}

void CSaveDataDlg::OnBnClickedSaveDataReset()
{
	m_SaveStartEdit.SetWindowText(m_StartStr);
	m_SaveLenEdit.SetWindowText(m_LenStr);
	m_SaveStartEdit.SetReadOnly(false);
	m_SaveLenEdit.SetReadOnly(false);
}

BOOL CSaveDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_SaveDataDefault.SetCheck(BST_CHECKED);
	m_SaveStartEdit.SetWindowText("2000h");
	m_SaveLenEdit.SetWindowText("0800h");
	OnBnClickedSaveDataDefault();
	return TRUE; 
}

void CSaveDataDlg::OnBnClickedOk()
{
	m_SaveStartEdit.GetWindowText(m_StartStr);
	m_SaveLenEdit.GetWindowText(m_LenStr);
	OnOK();
}
