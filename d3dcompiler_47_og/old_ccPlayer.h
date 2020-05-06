/*static int AfterCharacterCollision(uintptr_t);

static BYTE CtrlBytes[15];
static int Ctrl(uintptr_t, uintptr_t);
static void DoCtrlHook();
static void UndoCtrlHook();

static int CtrlCounterSimul(uintptr_t);
static int Draw(uintptr_t);
static int PostCtrl(uintptr_t);

static void DoMovementHook();
static void UndoMovementHook();

// Awakening funtions:
static BYTE OriginalAwakeningFunction[20];
static void InitAwakening();
static bool AwakeDebugEnabled;
static char** GetAwakeningID(int);
static void DoGetAwakeningIDHook();
static void UndoGetAwakeningIDHook();*/

/*int ccPlayer::AfterCharacterCollision(uintptr_t a1)
{
	cout << "AfterCharacterCollision -> " << *(int*)(a1 + 0xB28) << endl;
	return *(int*)(a1 + 0xB28);
}

typedef int (__fastcall * g_ccplayer_ctrl)(uintptr_t, uintptr_t);
g_ccplayer_ctrl g_ccPlayer_Ctrl;

int ccPlayer::Ctrl(uintptr_t a1, uintptr_t a2)
{
	g_ccPlayer_Ctrl = (g_ccplayer_ctrl)(d3dcompiler_47_og::moduleBase + 0x76EA50);

	cout << "ccPlayer::Ctrl -> " << std::hex << a1 << ", " << a2 << endl;

	//ccPlayer::UndoCtrlHook();
	//int a = g_ccPlayer_Ctrl(a1, a2);
	//ccPlayer::DoCtrlHook();
	int a = 0;
	return a;
}

BYTE ccPlayer::CtrlBytes[15];

void ccPlayer::DoCtrlHook()
{
	memcpy(ccPlayer::CtrlBytes, (void*)(d3dcompiler_47_og::moduleBase + 0x76EA50), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x76EA50), (void*)ccPlayer::Ctrl, 15);
}

void ccPlayer::UndoCtrlHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x76EA50), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x76EA50), CtrlBytes, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x85175C), 15, dwOld, &dwOld);
}

int ccPlayer::CtrlCounterSimul(uintptr_t)
{

}

int ccPlayer::Draw(uintptr_t)
{

}

int ccPlayer::PostCtrl(uintptr_t)
{

}

typedef int(__fastcall * g_obj_writepos)(uintptr_t, uintptr_t);
g_obj_writepos g_Obj_WritePos;

int Test(uintptr_t a1, uintptr_t a2)
{
	g_Obj_WritePos = (g_obj_writepos)(d3dcompiler_47_og::moduleBase + 0xABEEF0);

	//if ((*(float*)(a2 + 0x70) > 100.0f && *(float*)(a2 + 0x70) < 200.0f) || (*(float*)(a2 + 0x74) > 100.0f && *(float*)(a2 + 0x74) < 200.0f) || (*(float*)(a2 + 0x78) > 100.0f && *(float*)(a2 + 0x78) < 200.0f) || (*(float*)(a2 + 0x7C) > 100.0f && *(float*)(a2 + 0x7C) < 200.0f))
	//{
		cout << "Destination: " << std::hex << a1 << ", Source: " << std::hex << a2 << endl;
	//}

	ccPlayer::UndoMovementHook();
	int a = g_Obj_WritePos(a1, a2);
	ccPlayer::DoMovementHook();

	return a;
}

BYTE originalBytes[16];
void ccPlayer::DoMovementHook()
{
	memcpy(originalBytes, (void*)(d3dcompiler_47_og::moduleBase + 0xABEEF0), 16);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0xABEEF0), (void*)Test, 16);
}

void ccPlayer::UndoMovementHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xABEEF0), 16, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xABEEF0), originalBytes, 16);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xABEEF0), 16, dwOld, &dwOld);
}

// Awakening functions
BYTE ccPlayer::OriginalAwakeningFunction[20];
typedef char**(__fastcall * fc_getawakeningid)(int a1);
fc_getawakeningid fc_GetAwakeningID;
char* ExtraIDs[5] = { "AWAKE_2CMN", "AWAKE_2CMN_REAC", "AWAKE_3CMN", "AWAKE_3CMN_REAC", "ITEMTEST" };
int Extra = 5;
uintptr_t FirstPointer = -1;
void ccPlayer::InitAwakening()
{
	FirstPointer = (uintptr_t)malloc(sizeof(uintptr_t) * Extra);

	for (int x = 0; x < Extra; x++)
	{
		*(uintptr_t*)(FirstPointer + (sizeof(uintptr_t) * x)) = (uintptr_t)&ExtraIDs[x];
	}
}

bool ccPlayer::AwakeDebugEnabled = false;
char** ccPlayer::GetAwakeningID(int ActualID)
{
	char ** a;
	//ActualID = 471;
	if (ccPlayer::AwakeDebugEnabled) cout << ActualID << endl;

	if (ActualID <= 470)
	{
		fc_GetAwakeningID = (fc_getawakeningid)(d3dcompiler_47_og::moduleBase + 0x7693D4);

		//if(ccPlayer::AwakeDebugEnabled) cout << ActualID << endl;

		ccPlayer::UndoGetAwakeningIDHook();

		//cout << "Getting real ID..." << endl;

		a = fc_GetAwakeningID(ActualID);
		if(ActualID == 470) cout << std::hex << a << endl;

		//cout << "Got ID" << endl;

		ccPlayer::DoGetAwakeningIDHook();

		cout << a << endl;

		//return a;
	}
	else
	{
		int NewID = ActualID - 470 - 1;

		if (NewID < Extra)
		{
			cout << "Getting new ID" << endl;
			a = (char**)*(uintptr_t*)(FirstPointer + (sizeof(uintptr_t) * NewID));
			cout << std::hex << a << endl;
		}
		else
		{
			cout << "Getting dummy ID" << endl;
			a = ccPlayer::GetAwakeningID(0);
		}
	}

	return a;
}

void ccPlayer::DoGetAwakeningIDHook()
{
	memcpy(OriginalAwakeningFunction, (void*)(d3dcompiler_47_og::moduleBase + 0x7693D4), 20);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7693D4), (void*)ccPlayer::GetAwakeningID, 20);
}

void ccPlayer::UndoGetAwakeningIDHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x7693D4), 20, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x7693D4), OriginalAwakeningFunction, 20);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x7693D4), 20, dwOld, &dwOld);
}*/