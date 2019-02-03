// Tec2kSimDoc.h : interface of the CTec2kSimDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEC2KSIMDOC_H__01B7629C_B76E_49AD_8932_D61B3E3248CD__INCLUDED_)
#define AFX_TEC2KSIMDOC_H__01B7629C_B76E_49AD_8932_D61B3E3248CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTec2kSimDoc : public CDocument
{
protected: // create from serialization only
	CTec2kSimDoc();
	DECLARE_DYNCREATE(CTec2kSimDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTec2kSimDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTec2kSimDoc();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTec2kSimDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEC2KSIMDOC_H__01B7629C_B76E_49AD_8932_D61B3E3248CD__INCLUDED_)
