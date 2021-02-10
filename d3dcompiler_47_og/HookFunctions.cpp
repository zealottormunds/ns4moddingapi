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

#include "CameraControl.h"
#include "BattleFunctions.h"
#include "GameSettings.h"
#include "ccBoss02_2Phase01Manager.h"

using namespace moddingApi;
using namespace std;

// For messageInfo hook
BYTE originalMsgInfo[19];
BYTE originalMsgInfo2[19]; 
BYTE originalInitInfo[14];
BYTE originalInit2Info[17];

//bool Hook(void*, void*, int);
bool Hook2(void*, void*, int);

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

	// Hook Boss
	// HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x27F0A0), ccBoss02_2Phase01Manager::BossBattleBKKU_Loop00, 20);

	// Hook Substitution Modifier
	// HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7DE9C0), BattleFunctions::ChangeSubstitutionState, 18);

	// Hook Camera Controller
	// HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x74353C), CameraControl::CameraControllerMain, 14);

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

void HookFunctions::HookFade()
{
	cout << "Hooking" << endl;
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x6E07C4), (void*)HookQuick, 20);
}

int sceneToLoad = 2;
char* sceneName[] = { "ccSceneTitle", "ccSceneGameModeSelect", "ccSceneAdventure" };
int sceneMalloc[] = { 0x140, 0x168, 0x1608 };
int sceneAddress[] = { 0x71BA70, 0x6EAB74, 0x6CAAAC };

uintptr_t HookFunctions::HookQuick(char* a1)
{
	cout << "A1: " << a1 << endl;

	void * v2 = malloc(sceneMalloc[sceneToLoad]);
	void * v3 = 0;

	// 0x71BA70 ccSceneTitle_00
	typedef void*(__fastcall * funct)(void * m);
	funct ccSceneInit;
	ccSceneInit = (funct)(d3dcompiler_47_og::moduleBase + sceneAddress[sceneToLoad]);
	v3 = ccSceneInit(v2);

	// 0xAB3950 fc_ccSceneLoader_00
	typedef void(__fastcall * funct1)(void * p1, char * p2);
	funct1 fc_ccSceneLoader_00;
	fc_ccSceneLoader_00 = (funct1)(d3dcompiler_47_og::moduleBase + sceneAddress[sceneToLoad]);
	fc_ccSceneLoader_00(v3, sceneName[sceneToLoad]);

	cout << "V3: " << std::hex << v3 << endl;

	return (uintptr_t)v3;
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