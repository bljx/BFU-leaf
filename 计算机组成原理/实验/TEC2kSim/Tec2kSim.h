// Tec2kSim.h : main header file for the TEC2KSIM application
//

#if !defined(AFX_TEC2KSIM_H__37A46BD6_D2F7_4778_86E0_7C241235684B__INCLUDED_)
#define AFX_TEC2KSIM_H__37A46BD6_D2F7_4778_86E0_7C241235684B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimApp:
// See Tec2kSim.cpp for the implementation of this class
//

class CTec2kSimApp : public CWinApp
{
public:
	CTec2kSimApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTec2kSimApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTec2kSimApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEC2KSIM_H__37A46BD6_D2F7_4778_86E0_7C241235684B__INCLUDED_)
