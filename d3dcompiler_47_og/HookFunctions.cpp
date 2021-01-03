#include <WinSock2.h>
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
#include "PrmFunctions.h"

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

void DoMeHook()
{
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7F49C8), (void*)ccPlayer::meTest, 18);
}

int fc_msgtostring = 0xAB8720;
int fc_msgtostring_3 = 0xAB87D0;

void CreateVersionString()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x861ACB), 3, PAGE_EXECUTE_READWRITE, &dwOld);
	BYTE newOffset[] = { 0xE1, 0x7F, 0x88 };
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x861ACB), newOffset, 3);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x861ACB), 3, dwOld, &dwOld);

	dwOld = 0;
	char* destination = (char*)(d3dcompiler_47_og::RecalculateAddress(0x10E96B0));
	VirtualProtect((void*)(d3dcompiler_47_og::RecalculateAddress(0x10E96B0)), 0x64, PAGE_EXECUTE_READWRITE, &dwOld);
	char* version = "1.09 (Storm 4 Modding API by Zealot Tormunds)";
	strcpy(destination, version);
	VirtualProtect((void*)(d3dcompiler_47_og::RecalculateAddress(0x10E96B0)), 0x64, dwOld, &dwOld);

	cout << "Created version string in " << std::hex << d3dcompiler_47_og::RecalculateAddress(0x10E96B0) << endl;
}

// WRITE ALL THE FUNCTIONS YOU WANT TO HOOK IN HERE

void HookFade();
int HookQuick(unsigned int a1, unsigned int a2);

void HookFunctions::InitializeHooks()
{
	CreateVersionString();

	// PrmFunctions::ImplementFunctions();
	// DoMeHook();

	memcpy(originalMsgInfo, (void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring), 19); // Fixed
	HookFunctions::DoMessageInfoHook();
	memcpy(originalMsgInfo2, (void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring_3), 19); // Fixed
	HookFunctions::DoMessageInfoHook2();

	LuaHook::HookDeclareFunction();

	// HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x450A14), (void*)LuaHook::GetPadState, 20);	
	// HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x450E28), (void*)LuaHook::ccGroupBattleEventCameraMovePosBeginCoop, 14);
	// ccCharacterFunctions::DoCharacterSelectParamHook();
	// ccGameProperties::DoGamePropertiesHook();
	// ccGameProperties::DoInitHook();
	// ccGameProperties::DoAutoSaveHook();
	// ccGeneralGameFunctions::DoGameInfoHook();

	ccCharacterFunctions::PartnerFunctions();
	ccCharacterFunctions::SpecialCondFunctions();
}

void HookFade()
{
	cout << "Hooking fade" << endl;
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x537470), (void*)HookQuick, 16);
}

int HookQuick(unsigned int a1, unsigned int a2)
{
	cout << "A1: " << a1 << ", A2: " << a2 << endl;

	return 0;
}

// Fixed
void HookFunctions::DoMessageInfoHook()
{
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring), (void*)ccGeneralGameFunctions::Hook_MsgToString, 19);
}

// Fixed
void HookFunctions::UndoMessageInfoHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring), 19, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring), originalMsgInfo, 19);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring), 19, dwOld, &dwOld);
}

// Fixed
void HookFunctions::DoMessageInfoHook2()
{
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring_3), (void*)ccGeneralGameFunctions::Hook_MsgToString_Alt, 19);
}

// Fixed
void HookFunctions::UndoMessageInfoHook2()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring_3), 19, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring_3), originalMsgInfo2, 19);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring_3), 19, dwOld, &dwOld);
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