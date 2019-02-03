// Tec2kSimDoc.cpp : implementation of the CTec2kSimDoc class
//

#include "stdafx.h"
#include "Tec2kSim.h"

#include "Tec2kSimDoc.h"
#include "Tec2kSimView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimDoc

IMPLEMENT_DYNCREATE(CTec2kSimDoc, CDocument)

BEGIN_MESSAGE_MAP(CTec2kSimDoc, CDocument)
	//{{AFX_MSG_MAP(CTec2kSimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimDoc construction/destruction

CTec2kSimDoc::CTec2kSimDoc()
{
	// TODO: add one-time construction code here

}

CTec2kSimDoc::~CTec2kSimDoc()
{
}

BOOL CTec2kSimDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	return ((CTec2kSimView *)(pFrame->GetActiveView()))->TryStopVMAndExit();
}

BOOL CTec2kSimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTec2kSimDoc serialization

void CTec2kSimDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimDoc diagnostics

#ifdef _DEBUG
void CTec2kSimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTec2kSimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimDoc commands
