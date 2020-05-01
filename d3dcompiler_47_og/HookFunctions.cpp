#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "HookFunctions.h"

#include "ccMain.h"
#include "d3dcompiler_47_og.h"
#include "ccGeneralGameFunctions.h"
#include "ccBossIAFunctions.h"
#include "ccBattleFunctions.h"
#include "ccPlayer.h"
#include "LuaHook.h"
#include "ccCharacterFunctions.h"
#include "ccGameProperties.h"

using namespace moddingApi;
using namespace std;

// For messageInfo hook
BYTE originalMsgInfo[19];
BYTE originalMsgInfo2[19]; 
BYTE originalInitInfo[14];
BYTE originalInit2Info[17];

//bool Hook(void*, void*, int);
bool Hook2(void*, void*, int);
bool Hook3(void*, void*, int);

// WRITE ALL THE FUNCTIONS YOU WANT TO HOOK IN HERE
void HookFunctions::InitializeHooks()
{
	//ccPlayer::InitAwakening();

	//HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x85CC80), (void*)ccGeneralGameFunctions::GetVersionStringAPI, 14); // GetVersionString hook
	//HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x8607EC), (void*)ccGeneralGameFunctions::GetVersionStringAPI, 14);

	memcpy(originalMsgInfo, (void*)(d3dcompiler_47_og::moduleBase + 0xAB7BF0), 19); // Fixed
	HookFunctions::DoMessageInfoHook();
	memcpy(originalMsgInfo2, (void*)(d3dcompiler_47_og::moduleBase + 0xAB7CA0), 19); // Fixed
	HookFunctions::DoMessageInfoHook2();


	//LuaHook::HookDeclareFunction();
	// NOT FIXED YET!
	
	//HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x450A14), (void*)LuaHook::GetPadState, 20);
	// NOT FIXED YET!
	
	//HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x450E28), (void*)LuaHook::ccGroupBattleEventCameraMovePosBeginCoop, 14);

	// Hook charsel
	//ccCharacterFunctions::DoCharacterSelectParamHook();

	// Game properties hook
	//ccGameProperties::DoGamePropertiesHook();

	// Init game hook
	//ccGameProperties::DoInitHook();

	// AutoSaveCaution
	//ccGameProperties::DoAutoSaveHook();

	// Game Info Hook
	//ccGeneralGameFunctions::DoGameInfoHook();

	// Test NOT FIXED YET!!!
	ccCharacterFunctions::PartnerFunctions();
	ccCharacterFunctions::SpecialCondFunctions();
	//ccCharacterFunctions::Hook_COND_BKKX();
}

void HookFunctions::DoMessageInfoHook()
{
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0xAB7BF0), (void*)ccGeneralGameFunctions::Hook_MsgToString, 19);
}

void HookFunctions::UndoMessageInfoHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xAB7BF0), 19, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xAB7BF0), originalMsgInfo, 19);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xAB7BF0), 19, dwOld, &dwOld);
}

void HookFunctions::DoMessageInfoHook2()
{
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0xAB7CA0), (void*)ccGeneralGameFunctions::Hook_MsgToString_Alt, 19);
}

void HookFunctions::UndoMessageInfoHook2()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xAB7CA0), 19, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xAB7CA0), originalMsgInfo2, 19);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xAB7CA0), 19, dwOld, &dwOld);
}

// FUNCTION TO HOOK
bool HookFunctions::Hook(void * toHook, void * ourFunct, int len)
{
	DWORD MinLen = 14;

	if (len < MinLen)
	{
		return false;
	}

	BYTE stub[] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
	};

	void* pTrampoline = VirtualAlloc(0, len + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	DWORD dwOld = 0;

	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &dwOld);

	DWORD64 retto = (DWORD64)toHook + len;

	// trampoline
	memcpy(stub + 6, &retto, 8);
	memcpy((void*)((DWORD_PTR)pTrampoline), toHook, len);
	memcpy((void*)((DWORD_PTR)pTrampoline + len), stub, sizeof(stub));

	// orig
	memcpy(stub + 6, &ourFunct, 8);
	memcpy(toHook, stub, sizeof(stub));

	for (int i = MinLen; i < len; i++)
	{
		*(BYTE*)((DWORD_PTR)toHook + i) = 0x90;
	}
	VirtualProtect(toHook, len, dwOld, &dwOld);

	return true;
}

// FUNCTION TO HOOK 2
bool Hook2(void * toHook, void * ourFunct, int len)
{
	DWORD MinLen = 14;

	if (len < MinLen)
	{
		return false;
	}

	BYTE replace[] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
	};

	BYTE newFunc[] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ptr

					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

					0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ptr
	};

	void* pTrampoline = VirtualAlloc(0, 42, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	DWORD dwOld = 0;

	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &dwOld);

	DWORD_PTR newFuncEnd_Jmp = (DWORD_PTR)toHook + len;

	// trampoline
	memcpy(replace + 6, &pTrampoline, 8);
	memcpy(newFunc + 6, &ourFunct, 8);
	memcpy(newFunc + 14, toHook, len);
	memcpy(newFunc + 34, &newFuncEnd_Jmp, 8);

	memcpy((void*)((DWORD_PTR)pTrampoline), &newFunc, 42);
	memcpy(toHook, replace, sizeof(replace));

	cout << "ourFunct: " << std::hex << (DWORD_PTR)ourFunct << endl;
	cout << "toHook: " << std::hex << (DWORD_PTR)toHook << endl;
	cout << "tramp: " << std::hex << (DWORD_PTR)pTrampoline << endl;
	for (int x = 0; x < 42; x++)
	{
		cout << "0x" << std::hex << (int)newFunc[x] << " ";
	}

	cout << endl;

	for (int i = MinLen; i < len; i++)
	{
		*(BYTE*)((DWORD_PTR)toHook + i) = 0x90;
	}
	VirtualProtect(toHook, len, dwOld, &dwOld);

	return true;
}

// DoHook and UndoHook
vector<string> HookID;
vector<vector<BYTE>> HookBytes;
vector<uintptr_t> HookAddress;
void DoHook(void* toHook, void* ourFunct, int len, string ID)
{
	int Count = -1;
	for (int x = 0; x < HookID.size(); x++)
	{
		if (ID == HookID[x])
		{
			Count = x;
		}
	}

	if (Count == -1)
	{
		HookID.push_back(ID);
		HookAddress.push_back((uintptr_t)toHook);
		vector<BYTE> originalFunction;

		for (int x = 0; x < len; x++)
		{
			originalFunction.push_back(*(BYTE*)((uintptr_t)toHook + x));
		}

		HookBytes.push_back(originalFunction);

		HookFunctions::Hook(toHook, ourFunct, len);
	}
	else
	{
		HookFunctions::Hook(toHook, ourFunct, len);
	}
}
void UndoHook(string ID)
{
	int Count = -1;
	for (int x = 0; x < HookID.size(); x++)
	{
		if (ID == HookID[x])
		{
			Count = x;
		}
	}

	if (Count != -1)
	{
		DWORD dwOld = 0;
		VirtualProtect((void*)(HookAddress[Count]), HookBytes[Count].size(), PAGE_EXECUTE_READWRITE, &dwOld);

		cout << "len: " << HookBytes[Count].size() << endl;

		for (int x = 0; x < HookBytes[Count].size(); x++)
		{
			memcpy((void*)(HookAddress[Count]), &HookBytes[Count][x], 1);
		}
		VirtualProtect((void*)(HookAddress[Count]), HookBytes[Count].size(), dwOld, &dwOld);

		cout << "Unhooked function at " << std::hex << HookAddress[Count] << endl;
	}
}

//memcpy(originalInit2Info, (void*)(d3dcompiler_47_og::moduleBase + 0x85AE80), 17);
//HookFunctions::DoInitializeHook2();
//memcpy(originalInitInfo, (void*)(d3dcompiler_47_og::moduleBase + 0x85175C), 14);
//HookFunctions::DoInitializeHook();
//ccPlayer::DoCtrlHook();
//ccPlayer::DoMovementHook();
//HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x746360), (void*)ccBattleFunctions::Battle_FillChakra, 17); // Battle_FillChakra hook
//HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7463E8), (void*)ccBattleFunctions::Battle_FillSubstitution, 17); // Battle_FillSubstitution hook
//HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x56AA34), (void*)ccGeneralGameFunctions::Cpk_LoadXfbin, 17);