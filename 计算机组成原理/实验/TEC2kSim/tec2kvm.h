
#if !defined(AFX_TEC2KVM_H__E7EC5D46_7890_4E8D_BCBB_CD9AF095D448__INCLUDED_)
#define AFX_TEC2KVM_H__E7EC5D46_7890_4E8D_BCBB_CD9AF095D448__INCLUDED_

#define MESSAGE_PEEKING_CYCLE		256

enum CConsolePortState { PortDirect, PortCommand, PortData };
enum CConsoleDataType { DataSend, DataReceive };

class CTec2kConsole
{
private:
	CTec2kConPanel *pChildView;
	char *ScreenText;
	int Width, Height;
	int ColPos, RowPos;
	char KeyCode;
	bool HasUnreadKey;
	bool CursorVisible;
	CConsolePortState ConsolePortState;
	CConsoleDataType ConsoleDataType;
	char *TransferCommand;
	unsigned char StartLenBuffer[4];
	size_t WordSize;
	int TransferCount, TransferIndex, LastPercent;
	bool IsTransferCounting;
	unsigned char TransferByte;
	unsigned char LastTransferByte;
    
	void ScrollALine();
	char PortInDirect(int Port);
	void PortOutDirect(int Port, char Value);
	char PortInCommand(int Port);
	void PortOutCommand(int Port, char Value);
	char PortInData(int Port);
	void PortOutData(int Port, char Value);
	void UpdateTransferCount();

public:
	CTec2kConsole(CTec2kConPanel *pView, int theWidth = 80, int theHeight = 25);
	~CTec2kConsole();

	int GetWidth()
		{ return Width; }
	int GetHeight()
		{ return Height; }
	int GetColPos()
		{ return ColPos; }
	int GetRowPos()
		{ return RowPos; }
	char *GetScreenText()
		{ return ScreenText; }
	bool IsCursorVisible()
		{ return CursorVisible; }
	
	void KeyPressed(char Key);
	char PortIn(int Port);
	void PortOut(int Port, char Value);
	void DoMessageLoop();
	void ClearScreen();
	void ToDoNotify();
	void EnableCursor();
	void DisbleCursor();
	void FlashCursor();
	void DirectMode();
	void TransferMode(CConsoleDataType DataType, char *Command, 
		size_t WordSize_);
};

class CTec2kVM
{
protected:
	CTec2kConsole *pConsole;
	bool ToEnd;
	bool ToDestroy;

	virtual void ExecuteAnInstruction() = 0;
	virtual void SetPC(int Address) = 0;
	virtual char *GetSendCommand() = 0;
	virtual char *GetReceiveCommand() = 0;

public:
	CTec2kVM(CTec2kConsole *pCon);
	virtual ~CTec2kVM();

	virtual void SetRegister(int Index, int Value) = 0;
	virtual int GetRegister(int Index) = 0;

    virtual void WriteToMemory(int StartAddress, int Length, void *Buffer) = 0;
    virtual void ReadFromMemory(int StartAddress, int Length, void *Buffer) = 0;

	void Step(int StartAddress);
	void Run(int StartAddress);
	void Stop();
	void StopAndFree();
	void MonSendData();
	void MonReceiveData();
	virtual void SetStubAndRun(int StartAddress) = 0; 
	virtual size_t GetWordSize() = 0;
	virtual char *GetMonitorFileName() = 0;
	virtual void GetSendStartLen(int *pStart, int *pLen) = 0;
	virtual void SetSendStartLen(int Start, int Len) = 0;
};

#define VM16_FLAG_BIT_CARRY				0x8000
#define VM16_FLAG_BIT_ZERO				0x4000
#define VM16_FLAG_BIT_OVER				0x2000
#define VM16_FLAG_BIT_SIGN				0x1000

#define VM16_REGISTER_INDEX_SP			4
#define VM16_REGISTER_INDEX_PC			5

#define VM16_SEND_DATA_START_ADDRESS	0x2600
#define VM16_SEND_DATA_LENGTH			0x2601

class CTec2kVM16;

typedef void (CTec2kVM16::*INSTRUCTION_FUNCTION16)(void);

struct CInstructionInfo16
{
	char *szName;
	unsigned nCode;
	unsigned nType;
	INSTRUCTION_FUNCTION16 pFunc;
};

class CTec2kVM16 : public CTec2kVM
{
private:
	static const CInstructionInfo16 InstructionList[];
	static const CInstructionInfo16 *InstructionInfoMap[256];
	static bool InfoMapInitialized;
	static const short FlagCarryValues[];
	static const short FlagZeroValues[];
	static const short FlagOverValues[];
	static const short FlagSignValues[];

	short Register[16];
	short *pMemory;
	bool FlagCarry;
	bool FlagZero;
	bool FlagOver;
	bool FlagSign;
	bool InterruptEnabled;
    unsigned short *pPC;
    unsigned short *pSP;
	unsigned short CurrentCode;

	void InitInstructionInfoMap();
	void ExecuteAnInstruction();
	virtual void SetPC(int Address);
	char *GetSendCommand();
	char *GetReceiveCommand();

	void ExecuteADD();
	void ExecuteSUB();
	void ExecuteAND();
	void ExecuteCMP();
	void ExecuteXOR();
	void ExecuteTEST();
	void ExecuteOR();
	void ExecuteMVRR();
	void ExecuteDEC();
	void ExecuteINC();
	void ExecuteSHL();
	void ExecuteSHR();
	void ExecuteJR();
	void ExecuteJRC();
	void ExecuteJRNC();
	void ExecuteJRZ();
	void ExecuteJRNZ();
	void ExecuteJMPA();
	void ExecuteLDRR();
	void ExecuteIN();
	void ExecuteSTRR();
	void ExecutePSHF();
	void ExecutePUSH();
	void ExecuteOUT();
	void ExecutePOP();
	void ExecuteMVRD();
	void ExecutePOPF();
	void ExecuteRET();
	void ExecuteCALA();

	void ExecuteADC();
	void ExecuteSBB();
	void ExecuteRCL();
	void ExecuteRCR();
	void ExecuteASR();
	void ExecuteNOT();
	void ExecuteJMPR();
	void ExecuteJRS();
	void ExecuteJRNS();
	void ExecuteCLC();
	void ExecuteSTC();
	void ExecuteEI();
	void ExecuteDI();
	void ExecuteCALR();
	void ExecuteLDRA();
	void ExecuteLDRX();
	void ExecuteSTRX();
	void ExecuteSTRA();
	void ExecuteIRET();

	void ExecuteHALT();

public:
	CTec2kVM16(CTec2kConsole *pCon, int MemorySize = 65536);
	~CTec2kVM16();

	void SetRegister(int Index, int Value);
	int GetRegister(int Index);

    void WriteToMemory(int StartAddress, int Length, void *Buffer);
    void ReadFromMemory(int StartAddress, int Length, void *Buffer);
	void SetStubAndRun(int StartAddress); 
	size_t GetWordSize();
	char *GetMonitorFileName();
	void GetSendStartLen(int *pStart, int *pLen);
	void SetSendStartLen(int Start, int Len);
};

#define VM8_FLAG_BIT_CARRY				0x80
#define VM8_FLAG_BIT_ZERO				0x40
#define VM8_FLAG_BIT_OVER				0x20
#define VM8_FLAG_BIT_SIGN				0x10

#define VM8_REGISTER_INDEX_PC			4
#define VM8_REGISTER_INDEX_SP			6
#define VM8_REGISTER_INDEX_DATA_ADDR	8
#define VM8_REGISTER_INDEX_CODE_ADDR	10

#define VM8_SEND_DATA_START_ADDRESS	0x27ce
#define VM8_SEND_DATA_LENGTH			0x27cc

class CTec2kVM8;

typedef void (CTec2kVM8::*INSTRUCTION_FUNCTION8)(void);

struct CInstructionInfo8
{
	char *szName;
	unsigned nStartCode;
	unsigned nType;
	INSTRUCTION_FUNCTION8 pFunc;
};

class CTec2kVM8 : public CTec2kVM
{
private:
	static const CInstructionInfo8 InstructionList[];
	static const int InstructionCodeWidth[];
	static const CInstructionInfo8 *InstructionInfoMap[256];
	static bool InfoMapInitialized;
	static const char FlagCarryValues[];
	static const char FlagZeroValues[];
	static const char FlagOverValues[];
	static const char FlagSignValues[];

	char Register[16];
	char *pMemory;
	bool FlagCarry;
	bool FlagZero;
	bool FlagOver;
	bool FlagSign;
    unsigned short *pPC;
    unsigned short *pSP;
	unsigned short *pDataAddr;
	unsigned short *pCodeAddr;
	unsigned char CurrentCode;

	void InitInstructionInfoMap();
	void ExecuteAnInstruction();
	virtual void SetPC(int Address);
	char *GetSendCommand();
	char *GetReceiveCommand();

	void ExecuteADD();
	void ExecuteSUB();
	void ExecuteAND();
	void ExecuteCMP();
	void ExecuteMOV();
    void ExecuteSHR();
    void ExecuteSHL();
    void ExecuteIN();
    void ExecuteOUT();
	void ExecutePUSH();
	void ExecutePOP();
	void ExecuteSTO();
	void ExecuteLOD();
    void ExecuteINC();
	void ExecuteDEC();
    void ExecuteCLC();
    void ExecuteSTC();
    void ExecutePSHF();
    void ExecutePOPF();
    void ExecuteCALL();
    void ExecuteRET();
    void ExecuteJMP();
    void ExecuteTPC();
    void ExecuteFPC();
    void ExecuteTSP();
    void ExecuteFSP();
	void ExecuteMVD();
	void ExecuteJZ();
	void ExecuteJNZ();
	void ExecuteJC();
	void ExecuteJNC();
	void ExecuteJR();

	void ExecuteOR();
	void ExecuteTEST();
	void ExecuteADC();
	void ExecuteRCR();
	void ExecuteRCL();
	void ExecuteREAD();
	void ExecuteWRIT();
	void ExecuteINPT();
	void ExecuteOUPT();
	void ExecuteJS();
	void ExecuteJNS();
    void ExecuteJUMP();

    void ExecuteHALT();

public:
	CTec2kVM8(CTec2kConsole *pCon, int MemorySize = 65536);
	~CTec2kVM8();

	void SetRegister(int Index, int Value);
	int GetRegister(int Index);

    void WriteToMemory(int StartAddress, int Length, void *Buffer);
    void ReadFromMemory(int StartAddress, int Length, void *Buffer);
	void SetStubAndRun(int StartAddress); 
	size_t GetWordSize();
	char *GetMonitorFileName();
	void GetSendStartLen(int *pStart, int *pLen);
	void SetSendStartLen(int Start, int Len);
};

#endif // !defined(AFX_TEC2KVM_H__E7EC5D46_7890_4E8D_BCBB_CD9AF095D448__INCLUDED_)
