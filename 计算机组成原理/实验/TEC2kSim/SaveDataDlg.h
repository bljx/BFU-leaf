#include "afxwin.h"
#if !defined(AFX_SAVEDATADLG_H__65D06403_4394_40C6_A966_AF10067373D6__INCLUDED_)
#define AFX_SAVEDATADLG_H__65D06403_4394_40C6_A966_AF10067373D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveDataDlg dialog

class CSaveDataDlg : public CDialog
{
// Construction
public:
	CSaveDataDlg(CString& StartStr, CString& LenStr, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveDataDlg)
	enum { IDD = IDD_SAVE_DATA };
	CButton	m_SaveDataDefault;
	CButton m_SaveDataReset;
	CEdit	m_SaveStartEdit;
	CEdit	m_SaveLenEdit;
	//}}AFX_DATA

	CString m_StartStr;
	CString m_LenStr;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveDataDlg)
	afx_msg void OnBnClickedSaveDataDefault();
	afx_msg void OnBnClickedSaveDataReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString m_DefaultStartStr;
	CString m_DefaultLenStr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEDATADLG_H__65D06403_4394_40C6_A966_AF10067373D6__INCLUDED_)
