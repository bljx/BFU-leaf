// StartAddressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tec2kSim.h"
#include "StartAddressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartAddressDlg dialog


CStartAddressDlg::CStartAddressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStartAddressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartAddressDlg)
	m_AddressEdit = _T("");
	//}}AFX_DATA_INIT
}


void CStartAddressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartAddressDlg)
	DDX_Text(pDX, IDC_ADDRESS_EDIT, m_AddressEdit);
	DDV_MaxChars(pDX, m_AddressEdit, 6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartAddressDlg, CDialog)
	//{{AFX_MSG_MAP(CStartAddressDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartAddressDlg message handlers
