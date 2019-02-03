// Tec2kSimView.h : interface of the CTec2kSimView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEC2KSIMVIEW_H__FB823168_8E7A_4C97_A8D6_C59AE501E104__INCLUDED_)
#define AFX_TEC2KSIMVIEW_H__FB823168_8E7A_4C97_A8D6_C59AE501E104__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TEC2K_TODO_NONE					0
#define TEC2K_TODO_START_VM16			1
#define TEC2K_TODO_START_VM8			2
#define TEC2K_TODO_EXIT_APP				3

#define TEC2K_CONSOLE_TEXT_COLOR			RGB(255, 255, 255)
#define TEC2K_CONSOLE_BACK_COLOR			RGB(0, 0, 128)

#define TEC2K_CURSOR_TIMER_ID			10000
#define TEC2K_CURSOR_TIMER_INTERVAL		500

class CTec2kConsole;
class CTec2kVM;

class CTec2kSimView : public CView
{
protected: // create from serialization only
	CTec2kSimView();
	DECLARE_DYNCREATE(CTec2kSimView)

// Attributes
public:
	CTec2kSimDoc* GetDocument();

// Operations
public:
	void UpdateAChar(int RowPos, int ColPos, char aChar);
	void ScrollALine();
	void ToDoNotify();
	void UpdateCursor(CDC *pDC);
	void UpdateCursor();
	void EnableCursorTimer();
	void DisableCursorTimer();
	void ClearScreen();
	void DoMessageLoop();
	bool TryStopVMAndExit();
	unsigned char MonReadByte();
	void MonWriteByte(unsigned char Value);
	void ShowTransferInfo(int Index, int Count, int Percent);
	void TransferFinished();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTec2kSimView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTec2kSimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int RowCount, ColCount;
	int FontWidth, FontHeight;
	CBrush BackBrush;
	CPen CursorPen;
	CFont TextFont;
	CTec2kVM *pVM;
	CTec2kConsole *pConsole;
	bool bMonitor;
	bool bRunning;
	unsigned short LastAddress;
	int ToDoNext;
	int VMType;
	CWinApp *pApp;
	CWnd *pStatusBar;
	CFile *pTransferFile;
	bool bTransferingData;
	char *pTransferTypeStr;

	static CString GetHexStr(int Value);
	static int GetHexValue(CString s);

// Generated message map functions
protected:
	//{{AFX_MSG(CTec2kSimView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFileTec16();
	afx_msg void OnUpdateFileTec16(CCmdUI* pCmdUI);
	afx_msg void OnFileTec8();
	afx_msg void OnUpdateFileTec8(CCmdUI* pCmdUI);
	afx_msg void OnFileStartMonitor();
	afx_msg void OnUpdateFileStartMonitor(CCmdUI* pCmdUI);
	afx_msg void OnFileLoadProgram();
	afx_msg void OnFileRunProgram();
	afx_msg void OnUpdateFileRunProgram(CCmdUI* pCmdUI);
	afx_msg void OnFileStop();
	afx_msg void OnUpdateFileStop(CCmdUI* pCmdUI);
	afx_msg void OnFileLoadData();
	afx_msg void OnUpdateFileLoadData(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveData();
	afx_msg void OnUpdateFileSaveData(CCmdUI* pCmdUI);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

typedef CTec2kSimView CTec2kConPanel;

#ifndef _DEBUG  // debug version in Tec2kSimView.cpp
inline CTec2kSimDoc* CTec2kSimView::GetDocument()
   { return (CTec2kSimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEC2KSIMVIEW_H__FB823168_8E7A_4C97_A8D6_C59AE501E104__INCLUDED_)
