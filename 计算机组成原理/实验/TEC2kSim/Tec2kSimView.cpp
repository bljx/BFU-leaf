// Tec2kSimView.cpp : implementation of the CTec2kSimView class
//

#include "stdafx.h"
#include "Tec2kSim.h"

#include "Tec2kSimDoc.h"
#include "Tec2kSimView.h"
#include "StartAddressDlg.h"
#include "SaveDataDlg.h"
#include "Tec2kVM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimView

IMPLEMENT_DYNCREATE(CTec2kSimView, CView)

BEGIN_MESSAGE_MAP(CTec2kSimView, CView)
	//{{AFX_MSG_MAP(CTec2kSimView)
	ON_WM_SIZE()
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_TEC16, OnFileTec16)
	ON_UPDATE_COMMAND_UI(ID_FILE_TEC16, OnUpdateFileTec16)
	ON_COMMAND(ID_FILE_TEC8, OnFileTec8)
	ON_UPDATE_COMMAND_UI(ID_FILE_TEC8, OnUpdateFileTec8)
	ON_COMMAND(ID_FILE_START_MONITOR, OnFileStartMonitor)
	ON_UPDATE_COMMAND_UI(ID_FILE_START_MONITOR, OnUpdateFileStartMonitor)
	ON_COMMAND(ID_FILE_LOAD_PROGRAM, OnFileLoadProgram)
	ON_COMMAND(ID_FILE_RUN_PROGRAM, OnFileRunProgram)
	ON_UPDATE_COMMAND_UI(ID_FILE_RUN_PROGRAM, OnUpdateFileRunProgram)
	ON_COMMAND(ID_FILE_STOP, OnFileStop)
	ON_UPDATE_COMMAND_UI(ID_FILE_STOP, OnUpdateFileStop)
	ON_COMMAND(ID_FILE_LOAD_DATA, OnFileLoadData)
	ON_UPDATE_COMMAND_UI(ID_FILE_LOAD_DATA, OnUpdateFileLoadData)
	ON_COMMAND(ID_FILE_SAVE_DATA, OnFileSaveData)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_DATA, OnUpdateFileSaveData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimView construction/destruction

CTec2kSimView::CTec2kSimView()
{
	pApp = AfxGetApp();
	bRunning = bMonitor = false;
	bTransferingData = false;
	pTransferFile = NULL;
	LastAddress = 0;
	RowCount = 25;
	ColCount = 80;
	BackBrush.CreateSolidBrush(TEC2K_CONSOLE_BACK_COLOR);
	CursorPen.CreatePen(PS_SOLID, 1, TEC2K_CONSOLE_TEXT_COLOR ^
		TEC2K_CONSOLE_BACK_COLOR);
	pConsole = new CTec2kConsole(this, ColCount, RowCount);
	VMType = 0;
	ToDoNext = TEC2K_TODO_START_VM16;
	ToDoNotify();
}

CTec2kSimView::~CTec2kSimView()
{
	delete pConsole;
}

BOOL CTec2kSimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimView drawing

void CTec2kSimView::OnDraw(CDC* pDC)
{
	CTec2kSimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect ClipRect = ((CPaintDC *)pDC)->m_ps.rcPaint;
	pDC->FillRect(&ClipRect, &BackBrush);
	pDC->SelectObject(&TextFont);
	pDC->SetBkColor(TEC2K_CONSOLE_BACK_COLOR);
	pDC->SetTextColor(TEC2K_CONSOLE_TEXT_COLOR);
	int CharL = ClipRect.left / FontWidth;
	int CharT = ClipRect.top / FontHeight;
	int CharW = (ClipRect.right - 1) / FontWidth;
	int CharB = (ClipRect.bottom - 1) / FontHeight;
	CharW = (CharW < ColCount) ? (CharW - CharL + 1) : (ColCount - CharL);
	if (CharB >= RowCount)
		CharB = RowCount - 1;
	char *pALine = pConsole->GetScreenText() + (CharT * ColCount) + CharL;
	int x = CharL * FontWidth;
	int y = CharT * FontHeight;
	for (int i = CharT; i <= CharB; i++)
	{	
		pDC->TextOut(x, y, pALine, CharW);
		pALine += ColCount;
		y += FontHeight;
	}
	if (pConsole->IsCursorVisible())
		UpdateCursor(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimView diagnostics

#ifdef _DEBUG
void CTec2kSimView::AssertValid() const
{
	CView::AssertValid();
}

void CTec2kSimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTec2kSimDoc* CTec2kSimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTec2kSimDoc)));
	return (CTec2kSimDoc*)m_pDocument;
}
#endif //_DEBUG

CString CTec2kSimView::GetHexStr(int Value)
{
	CString s;
	s.Format("%04xh", Value);
	return s;
}

int CTec2kSimView::GetHexValue(CString s)
{
	int Value;
	s.MakeLower();
	if (s.Left(2) == "0x")
		sscanf((const char *)(LPCTSTR)(s.Right(s.GetLength() - 2)), 
			"%x", &Value);
	else if (s.Right(1) == "h")
		sscanf((const char *)(LPCTSTR)(s.Left(s.GetLength() - 1)),
			"%x", &Value);
	else 
		Value = atoi((const char *)(LPCTSTR)s);
	return Value;
}

/////////////////////////////////////////////////////////////////////////////
// CTec2kSimView message handlers

void CTec2kSimView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	FontHeight = cy / RowCount;
	if (FontHeight < 2) 
		FontHeight = 2;
	CClientDC dc(this);
	CString s('0', ColCount);
	LOGFONT lf;
	lf.lfWidth = 0;
	lf.lfEscapement = 0; 
	lf.lfOrientation = 0; 
	lf.lfWeight = FW_NORMAL; 
	lf.lfItalic = FALSE; 
	lf.lfUnderline = FALSE;  
	lf.lfStrikeOut = FALSE; 
	lf.lfCharSet = GB2312_CHARSET; 
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS; 
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS; 
	lf.lfQuality = DEFAULT_QUALITY; 
	lf.lfPitchAndFamily = DEFAULT_PITCH; 
	strcpy(lf.lfFaceName, "宋体"); 
	for (;;)
	{
		lf.lfHeight = FontHeight;
		TextFont.DeleteObject();
		TextFont.CreateFontIndirect(&lf);
		dc.SelectObject(TextFont);
		FontWidth = dc.GetTextExtent(s).cx;
		if ((FontWidth <= cx) || (FontHeight <= 2))
			break;
		FontHeight--;
	}
	s.Delete(0);
	FontWidth -= dc.GetTextExtent(s).cx;
}

void CTec2kSimView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    pConsole->KeyPressed(nChar);
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CTec2kSimView::OnTimer(UINT nIDEvent)
{
	pConsole->FlashCursor();

	CView::OnTimer(nIDEvent);
}

void CTec2kSimView::OnFileTec16() 
{
	if (VMType == 16) return;

	ToDoNext = TEC2K_TODO_START_VM16;
	if (bMonitor || bRunning)
		pVM->StopAndFree();
	else
	{
		delete pVM;
		ToDoNotify();
	}
}

void CTec2kSimView::OnUpdateFileTec16(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(VMType == 16);
}

void CTec2kSimView::OnFileTec8() 
{
	if (VMType == 8) return;

	ToDoNext = TEC2K_TODO_START_VM8;
	if (bMonitor || bRunning)
		pVM->StopAndFree();
	else
	{
		delete pVM;
		ToDoNotify();
	}
}

void CTec2kSimView::OnUpdateFileTec8(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(VMType == 8);
}

void CTec2kSimView::OnFileStartMonitor() 
{
	CString FileName;
	::GetModuleFileName(0, FileName.GetBuffer(260), 260);
	FileName.ReleaseBuffer();
	FileName = FileName.Left(FileName.ReverseFind('\\') + 1) + 
		pVM->GetMonitorFileName();
	int Length;
	char *Buffer;
	TRY
	{
		CFile f(FileName, CFile::modeRead);
		Length = f.GetLength();
		Buffer = new char[Length];
		f.Read(Buffer, Length);
		f.Close();
	}
	CATCH(CFileException, pEx)
	{
		MessageBox("监控程序目标代码文件读取失败。", "启动监控程序", 
			MB_ICONWARNING | MB_OK);
		return;
	}
	END_CATCH
	pVM->WriteToMemory(0, Length / pVM->GetWordSize(), Buffer);
	delete []Buffer;
	bMonitor = true;
	pConsole->ClearScreen();
	pVM->Run(0);
	bMonitor = false;
}

void CTec2kSimView::OnUpdateFileStartMonitor(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!bMonitor && !bRunning);
}

void CTec2kSimView::OnFileLoadProgram() 
{
	char *Filter = "TEC-2000 目标代码(*.cod)|*.cod|所有文件(*.*)|*.*||";
    CFileDialog dlg(TRUE, ".cod", NULL, 0, Filter);
	if (dlg.DoModal() == IDOK)
	{
		TRY
		{
			CFile f(dlg.GetFileName(), CFile::modeRead);
			unsigned short StartAddr, Length, ByteCount;
			f.Read(&StartAddr, 1);
			f.Read(&StartAddr, 2);
			f.Read(&Length, 2);
			ByteCount = Length * pVM->GetWordSize();
			char *Buffer = new char[ByteCount];
			f.Read(Buffer, ByteCount);
			f.Close();
			pVM->WriteToMemory(StartAddr, Length, Buffer);
			delete []Buffer;
			LastAddress = StartAddr;
			CString s;
			s.Format("代码已成功装入，\n起始地址为 " + GetHexStr(LastAddress));
			MessageBox(s, "装入代码", MB_ICONINFORMATION | MB_OK);
		}
		CATCH(CFileException, pEx)
		{
			MessageBox("目标代码文件读取失败。", "装入代码", 
				MB_ICONWARNING | MB_OK);
		}
		END_CATCH
	}
}

void CTec2kSimView::OnFileRunProgram() 
{
    CStartAddressDlg theDlg;
	theDlg.m_AddressEdit.Format("%04xh", LastAddress);
	if  (theDlg.DoModal() == IDOK)
	{
		LastAddress = GetHexValue(theDlg.m_AddressEdit);
		bRunning = true;
		pConsole->ClearScreen();
		pVM->SetStubAndRun(LastAddress);
		bRunning = false;
	}
}

void CTec2kSimView::OnUpdateFileRunProgram(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!bMonitor && !bRunning);
}

void CTec2kSimView::OnFileStop() 
{
	pVM->Stop();	
}

void CTec2kSimView::OnUpdateFileStop(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(bMonitor || bRunning);
}

void CTec2kSimView::OnFileLoadData() 
{
	char *Filter = "TEC-2000 代码文件(*.cod)|*.cod|所有文件(*.*)|*.*||";
    CFileDialog dlg(TRUE, ".cod", NULL, 0, Filter);
	if (dlg.DoModal() == IDOK)
	{
		TRY
		{
			pTransferFile = new CFile(dlg.GetFileName(), CFile::modeRead);
		}
		CATCH(CFileException, pEx)
		{
			MessageBox("代码文件读取失败。", "发送文件", 
				MB_ICONWARNING | MB_OK);
			return;
		}
		END_CATCH
		pStatusBar = GetParentFrame()->GetMessageBar();
		pTransferTypeStr = "发送";
		bTransferingData = true;
		pVM->MonReceiveData();
	}
}

void CTec2kSimView::OnUpdateFileLoadData(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(bMonitor && !bTransferingData);
}

void CTec2kSimView::OnFileSaveData() 
{
	int Start, Len;
	pVM->GetSendStartLen(&Start, &Len);
	CSaveDataDlg saveDataDlg(GetHexStr(Start), GetHexStr(Len));
	if (saveDataDlg.DoModal() != IDOK)
		return;

	pVM->SetSendStartLen(GetHexValue(saveDataDlg.m_StartStr), 
		GetHexValue(saveDataDlg.m_LenStr));
	char *Filter = "TEC-2000 代码文件(*.cod)|*.cod|所有文件(*.*)|*.*||";
    CFileDialog fileDlg(FALSE, ".cod", NULL, OFN_OVERWRITEPROMPT, Filter);
	if (fileDlg.DoModal() == IDOK)
	{
		TRY
		{
			pTransferFile = new CFile(fileDlg.GetFileName(), 
				CFile::modeWrite | CFile::modeCreate);
		}
		CATCH(CFileException, pEx)
		{
			MessageBox("代码文件保存失败。", "接收文件", 
				MB_ICONWARNING | MB_OK);
			return;
		}
		END_CATCH
		pStatusBar = GetParentFrame()->GetMessageBar();
		pTransferTypeStr = "接收";
		bTransferingData = true;
		pVM->MonSendData();
	}
}

void CTec2kSimView::OnUpdateFileSaveData(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(bMonitor && !bTransferingData);
}

void CTec2kSimView::UpdateAChar(int RowPos, int ColPos, char aChar)
{
	CClientDC dc(this);
	dc.SelectObject(&TextFont);
	dc.SetBkColor(TEC2K_CONSOLE_BACK_COLOR);
	dc.SetTextColor(TEC2K_CONSOLE_TEXT_COLOR);
	dc.TextOut(ColPos * FontWidth, RowPos * FontHeight, aChar);
}

void CTec2kSimView::ScrollALine()
{
	ScrollWindow(0, -FontHeight);
}

void CTec2kSimView::ToDoNotify()
{
	switch (ToDoNext)
	{
	case TEC2K_TODO_START_VM16:
		pVM = new CTec2kVM16(pConsole);
		VMType = 16;
		break;
	case TEC2K_TODO_START_VM8:
		pVM = new CTec2kVM8(pConsole);
		VMType = 8;
		break;
	case TEC2K_TODO_EXIT_APP:
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		break;
	}
}

void CTec2kSimView::UpdateCursor(CDC *pDC)
{
	int OldROP2 = pDC->SetROP2(R2_XORPEN);
	pDC->SelectObject(CursorPen);
	CRect rc;
	rc.left = pConsole->GetColPos() * FontWidth;
	rc.right = rc.left + FontWidth;
	rc.bottom = (pConsole->GetRowPos() + 1) * FontHeight;
	rc.top = rc.bottom - 2;
	pDC->Rectangle(&rc);
	pDC->SetROP2(OldROP2); 
}

void CTec2kSimView::UpdateCursor()
{
	CClientDC dc(this);
	UpdateCursor(&dc);
}

void CTec2kSimView::EnableCursorTimer()
{
	SetTimer(TEC2K_CURSOR_TIMER_ID, TEC2K_CURSOR_TIMER_INTERVAL, NULL);
}

void CTec2kSimView::DisableCursorTimer()
{
	KillTimer(TEC2K_CURSOR_TIMER_ID);
}

void CTec2kSimView::ClearScreen()
{
	Invalidate(false);
}

void CTec2kSimView::DoMessageLoop()
{
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;

	while (bIdle)
	{
		// call OnIdle while in bIdle state
		if (!pApp->OnIdle(lIdleCount++))
			bIdle = FALSE; // assume "no idle" state
	}

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (msg.message == WM_QUIT)
			break;
		else
			pApp->PumpMessage();
	} 
}

bool CTec2kSimView::TryStopVMAndExit()
{
	bool IsRunning = bMonitor || bRunning;
	if (IsRunning)
	{
		ToDoNext = TEC2K_TODO_EXIT_APP;
		pVM->StopAndFree();
		pVM = NULL;
	}
	else if (pVM)
		delete pVM;
	return !IsRunning;
}

unsigned char CTec2kSimView::MonReadByte()
{
	unsigned char Value;
	TRY
	{
		pTransferFile->Read(&Value, 1);
	}
	CATCH(CFileException, pEx)
	{
		Value = 0;
	}
	END_CATCH
	return Value;
}

void CTec2kSimView::MonWriteByte(unsigned char Value)
{
	TRY
	{
		pTransferFile->Write(&Value, 1);
	}
	CATCH(CFileException, pEx)
	{
	}
	END_CATCH
}

void CTec2kSimView::ShowTransferInfo(int Index, int Count, int Percent)
{
	CString s;
	if (Percent == 100)
		s.Format("%s文件完成", pTransferTypeStr);
	else
		s.Format("已%s %d 字节，完成总长 %d 字节的 %d%%", pTransferTypeStr, 
			Index, Count, Percent);
	pStatusBar->SetWindowText(s);
}

void CTec2kSimView::TransferFinished()
{
	if (bTransferingData)
	{
		TRY
		{
			pTransferFile->Close();
		}
		CATCH(CFileException, pEx)
		{
		}
		END_CATCH
		delete pTransferFile;
		bTransferingData = false;
	}
}

