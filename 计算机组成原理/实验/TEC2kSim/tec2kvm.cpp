
#include "stdafx.h"
#include "tec2kconpanel.h"
#include "tec2kvm.h"

CTec2kConsole::CTec2kConsole(CTec2kConPanel *pView, int theWidth, int theHeight)
{
	pChildView = pView;
	Width = theWidth;
	Height = theHeight;
	ScreenText = new char[Width * Height];
	CursorVisible = false;
	ConsolePortState = PortDirect;
	HasUnreadKey = false;
	ClearScreen();
}

CTec2kConsole::~CTec2kConsole()
{
	delete []ScreenText;
}

void CTec2kConsole::ScrollALine()
{
	int Temp = Width * (Height - 1);
	memcpy(ScreenText, ScreenText + Width, Temp);
	memset(ScreenText + Temp, 32, Width);
	pChildView->ScrollALine();
}

char CTec2kConsole::PortInDirect(int Port)
{
	switch (Port)
	{
	case 0:
		HasUnreadKey = false;
		return KeyCode;

	case 1:
		return (HasUnreadKey << 1) + 1;

	default:
		return 0;
	}
}

void CTec2kConsole::PortOutDirect(int Port, char Value)
{
	if (Port) 
		return;

	if (CursorVisible)
		FlashCursor();
	switch (Value)
	{
	case '\r':

		ColPos = 0;
		break;

	case '\n':
		if (++RowPos == Height)
		{
			ScrollALine();
			RowPos--;
		}
		break;

	case '\t':
		do {	
			ScreenText[RowPos * Width + ColPos] = ' ';
			pChildView->UpdateAChar(RowPos, ColPos++, Value);
		} while ((ColPos & 7) && (ColPos < Width));
		if (ColPos >= Width)
		{
			ColPos = 0;
			if (++RowPos == Height)
			{
				ScrollALine();
				RowPos--;
			}
		}
		break;

	case '\b':
		if (ColPos)
			ColPos--;
		else if (RowPos)
		{
			RowPos--;
			ColPos = Width - 1;
		}
		break;

	case 0x1b:
		break;

	default:
		ScreenText[RowPos * Width + ColPos] = Value;
		pChildView->UpdateAChar(RowPos, ColPos, Value);
		if (++ColPos == Width)
		{
			ColPos = 0;
			if (++RowPos == Height)
			{
				ScrollALine();
				RowPos--;
			}
		}

	}
}

char CTec2kConsole::PortInCommand(int Port)
{
	switch (Port)
	{
	case 0:
		return TransferCommand[TransferIndex++];

	case 1:
		return 3;

	default:
		return 0;
	}
}

void CTec2kConsole::PortOutCommand(int Port, char Value)
{
	if (Port)
		return;

	if ((Value == '\n') && !TransferCommand[TransferIndex])
	{
		ConsolePortState = PortData;
		IsTransferCounting = false;
		TransferCount = 4;
		TransferIndex = 0;
	}
}

char CTec2kConsole::PortInData(int Port)
{
	switch (Port)
	{
	case 0:
		switch (ConsoleDataType)
		{
		case DataSend:
			UpdateTransferCount();
			return TransferByte;

		case DataReceive:
			TransferByte = (IsTransferCounting ? (pChildView->MonReadByte()) :
				StartLenBuffer[TransferIndex]);
			return TransferByte;
		}

	case 1:
		return 3;

	default:
		return 0;
	}
}

void CTec2kConsole::PortOutData(int Port, char Value)
{
	if (Port)
		return;

	switch (ConsoleDataType)
	{
	case DataSend:
		TransferByte = Value;
		if (IsTransferCounting)
			pChildView->MonWriteByte(Value);
		else
			StartLenBuffer[TransferIndex] = Value;
		break;

	case DataReceive:
		UpdateTransferCount();
		break;
	}
}

void CTec2kConsole::UpdateTransferCount()
{
	TransferIndex++;
	if (!IsTransferCounting)
	{
		if (IsTransferCounting = (TransferIndex == TransferCount))
		{
			if (ConsoleDataType == DataSend)
			{
				for (int i = 0; i < 4; i++)
					pChildView->MonWriteByte(StartLenBuffer[i ^ 1]);
			}
			TransferCount = (((unsigned short)StartLenBuffer[2] << 8) + 
				StartLenBuffer[3]) * WordSize;
			if (!TransferCount)
				TransferCount = 0x10000;
			TransferIndex = 0;
			LastPercent = -1;
		}
		LastTransferByte = TransferByte;
	}
	if (IsTransferCounting)
	{
		int Percent = TransferIndex * 100 / TransferCount;
		if (LastPercent != Percent)
		{
			pChildView->ShowTransferInfo(TransferIndex, TransferCount, Percent);
			LastPercent = Percent;
		}
		if (TransferIndex == TransferCount)
			DirectMode();
	}
}

void CTec2kConsole::KeyPressed(char Key)
{
	KeyCode = (Key == '\b') ? 0x7f : Key; 
	HasUnreadKey = true; 
}

char CTec2kConsole::PortIn(int Port)
{
	switch (ConsolePortState)
	{
	case PortCommand:
		return PortInCommand(Port);

	case PortData:
		return PortInData(Port);

	default:
		return PortInDirect(Port);
	}
}

void CTec2kConsole::PortOut(int Port, char Value)
{
	switch (ConsolePortState)
	{
	case PortCommand:
		PortOutCommand(Port, Value);
		break;

	case PortData:
		PortOutData(Port, Value);
		break;

	default:
		PortOutDirect(Port, Value);
		break;
	}
}

void CTec2kConsole::DoMessageLoop()
{
	pChildView->DoMessageLoop();
}

void CTec2kConsole::ClearScreen()
{
	memset(ScreenText, 32, Width * Height);
	RowPos = 0;
	ColPos = 0;
	HasUnreadKey = false;
	pChildView->ClearScreen();
}

void CTec2kConsole::ToDoNotify()
{
	pChildView->ToDoNotify();
}

void CTec2kConsole::EnableCursor()
{
	pChildView->EnableCursorTimer();
	CursorVisible = false;
}

void CTec2kConsole::DisbleCursor()
{
	if (CursorVisible)
		FlashCursor();
	pChildView->DisableCursorTimer();
}

void CTec2kConsole::FlashCursor()
{
	CursorVisible = !CursorVisible;
	pChildView->UpdateCursor();
}

void CTec2kConsole::DirectMode()
{
	ConsolePortState = PortDirect;
	pChildView->TransferFinished();
}

void CTec2kConsole::TransferMode(CConsoleDataType DataType, char *Command, 
	size_t WordSize_)
{
	TransferCommand = Command;
	ConsoleDataType = DataType;
	WordSize = WordSize_;
	ConsolePortState = PortCommand;
	TransferIndex = 0;
	if (DataType == DataSend)
		pChildView->MonWriteByte(1);
	else
	{
		pChildView->MonReadByte();
		for (int i = 0; i < 4; i++)
			StartLenBuffer[i ^ 1] = pChildView->MonReadByte();
	}
}

CTec2kVM::CTec2kVM(CTec2kConsole *pCon)
{
	pConsole = pCon;
	ToDestroy = false;
}

CTec2kVM::~CTec2kVM()
{
}

void CTec2kVM::Step(int StartAddress)
{
	SetPC(StartAddress);
	ExecuteAnInstruction();
}

void CTec2kVM::Run(int StartAddress)
{
	SetPC(StartAddress);
	ToEnd = false;
	pConsole->EnableCursor();
	int PeekMessageCount = MESSAGE_PEEKING_CYCLE;
	do
	{
		ExecuteAnInstruction();
		if (!(--PeekMessageCount))
		{
			pConsole->DoMessageLoop();
			PeekMessageCount = MESSAGE_PEEKING_CYCLE;
		}
	}
	while (!ToEnd);
	pConsole->DisbleCursor();
	pConsole->DirectMode();
	if (ToDestroy)
	{
		pConsole->ClearScreen();
		pConsole->ToDoNotify(); 
		delete this;
	}
}

void CTec2kVM::Stop()
{
	ToEnd = true;
}

void CTec2kVM::StopAndFree()
{
	ToDestroy = true;
	Stop();
}

void CTec2kVM::MonSendData()
{
	pConsole->TransferMode(DataSend, GetSendCommand(), GetWordSize());
}

void CTec2kVM::MonReceiveData()
{
	pConsole->TransferMode(DataReceive, GetReceiveCommand(), GetWordSize());
}

// 根据指令操作码高4位字节建立相应的函数映射表，加快速度
const CInstructionInfo16 CTec2kVM16::InstructionList[] = {
	{ "add",  0x00, 1, &CTec2kVM16::ExecuteADD  },
	{ "sub",  0x01, 1, &CTec2kVM16::ExecuteSUB  },
	{ "and",  0x02, 1, &CTec2kVM16::ExecuteAND  },
	{ "cmp",  0x03, 1, &CTec2kVM16::ExecuteCMP  },
	{ "xor",  0x04, 1, &CTec2kVM16::ExecuteXOR  },
	{ "test", 0x05, 1, &CTec2kVM16::ExecuteTEST },
	{ "or",   0x06, 1, &CTec2kVM16::ExecuteOR   },
	{ "mvrr", 0x07, 1, &CTec2kVM16::ExecuteMVRR },
	{ "dec",  0x08, 4, &CTec2kVM16::ExecuteDEC  },
	{ "inc",  0x09, 4, &CTec2kVM16::ExecuteINC  },
	{ "shl",  0x0a, 4, &CTec2kVM16::ExecuteSHL  },
	{ "shr",  0x0b, 4, &CTec2kVM16::ExecuteSHR  },
	{ "jr",   0x41, 8, &CTec2kVM16::ExecuteJR   },
	{ "jrc",  0x44, 8, &CTec2kVM16::ExecuteJRC  },
	{ "jrnc", 0x45, 8, &CTec2kVM16::ExecuteJRNC },
	{ "jrz",  0x46, 8, &CTec2kVM16::ExecuteJRZ  },
	{ "jrnz", 0x47, 8, &CTec2kVM16::ExecuteJRNZ },
	{ "jmpa", 0x80, 9, &CTec2kVM16::ExecuteJMPA },
	{ "ldrr", 0x81, 1, &CTec2kVM16::ExecuteLDRR },
	{ "in",   0x82, 2, &CTec2kVM16::ExecuteIN   },
	{ "strr", 0x83, 1, &CTec2kVM16::ExecuteSTRR },
	{ "pshf", 0x84, 5, &CTec2kVM16::ExecutePSHF },
	{ "push", 0x85, 3, &CTec2kVM16::ExecutePUSH },
	{ "out",  0x86, 2, &CTec2kVM16::ExecuteOUT  },
	{ "pop",  0x87, 4, &CTec2kVM16::ExecutePOP  },
	{ "mvrd", 0x88, 6, &CTec2kVM16::ExecuteMVRD },
	{ "popf", 0x8c, 5, &CTec2kVM16::ExecutePOPF },
	{ "ret",  0x8f, 5, &CTec2kVM16::ExecuteRET  },
	{ "cala", 0xce, 9, &CTec2kVM16::ExecuteCALA },

	{ "adc",  0x20, 1, &CTec2kVM16::ExecuteADC  },
	{ "sbb",  0x21, 1, &CTec2kVM16::ExecuteSBB  },
	{ "rcl",  0x2a, 4, &CTec2kVM16::ExecuteRCL  },
	{ "rcr",  0x2b, 4, &CTec2kVM16::ExecuteRCR  },
	{ "asr",  0x2c, 4, &CTec2kVM16::ExecuteASR  },
	{ "not",  0x2d, 4, &CTec2kVM16::ExecuteNOT  },
	{ "jmpr", 0x60, 3, &CTec2kVM16::ExecuteJMPR },
	{ "jrs",  0x64, 8, &CTec2kVM16::ExecuteJRS  },
	{ "jrns", 0x65, 8, &CTec2kVM16::ExecuteJRNS },
	{ "clc",  0x6c, 5, &CTec2kVM16::ExecuteCLC  },
	{ "stc",  0x6d, 5, &CTec2kVM16::ExecuteSTC  },
	{ "ei",   0x6e, 5, &CTec2kVM16::ExecuteEI   },
	{ "di",   0x6f, 5, &CTec2kVM16::ExecuteDI   },
	{ "calr", 0xe0, 3, &CTec2kVM16::ExecuteCALR },
	{ "ldra", 0xe4, 6, &CTec2kVM16::ExecuteLDRA },
	{ "ldrx", 0xe5, 7, &CTec2kVM16::ExecuteLDRX },
	{ "strx", 0xe6, 7, &CTec2kVM16::ExecuteSTRX },
	{ "stra", 0xe7, 6, &CTec2kVM16::ExecuteSTRA },
	{ "iret", 0xef, 5, &CTec2kVM16::ExecuteIRET },

	{ "halt", 0xf0, 5, &CTec2kVM16::ExecuteHALT }
};

const CInstructionInfo16 *CTec2kVM16::InstructionInfoMap[256];

bool CTec2kVM16::InfoMapInitialized = false;

const short CTec2kVM16::FlagCarryValues[] = { 0, VM16_FLAG_BIT_CARRY };
const short CTec2kVM16::FlagZeroValues[]  = { 0, VM16_FLAG_BIT_ZERO };
const short CTec2kVM16::FlagOverValues[]  = { 0, VM16_FLAG_BIT_OVER };
const short CTec2kVM16::FlagSignValues[]  = { 0, VM16_FLAG_BIT_SIGN };

CTec2kVM16::CTec2kVM16(CTec2kConsole *pCon, int MemorySize) : CTec2kVM(pCon)
{
	// 建立内存区域，初始化各指针
	pMemory = new short[MemorySize];
	pPC = (unsigned short *)(Register + VM16_REGISTER_INDEX_PC);
	pSP = (unsigned short *)(Register + VM16_REGISTER_INDEX_SP);

	if (!InfoMapInitialized)
		InitInstructionInfoMap();
}

CTec2kVM16::~CTec2kVM16()
{
	delete []pMemory;
}

void CTec2kVM16::InitInstructionInfoMap()
{
	memset(InstructionInfoMap, 0, sizeof(InstructionInfoMap));
	for (int i = 0; i < sizeof(InstructionList) / sizeof(InstructionList[0]); i++)
		InstructionInfoMap[InstructionList[i].nCode] = &InstructionList[i];
	InfoMapInitialized = true;
}

void CTec2kVM16::ExecuteAnInstruction()
{
	// 取操作码，PC并加1
	CurrentCode = pMemory[(*pPC)++];
	unsigned char OperatorCode = CurrentCode >> 8;
	// 根据高4位字节的值，调用相应的函数，注意成员函数的调用方式
	if (InstructionInfoMap[OperatorCode])
		(this->*(InstructionInfoMap[OperatorCode]->pFunc))();
}

void CTec2kVM16::SetPC(int Address)
{
	*pPC = Address;
}

char *CTec2kVM16::GetSendCommand()
{
	return "\rg769\r";
}

char *CTec2kVM16::GetReceiveCommand()
{
	return "\rg78b\r";
}

////////////////////////////////////////////////////////////////////////////////
//
// 以下宏定义只能在CTec2kVM16类的各条指令执行函数中使用，在其他位置使用将出错！
//

// 取得目标寄存器指令的寄存器号，操作码的低2位字节是寄存器号，结果存index
#define VM16_DST_REG_INDEX  ((CurrentCode >> 4) & 0x0f)

// 取得单寄存器指令的寄存器号，操作码的低2位字节是寄存器号，结果存index
#define VM16_SRC_REG_INDEX  (CurrentCode & 0x0f)

#define VM16_EXT_REG_VALUE(index) \
	((unsigned int)((int)Register[(index)] & 0x1ffff))

#define VM16_EXT_DST_REG_VALUE  (VM16_EXT_REG_VALUE(VM16_DST_REG_INDEX))

#define VM16_EXT_SRC_REG_VALUE  (VM16_EXT_REG_VALUE(VM16_SRC_REG_INDEX))

#define VM16_WORD_PARAM  ((unsigned short)pMemory[(*pPC)++])

#define VM16_BYTE_PARAM  (char(CurrentCode))

#define VM16_SET_REG_VALUE(index, value) \
	{ Register[index] = (short)(value); }

#define VM16_SET_FLAG_CARRY_ADD(value) 	{ FlagCarry = ((value) & 0x20000) != 0; }

#define VM16_SET_FLAG_CARRY_SUB(value) 	{ FlagCarry = ((value) & 0x20000) == 0; }

#define VM16_SET_FLAG_ZERO(value)  { FlagZero = short(value) == 0; }

#define VM16_SET_FLAG_OVER(value) \
	{ FlagOver = ((((value) >> 1) ^ (value)) & 0x8000) != 0; }

#define VM16_SET_FLAG_SIGN(value)  { FlagSign = ((value) & 0x8000) != 0; }

#define VM16_SET_ALL_FLAGS_ADD(value) \
	{ \
		VM16_SET_FLAG_CARRY_ADD(value) \
		VM16_SET_FLAG_ZERO(value) \
		VM16_SET_FLAG_OVER(value) \
		VM16_SET_FLAG_SIGN(value) \
	}

#define VM16_SET_ALL_FLAGS_SUB(value) \
	{ \
		VM16_SET_FLAG_CARRY_SUB(value) \
		VM16_SET_FLAG_ZERO(value) \
		VM16_SET_FLAG_OVER(value) \
		VM16_SET_FLAG_SIGN(value) \
	}

#define VM16_PUSH_TO_STACK(value)  { pMemory[--(*pSP)] = (value); }

#define VM16_POP_FROM_STACK  (pMemory[(*pSP)++])

#define VM16_JUMP_RELATIVE 	{ *pPC += short(VM16_BYTE_PARAM); } 

#define VM16_JUMP_CONDITION(boolcondition) \
	{ \
		if (boolcondition) \
			VM16_JUMP_RELATIVE \
	}

////////////////////////////////////////////////////////////////////////////////

void CTec2kVM16::ExecuteADD()
{
	int dr = VM16_DST_REG_INDEX;

	unsigned resValue = VM16_EXT_REG_VALUE(dr) + VM16_EXT_SRC_REG_VALUE;

	VM16_SET_ALL_FLAGS_ADD(resValue)
	VM16_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM16::ExecuteSUB()
{
	int dr = VM16_DST_REG_INDEX;

	unsigned resValue = VM16_EXT_REG_VALUE(dr) - VM16_EXT_SRC_REG_VALUE;

	VM16_SET_ALL_FLAGS_SUB(resValue)
	VM16_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM16::ExecuteAND()
{
	int dr = VM16_DST_REG_INDEX;

	unsigned resValue = VM16_EXT_REG_VALUE(dr) & VM16_EXT_SRC_REG_VALUE;

	VM16_SET_ALL_FLAGS_ADD(resValue)
	VM16_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM16::ExecuteCMP()
{
	unsigned resValue = VM16_EXT_DST_REG_VALUE - VM16_EXT_SRC_REG_VALUE;

	VM16_SET_ALL_FLAGS_SUB(resValue)
}

void CTec2kVM16::ExecuteXOR()
{
	int dr = VM16_DST_REG_INDEX;

	unsigned resValue = VM16_EXT_REG_VALUE(dr) ^ VM16_EXT_SRC_REG_VALUE;

	VM16_SET_ALL_FLAGS_ADD(resValue)
	VM16_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM16::ExecuteTEST()
{
	unsigned resValue = VM16_EXT_DST_REG_VALUE & VM16_EXT_SRC_REG_VALUE;

	VM16_SET_ALL_FLAGS_ADD(resValue)
}

void CTec2kVM16::ExecuteOR()
{
	int dr = VM16_DST_REG_INDEX;

	unsigned resValue = VM16_EXT_REG_VALUE(dr) | VM16_EXT_SRC_REG_VALUE;

	VM16_SET_ALL_FLAGS_ADD(resValue)
	VM16_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM16::ExecuteMVRR()
{
	VM16_SET_REG_VALUE(VM16_DST_REG_INDEX, Register[VM16_SRC_REG_INDEX])
}

void CTec2kVM16::ExecuteDEC()
{
	int reg = VM16_DST_REG_INDEX;
	unsigned value = VM16_EXT_REG_VALUE(reg);

	value--;

	VM16_SET_ALL_FLAGS_SUB(value)
	VM16_SET_REG_VALUE(reg, value)
}

void CTec2kVM16::ExecuteINC()
{ 
	int reg = VM16_DST_REG_INDEX;
	unsigned value = VM16_EXT_REG_VALUE(reg);

	value++;

	VM16_SET_ALL_FLAGS_ADD(value)
	VM16_SET_REG_VALUE(reg, value)
}

void CTec2kVM16::ExecuteSHL()

{
	int reg = VM16_DST_REG_INDEX;

    unsigned short value = Register[reg];
    FlagCarry = (value & 0x8000) != 0;

	VM16_SET_REG_VALUE(reg, value << 1)
}

void CTec2kVM16::ExecuteSHR()
{
	int reg = VM16_DST_REG_INDEX;

    unsigned short value = Register[reg];
	FlagCarry = value & 1;

	VM16_SET_REG_VALUE(reg, value >> 1)
}

void CTec2kVM16::ExecuteJR()
{
	VM16_JUMP_RELATIVE
}

void CTec2kVM16::ExecuteJRC()
{
	VM16_JUMP_CONDITION(FlagCarry)
}

void CTec2kVM16::ExecuteJRNC()
{
	VM16_JUMP_CONDITION(!FlagCarry)
}

void CTec2kVM16::ExecuteJRZ()
{
	VM16_JUMP_CONDITION(FlagZero)
}

void CTec2kVM16::ExecuteJRNZ()
{
	VM16_JUMP_CONDITION(!FlagZero)
}

void CTec2kVM16::ExecuteJMPA()
{
	unsigned short WordParam = VM16_WORD_PARAM;

	*pPC = WordParam;
}

void CTec2kVM16::ExecuteLDRR()
{
	VM16_SET_REG_VALUE(VM16_DST_REG_INDEX, 
		pMemory[(unsigned short)Register[VM16_SRC_REG_INDEX]])
}

void CTec2kVM16::ExecuteIN()
{
	VM16_SET_REG_VALUE(0, pConsole->PortIn((unsigned char)VM16_BYTE_PARAM & 3))
}

void CTec2kVM16::ExecuteSTRR()
{
	pMemory[(unsigned short)Register[VM16_DST_REG_INDEX]] = 
		Register[VM16_SRC_REG_INDEX];
}

void CTec2kVM16::ExecutePSHF()
{
	short FlagChar = FlagCarryValues[FlagCarry] | FlagZeroValues[FlagZero] |
		FlagOverValues[FlagOver] | FlagSignValues[FlagSign];

	VM16_PUSH_TO_STACK(FlagChar)
}

void CTec2kVM16::ExecutePUSH()
{
	VM16_PUSH_TO_STACK(Register[VM16_SRC_REG_INDEX])
}

void CTec2kVM16::ExecuteOUT()
{
	pConsole->PortOut((unsigned char)VM16_BYTE_PARAM & 3, (unsigned char)Register[0]);
}

void CTec2kVM16::ExecutePOP()
{
	VM16_SET_REG_VALUE(VM16_DST_REG_INDEX, VM16_POP_FROM_STACK)
}

void CTec2kVM16::ExecuteMVRD()
{
	VM16_SET_REG_VALUE(VM16_DST_REG_INDEX, VM16_WORD_PARAM)
}

void CTec2kVM16::ExecutePOPF()
{
	short FlagChar = VM16_POP_FROM_STACK;

	FlagCarry = (FlagChar & VM16_FLAG_BIT_CARRY) != 0;
	FlagZero = (FlagChar & VM16_FLAG_BIT_ZERO) != 0;
	FlagOver = (FlagChar & VM16_FLAG_BIT_OVER) != 0;
	FlagSign = (FlagChar & VM16_FLAG_BIT_SIGN) != 0;
}
	
void CTec2kVM16::ExecuteRET()
{
	*pPC = VM16_POP_FROM_STACK;
}

void CTec2kVM16::ExecuteCALA()
{
	unsigned short WordParam = VM16_WORD_PARAM;
	
	VM16_PUSH_TO_STACK(*pPC)
	*pPC = WordParam;
}

void CTec2kVM16::ExecuteADC()
{
	int dr = VM16_DST_REG_INDEX;

	unsigned resValue = VM16_EXT_REG_VALUE(dr) + VM16_EXT_SRC_REG_VALUE +
		(unsigned)FlagCarry;

	VM16_SET_ALL_FLAGS_ADD(resValue)
	VM16_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM16::ExecuteSBB()
{
	int dr = VM16_DST_REG_INDEX;

	unsigned resValue = VM16_EXT_REG_VALUE(dr) - VM16_EXT_SRC_REG_VALUE -
		unsigned(!FlagCarry);

	VM16_SET_ALL_FLAGS_SUB(resValue)
	VM16_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM16::ExecuteRCL()
{
	int reg = VM16_DST_REG_INDEX;

	unsigned value = Register[reg];
	value <<= 1;
	if (FlagCarry)
		value |= 1;
    FlagCarry = (value & 0x10000) != 0;

	VM16_SET_REG_VALUE(reg, value)
}

void CTec2kVM16::ExecuteRCR()
{
	int reg = VM16_DST_REG_INDEX;

	unsigned value = Register[reg];
	if (FlagCarry)
		value |= 0x10000;
	else
		value &= 0xffff;
    FlagCarry = value & 1;

	VM16_SET_REG_VALUE(reg, value >> 1)
}

void CTec2kVM16::ExecuteASR()
{
	int reg = VM16_DST_REG_INDEX;

	short value = Register[reg];
    FlagCarry = value & 1;

	VM16_SET_REG_VALUE(reg, value >> 1)
}

void CTec2kVM16::ExecuteNOT()
{
	int reg = VM16_DST_REG_INDEX;
	VM16_SET_REG_VALUE(reg, ~Register[reg])
}

void CTec2kVM16::ExecuteJMPR()
{
	*pPC = Register[VM16_SRC_REG_INDEX];
}
	
void CTec2kVM16::ExecuteJRS()
{
	VM16_JUMP_CONDITION(FlagSign)
}

void CTec2kVM16::ExecuteJRNS()
{
	VM16_JUMP_CONDITION(!FlagSign)
}

void CTec2kVM16::ExecuteCLC()
{
	FlagCarry = false;
}

void CTec2kVM16::ExecuteSTC()
{
	FlagCarry = true;
}

void CTec2kVM16::ExecuteEI()
{
	InterruptEnabled = true;
}

void CTec2kVM16::ExecuteDI()
{
	InterruptEnabled = false;
}
	
void CTec2kVM16::ExecuteCALR()
{
	VM16_PUSH_TO_STACK(*pPC)
	*pPC = Register[VM16_SRC_REG_INDEX];
}

void CTec2kVM16::ExecuteLDRA()
{
	VM16_SET_REG_VALUE(VM16_DST_REG_INDEX, pMemory[VM16_WORD_PARAM]);
}

void CTec2kVM16::ExecuteLDRX()
{
	VM16_SET_REG_VALUE(VM16_DST_REG_INDEX, 
		pMemory[VM16_WORD_PARAM + (unsigned short)Register[VM16_SRC_REG_INDEX]]);
}

void CTec2kVM16::ExecuteSTRX()
{
	pMemory[VM16_WORD_PARAM + (unsigned short)Register[VM16_SRC_REG_INDEX]] = 
		Register[VM16_DST_REG_INDEX];
}

void CTec2kVM16::ExecuteSTRA()
{
	pMemory[VM16_WORD_PARAM] = Register[VM16_SRC_REG_INDEX];
}

void CTec2kVM16::ExecuteIRET()
{
}

void CTec2kVM16::ExecuteHALT()
{
	Stop();
}

void CTec2kVM16::SetRegister(int Index, int Value) 
{
	Register[Index] = Value; 
}

int CTec2kVM16::GetRegister(int Index)
{
	return Register[Index]; 
} 

void CTec2kVM16::WriteToMemory(int StartAddress, int Length, void *Buffer)
{
	if (StartAddress < 0 || StartAddress >= 0x10000) 
		return;

	if (StartAddress + Length > 0x10000)
		Length = 0x10000 - StartAddress;
	unsigned char *pSrc = (unsigned char *)Buffer;
	unsigned short *pDst = (unsigned short *)&pMemory[StartAddress];
	for (int i = 0; i < Length; i++)
	{
		*(pDst++) = ((unsigned short)(*pSrc) << 8) | 
			(unsigned short)(*(pSrc + 1));
		pSrc++;
		pSrc++;
	}
}

void CTec2kVM16::ReadFromMemory(int StartAddress, int Length, void *Buffer)
{
	if (StartAddress < 0 || StartAddress >= 0x10000) 
		return;

	if (StartAddress + Length > 0x10000)
		Length = 0x10000 - StartAddress;
	unsigned short *pSrc = (unsigned short *)&pMemory[StartAddress];
	unsigned char *pDst = (unsigned char *)Buffer;
	for (int i = 0; i < Length; i++)
	{
		*(pDst++) = (unsigned char)((*pSrc) >> 8);
		*(pDst++) = (unsigned char)(*(pSrc++));
	}
}

void CTec2kVM16::SetStubAndRun(int StartAddress)
{
	static char StartBuf[] = { 0xce, 0, 0, 0, 0xf0, 0 };
	StartBuf[2] = StartAddress >> 8;
	StartBuf[3] = (char)StartAddress;
	WriteToMemory(0xfff0, sizeof(StartBuf), StartBuf);
	Run(0xfff0);
}

size_t CTec2kVM16::GetWordSize()
{
	return sizeof(*pMemory);
}

char *CTec2kVM16::GetMonitorFileName()
{
	return "monitor16.cod";
}

void CTec2kVM16::GetSendStartLen(int *pStart, int *pLen)
{
	*pStart = (unsigned short)pMemory[VM16_SEND_DATA_START_ADDRESS];
	*pLen = (unsigned short)pMemory[VM16_SEND_DATA_LENGTH];
}

void CTec2kVM16::SetSendStartLen(int Start, int Len)
{
	pMemory[VM16_SEND_DATA_START_ADDRESS] = Start;
	pMemory[VM16_SEND_DATA_LENGTH] = Len;
}

// 根据指令操作码高4位字节建立相应的函数映射表，加快速度
const int CTec2kVM8::InstructionCodeWidth[] = {0, 16, 4, 1, 16, 1, 4, 1, 1};

const CInstructionInfo8 CTec2kVM8::InstructionList[] = {
	{ "add",  0x00, 1, &CTec2kVM8::ExecuteADD  },
	{ "sub",  0x10, 1, &CTec2kVM8::ExecuteSUB  },
	{ "and",  0x20, 1, &CTec2kVM8::ExecuteAND  },
	{ "cmp",  0x30, 1, &CTec2kVM8::ExecuteCMP  },
	{ "mov",  0x40, 1, &CTec2kVM8::ExecuteMOV  },
	{ "shr",  0xa0, 2, &CTec2kVM8::ExecuteSHR  },
	{ "shl",  0xa4, 2, &CTec2kVM8::ExecuteSHL  },
	{ "in",   0xa8, 2, &CTec2kVM8::ExecuteIN   },
	{ "out",  0xac, 2, &CTec2kVM8::ExecuteOUT  },
	{ "push", 0xb0, 2, &CTec2kVM8::ExecutePUSH },
	{ "pop",  0xb4, 2, &CTec2kVM8::ExecutePOP  },
	{ "sto",  0xb8, 2, &CTec2kVM8::ExecuteSTO  },
	{ "lod",  0xbc, 2, &CTec2kVM8::ExecuteLOD  },
	{ "inc",  0xc0, 2, &CTec2kVM8::ExecuteINC  },
	{ "inc",  0xc8, 2, &CTec2kVM8::ExecuteINC  },
	{ "inc",  0xcc, 2, &CTec2kVM8::ExecuteINC  },
	{ "dec",  0x90, 2, &CTec2kVM8::ExecuteDEC  },

	{ "clc",  0xf8, 3, &CTec2kVM8::ExecuteCLC  },
	{ "stc",  0xf9, 3, &CTec2kVM8::ExecuteSTC  },
	{ "pshf", 0xfa, 3, &CTec2kVM8::ExecutePSHF },
	{ "popf", 0xfb, 3, &CTec2kVM8::ExecutePOPF },
	{ "call", 0xfc, 3, &CTec2kVM8::ExecuteCALL },
	{ "ret",  0xfd, 3, &CTec2kVM8::ExecuteRET  },
	{ "jmp",  0xff, 3, &CTec2kVM8::ExecuteJMP  },
	{ "tpc",  0xc4, 3, &CTec2kVM8::ExecuteTPC  },
	{ "fpc",  0xc5, 3, &CTec2kVM8::ExecuteFPC  },
	{ "tsp",  0xc6, 3, &CTec2kVM8::ExecuteTSP  },
	{ "fsp",  0xc7, 3, &CTec2kVM8::ExecuteFSP  },
	{ "mvd",  0xd0, 4, &CTec2kVM8::ExecuteMVD  },
	{ "jz",   0xe8, 5, &CTec2kVM8::ExecuteJZ   },
	{ "jnz",  0xe9, 5, &CTec2kVM8::ExecuteJNZ  },
	{ "jc",   0xea, 5, &CTec2kVM8::ExecuteJC   },
	{ "jnc",  0xeb, 5, &CTec2kVM8::ExecuteJNC  },
	{ "jr",   0xec, 5, &CTec2kVM8::ExecuteJR   },

	{ "or",   0x50, 1, &CTec2kVM8::ExecuteOR   },
	{ "test", 0x60, 1, &CTec2kVM8::ExecuteTEST },
	{ "adc",  0x70, 1, &CTec2kVM8::ExecuteADC  },
	{ "rcr",  0x80, 2, &CTec2kVM8::ExecuteRCR  },
	{ "rcl",  0x84, 2, &CTec2kVM8::ExecuteRCL  },
	{ "read", 0x88, 6, &CTec2kVM8::ExecuteREAD },
	{ "writ", 0x8c, 6, &CTec2kVM8::ExecuteWRIT },
	{ "inpt", 0xe2, 8, &CTec2kVM8::ExecuteINPT },
	{ "oupt", 0xe3, 8, &CTec2kVM8::ExecuteOUPT },
	{ "js",   0xe4, 5, &CTec2kVM8::ExecuteJS   },
	{ "jns",  0xe5, 5, &CTec2kVM8::ExecuteJNS  },
	{ "jump", 0xf7, 7, &CTec2kVM8::ExecuteJUMP },

	{ "halt", 0xf0, 3, &CTec2kVM8::ExecuteHALT }
};

const CInstructionInfo8 *CTec2kVM8::InstructionInfoMap[256];

bool CTec2kVM8::InfoMapInitialized = false;

const char CTec2kVM8::FlagCarryValues[] = { 0, VM8_FLAG_BIT_CARRY };
const char CTec2kVM8::FlagZeroValues[]  = { 0, VM8_FLAG_BIT_ZERO };
const char CTec2kVM8::FlagOverValues[]  = { 0, VM8_FLAG_BIT_OVER };
const char CTec2kVM8::FlagSignValues[]  = { 0, VM8_FLAG_BIT_SIGN };

CTec2kVM8::CTec2kVM8(CTec2kConsole *pCon, int MemorySize) : CTec2kVM(pCon)
{
	// 建立内存区域，初始化各指针
	pMemory = new char[MemorySize];
	pPC = (unsigned short *)(Register + VM8_REGISTER_INDEX_PC);
	pSP = (unsigned short *)(Register + VM8_REGISTER_INDEX_SP);
	pDataAddr = (unsigned short *)(Register + VM8_REGISTER_INDEX_DATA_ADDR);
	pCodeAddr = (unsigned short *)(Register + VM8_REGISTER_INDEX_CODE_ADDR);

	if (!InfoMapInitialized)
		InitInstructionInfoMap();
}

CTec2kVM8::~CTec2kVM8()
{
	delete []pMemory;
}

void CTec2kVM8::InitInstructionInfoMap()
{
	memset(InstructionInfoMap, 0, sizeof(InstructionInfoMap));
	for (int i = 0; i < sizeof(InstructionList) / sizeof(InstructionList[0]); i++)
	{
		unsigned char theCode = InstructionList[i].nStartCode;
		for (int j = 0; j < InstructionCodeWidth[InstructionList[i].nType]; j++)
			InstructionInfoMap[theCode++] = &InstructionList[i];
	}
	InfoMapInitialized = true;
}

void CTec2kVM8::ExecuteAnInstruction()
{
	// 取操作码，PC并加1
	CurrentCode = pMemory[(*pPC)++];
	// 根据高4位字节的值，调用相应的函数，注意成员函数的调用方式
	if (InstructionInfoMap[CurrentCode])
		(this->*(InstructionInfoMap[CurrentCode]->pFunc))();
}

void CTec2kVM8::SetPC(int Address)
{
	*pPC = Address;
}

char *CTec2kVM8::GetSendCommand()
{
	return "\rG 1F55\r";
}

char *CTec2kVM8::GetReceiveCommand()
{
	return "\rG 1F00\r";
}

////////////////////////////////////////////////////////////////////////////////
//
// 以下宏定义只能在CTec2kVM8类的各条指令执行函数中使用，在其他位置使用将出错！
//

// 取得双寄存器指令的寄存器号。操作码的低2位字节是sr的寄存器号，结果存srindex
// 操作码的第2，3位字节是dr的寄存器号，结果存drindex
#define VM8_HIGH_REG_INDEX  ((CurrentCode >> 2) & 3)

// 取得单寄存器指令的寄存器号，操作码的低2位字节是寄存器号，结果存index
#define VM8_LOW_REG_INDEX  (CurrentCode & 3)

// 取得单寄存器指令的寄存器号，操作码的低2位字节是寄存器号，结果存index
#define VM8_FULL_REG_INDEX  (CurrentCode & 0x0f)

// 取得指定寄存器的值，寄存器号为index，结果存value。如果value是16字节短整形，
// 则value的第8字节与第7字节相同，形成双符号位，便于实现加减运算的标志位设置
#define VM8_EXT_REG_VALUE(index) \
	((unsigned short)((short)Register[(index)] & 0x1ff))

#define VM8_EXT_HIGH_REG_VALUE  (VM8_EXT_REG_VALUE(VM8_HIGH_REG_INDEX))

#define VM8_EXT_LOW_REG_VALUE  (VM8_EXT_REG_VALUE(VM8_LOW_REG_INDEX))

#define VM8_GET_WORD_PARAM(value) \
	{ \
		value = (((unsigned short)((unsigned char)pMemory[*pPC])) << 8) | \
			((unsigned short)((unsigned char)pMemory[(*pPC) + 1])); \
		(*pPC)++; \
		(*pPC)++; \
	}

#define VM8_BYTE_PARAM  (pMemory[(*pPC)++])

#define VM8_SET_REG_VALUE(index, value) \
	{ Register[index] = (char)(value); }

#define VM8_SET_FLAG_CARRY_ADD(value) 	{ FlagCarry = ((value) & 0x200) != 0; }

#define VM8_SET_FLAG_CARRY_SUB(value) 	{ FlagCarry = ((value) & 0x200) == 0; }

#define VM8_SET_FLAG_ZERO(value)  { FlagZero = char(value) == 0; }

#define VM8_SET_FLAG_OVER(value) \
	{ FlagOver = ((((value) >> 1) ^ (value)) & 0x80) != 0; }

#define VM8_SET_FLAG_SIGN(value)  { FlagSign = ((value) & 0x80) != 0; }

#define VM8_SET_ALL_FLAGS_ADD(value) \
	{ \
		VM8_SET_FLAG_CARRY_ADD(value) \
		VM8_SET_FLAG_ZERO(value) \
		VM8_SET_FLAG_OVER(value) \
		VM8_SET_FLAG_SIGN(value) \
	}

#define VM8_SET_ALL_FLAGS_SUB(value) \
	{ \
		VM8_SET_FLAG_CARRY_SUB(value) \
		VM8_SET_FLAG_ZERO(value) \
		VM8_SET_FLAG_OVER(value) \
		VM8_SET_FLAG_SIGN(value) \
	}

#define VM8_PUSH_TO_STACK(value)  { pMemory[--(*pSP)] = (value); }

#define VM8_POP_FROM_STACK  (pMemory[(*pSP)++])

#define VM8_JUMP_RELATIVE \
	{ \
		signed char __JumpOffset = VM8_BYTE_PARAM; \
		*pPC += __JumpOffset; \
	} 

#define VM8_JUMP_CONDITION(boolcondition) \
	{ \
		if (boolcondition) \
			VM8_JUMP_RELATIVE \
		else \
			(*pPC)++; \
	}

////////////////////////////////////////////////////////////////////////////////

void CTec2kVM8::ExecuteADD()
{
	int dr = VM8_HIGH_REG_INDEX;

	unsigned short resValue = VM8_EXT_REG_VALUE(dr) + VM8_EXT_LOW_REG_VALUE;

	VM8_SET_ALL_FLAGS_ADD(resValue)
	VM8_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM8::ExecuteSUB()
{
	int dr = VM8_HIGH_REG_INDEX;

	unsigned short resValue = VM8_EXT_REG_VALUE(dr) - VM8_EXT_LOW_REG_VALUE;

	VM8_SET_ALL_FLAGS_SUB(resValue)
	VM8_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM8::ExecuteAND()
{
	int dr = VM8_HIGH_REG_INDEX;

	unsigned short resValue = VM8_EXT_REG_VALUE(dr) & VM8_EXT_LOW_REG_VALUE;

	VM8_SET_ALL_FLAGS_ADD(resValue)
	VM8_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM8::ExecuteCMP()
{
	unsigned short resValue = VM8_EXT_HIGH_REG_VALUE - VM8_EXT_LOW_REG_VALUE;

	VM8_SET_ALL_FLAGS_SUB(resValue)
}

void CTec2kVM8::ExecuteMOV()
{
	VM8_SET_REG_VALUE(VM8_HIGH_REG_INDEX, Register[VM8_LOW_REG_INDEX])
}

void CTec2kVM8::ExecuteSHR()
{
	int reg = VM8_LOW_REG_INDEX;

    unsigned char value = Register[reg];
	FlagCarry = value & 1;

	VM8_SET_REG_VALUE(reg, value >> 1)
}

void CTec2kVM8::ExecuteSHL()
{
	int reg = VM8_LOW_REG_INDEX;

    unsigned char value = Register[reg];
    FlagCarry = (value & 0x80) != 0;

	VM8_SET_REG_VALUE(reg, value << 1)
}

void CTec2kVM8::ExecuteIN()
{
	VM8_SET_REG_VALUE(0, pConsole->PortIn(VM8_LOW_REG_INDEX))
}

void CTec2kVM8::ExecuteOUT()
{
	pConsole->PortOut(VM8_LOW_REG_INDEX, Register[0]);
}

void CTec2kVM8::ExecutePUSH()
{
	VM8_PUSH_TO_STACK(Register[VM8_LOW_REG_INDEX])
}

void CTec2kVM8::ExecutePOP()
{
	VM8_SET_REG_VALUE(VM8_LOW_REG_INDEX, VM8_POP_FROM_STACK)
}

void CTec2kVM8::ExecuteSTO()
{
	pMemory[*pDataAddr] = Register[VM8_LOW_REG_INDEX];
}

void CTec2kVM8::ExecuteLOD()
{
	VM8_SET_REG_VALUE(VM8_LOW_REG_INDEX, pMemory[*pDataAddr])
}

void CTec2kVM8::ExecuteINC()
{ 
	int reg = VM8_FULL_REG_INDEX;
	unsigned short value = VM8_EXT_REG_VALUE(reg);

	value++;

	VM8_SET_ALL_FLAGS_ADD(value)
	VM8_SET_REG_VALUE(reg, value)
}

void CTec2kVM8::ExecuteDEC()
{
	int reg = VM8_LOW_REG_INDEX;
	unsigned short value = VM8_EXT_REG_VALUE(reg);

	value--;

	VM8_SET_ALL_FLAGS_SUB(value)
	VM8_SET_REG_VALUE(reg, value)
}

void CTec2kVM8::ExecuteCLC()
{
	FlagCarry = false;
}

void CTec2kVM8::ExecuteSTC()
{
	FlagCarry = true;
}

void CTec2kVM8::ExecutePSHF()
{
	char FlagChar = FlagCarryValues[FlagCarry] | FlagZeroValues[FlagZero] |
		FlagOverValues[FlagOver] | FlagSignValues[FlagSign];

	VM8_PUSH_TO_STACK(FlagChar)
}

void CTec2kVM8::ExecutePOPF()
{
	char FlagChar = VM8_POP_FROM_STACK;

	FlagCarry = (FlagChar & VM8_FLAG_BIT_CARRY) != 0;
	FlagZero = (FlagChar & VM8_FLAG_BIT_ZERO) != 0;
	FlagOver = (FlagChar & VM8_FLAG_BIT_OVER) != 0;
	FlagSign = (FlagChar & VM8_FLAG_BIT_SIGN) != 0;
}

void CTec2kVM8::ExecuteCALL()
{
	--(*pSP);
    *((unsigned short *)&pMemory[--(*pSP)]) = *pPC;
	*pPC = *pCodeAddr;
}

void CTec2kVM8::ExecuteRET()
{
	*pPC = *((unsigned short *)&pMemory[(*pSP)++]);
	(*pSP)++;
}

void CTec2kVM8::ExecuteJMP()
{
	*pPC = *pCodeAddr;
}

void CTec2kVM8::ExecuteTPC()
{ 
	*pPC = *((unsigned short *)(&Register[12]));
}

void CTec2kVM8::ExecuteFPC()
{ 
	*((unsigned short *)(&Register[12])) = *pPC;
}

void CTec2kVM8::ExecuteTSP()
{ 
	*pSP = *((unsigned short *)(&Register[14]));
}

void CTec2kVM8::ExecuteFSP()
{ 
	*((unsigned short *)(&Register[14])) = *pSP;
}

void CTec2kVM8::ExecuteMVD()
{
	VM8_SET_REG_VALUE(VM8_FULL_REG_INDEX, VM8_BYTE_PARAM);
}

void CTec2kVM8::ExecuteJZ()
{
	VM8_JUMP_CONDITION(FlagZero)
}

void CTec2kVM8::ExecuteJNZ()
{
	VM8_JUMP_CONDITION(!FlagZero)
}

void CTec2kVM8::ExecuteJC()
{
	VM8_JUMP_CONDITION(FlagCarry)
}

void CTec2kVM8::ExecuteJNC()
{
	VM8_JUMP_CONDITION(!FlagCarry)
}

void CTec2kVM8::ExecuteJR()
{
	VM8_JUMP_RELATIVE
}

void CTec2kVM8::ExecuteOR()
{
	int dr = VM8_HIGH_REG_INDEX;

	unsigned short resValue = VM8_EXT_REG_VALUE(dr) | VM8_EXT_LOW_REG_VALUE;

	VM8_SET_ALL_FLAGS_ADD(resValue)
	VM8_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM8::ExecuteTEST()
{
	unsigned short resValue = VM8_EXT_HIGH_REG_VALUE & VM8_EXT_LOW_REG_VALUE;

	VM8_SET_ALL_FLAGS_ADD(resValue)
}

void CTec2kVM8::ExecuteADC()
{
	int dr = VM8_HIGH_REG_INDEX;

	unsigned short resValue = VM8_EXT_REG_VALUE(dr) + VM8_EXT_LOW_REG_VALUE +
		(unsigned short)FlagCarry;

	VM8_SET_ALL_FLAGS_ADD(resValue)
	VM8_SET_REG_VALUE(dr, resValue)
}

void CTec2kVM8::ExecuteRCR()
{
	int reg = VM8_LOW_REG_INDEX;

	unsigned short value = Register[reg];
	if (FlagCarry)
		value |= 0x100;
	else
		value &= 0xff;
    FlagCarry = value & 1;

	VM8_SET_REG_VALUE(reg, value >> 1)
}

void CTec2kVM8::ExecuteRCL()
{
	int reg = VM8_LOW_REG_INDEX;

	unsigned short value = Register[reg];
	value <<= 1;
	if (FlagCarry)
		value |= 1;
    FlagCarry = (value & 0x100) != 0;

	VM8_SET_REG_VALUE(reg, value)
}

void CTec2kVM8::ExecuteREAD()
{
 	VM8_GET_WORD_PARAM(*pDataAddr)
	VM8_SET_REG_VALUE(VM8_LOW_REG_INDEX, pMemory[*pDataAddr])
}

void CTec2kVM8::ExecuteWRIT()
{
	VM8_GET_WORD_PARAM(*pDataAddr)

	pMemory[*pDataAddr] = Register[VM8_LOW_REG_INDEX];
}

void CTec2kVM8::ExecuteINPT()
{
}

void CTec2kVM8::ExecuteOUPT()
{
}

void CTec2kVM8::ExecuteJS()
{
	VM8_JUMP_CONDITION(FlagSign)
}

void CTec2kVM8::ExecuteJNS()
{
	VM8_JUMP_CONDITION(!FlagSign)
}

void CTec2kVM8::ExecuteJUMP()
{
	VM8_GET_WORD_PARAM(*pCodeAddr);

	*pPC = *pCodeAddr;
}

void CTec2kVM8::ExecuteHALT()
{
	Stop();
}

void CTec2kVM8::SetRegister(int Index, int Value) 
{
	Register[Index] = Value; 
}

int CTec2kVM8::GetRegister(int Index)
{
	return Register[Index]; 
} 

void CTec2kVM8::WriteToMemory(int StartAddress, int Length, void *Buffer)
{
	memcpy(pMemory + StartAddress, Buffer, Length); 
}

void CTec2kVM8::ReadFromMemory(int StartAddress, int Length, void *Buffer)
{
	memcpy(Buffer, pMemory + StartAddress, Length); 
}

void CTec2kVM8::SetStubAndRun(int StartAddress)
{
	static char StartBuf[] = { 0xda, 0, 0xdb, 0, 0xfc, 0xf0 };
	StartBuf[1] = (char)StartAddress;
	StartBuf[3] = StartAddress >> 8;
	WriteToMemory(0xfff0, sizeof(StartBuf), StartBuf);
	Run(0xfff0);
}

size_t CTec2kVM8::GetWordSize()
{
	return sizeof(*pMemory);
}

char *CTec2kVM8::GetMonitorFileName()
{
	return "monitor8.cod";
}

void CTec2kVM8::GetSendStartLen(int *pStart, int *pLen)
{
	*pStart = *((unsigned short *)(&pMemory[VM8_SEND_DATA_START_ADDRESS]));
	*pLen = *((unsigned short *)(&pMemory[VM8_SEND_DATA_LENGTH]));
}

void CTec2kVM8::SetSendStartLen(int Start, int Len)
{
	*((unsigned short *)(&pMemory[VM8_SEND_DATA_START_ADDRESS])) = Start;
	*((unsigned short *)(&pMemory[VM8_SEND_DATA_LENGTH])) = Len;
}

