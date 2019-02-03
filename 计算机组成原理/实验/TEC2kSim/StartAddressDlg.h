#if !defined(AFX_STARTADDRESSDLG_H__9A4B0D4A_557C_4EEE_96D6_918C62C26680__INCLUDED_)
#define AFX_STARTADDRESSDLG_H__9A4B0D4A_557C_4EEE_96D6_918C62C26680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartAddressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartAddressDlg dialog

class CStartAddressDlg : public CDialog
{
// Construction
public:
	CStartAddressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartAddressDlg)
	enum { IDD = IDD_START_ADDRESS_DIALOG };
	CString	m_AddressEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartAddressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStartAddressDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTADDRESSDLG_H__9A4B0D4A_557C_4EEE_96D6_918C62C26680__INCLUDED_)
