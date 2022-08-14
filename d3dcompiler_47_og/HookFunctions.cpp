#include <stdio.h>
#include <iostream>
#include <string>

#include "HookFunctions.h"

#include "ccMain.h"
#include "d3dcompiler_47_og.h"
#include "ccGeneralGameFunctions.h"
#include "ccPlayer.h"
#include "LuaHook.h"
#include "ccCharacterFunctions.h"
#include "ccGameProperties.h"

#include "CameraControl.h"
#include "BattleFunctions.h"
#include "GameSettings.h"

using namespace moddingApi;
using namespace std;

// For messageInfo hook
BYTE originalMsgInfo[19];
BYTE originalMsgInfo2[19]; 
BYTE originalInitInfo[14];
BYTE originalInit2Info[17];

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
void HookFunctions::InitializeHooks()
{
	CreateVersionString();

	memcpy(originalMsgInfo, (void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring), 19); // Fixed
	HookFunctions::DoMessageInfoHook();
	memcpy(originalMsgInfo2, (void*)(d3dcompiler_47_og::moduleBase + fc_msgtostring_3), 19); // Fixed
	HookFunctions::DoMessageInfoHook2();

	LuaHook::HookDeclareFunction();

	// Hook Cpk Load
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x854F3C), GameSettings::LoadCpkInitial, 15);

	ccCharacterFunctions::PartnerFunctions();
	ccCharacterFunctions::SpecialCondFunctions();

	// Load plugin hooks
	for (int actualPlugin = 0; actualPlugin < ccMain::PluginList.size(); actualPlugin++)
	{
		HINSTANCE hGetProcIDDLL = ccMain::PluginList.at(actualPlugin);

		typedef void(__stdcall *hookfunct)(__int64 moduleBase, __int64 hookFunction);
		hookfunct funct = (hookfunct)GetProcAddress(hGetProcIDDLL, "InitializeHooks");

		if (funct) funct(d3dcompiler_47_og::moduleBase, (__int64)HookFunctions::Hook);
	}
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