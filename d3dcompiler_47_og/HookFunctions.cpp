#include <stdio.h>
#include <iostream>
#include <string>

#include <WinSock2.h>
#include <Windows.h>

#include "Common.h"
#include "ccGeneralGameFunctions.h"
#include "HookFunctions.h"
#include "PatternScan.h"
#include "ModManager.h"
#include "DirectX.h"

#include "CpkLoader.h"
#include "NS4Framework.h"

#include "PartnerManager.h"
#include "SpecialConditionManager.h"

using namespace moddingApi;
using namespace std;

// For messageInfo hook
BYTE originalMsgInfo[19];
BYTE originalMsgInfo2[19]; 
BYTE originalInitInfo[14];
BYTE originalInit2Info[17];

__int64 HookFunctions::fc_msgtostring = 0xAB8720;
__int64 HookFunctions::fc_msgtostring_3 = 0xAB87D0;

// This is used to hook game functions with your own (you can replace original functions and add your own code to them)
void HookFunctions::InitializeHooks()
{
	int msgHookLength = 0;

	if (gameVersion != "1.09")
	{
		cout << "NS4Framework :: Pattern scanning has begun. This process may take a few seconds." << endl;

		isDebug = (PatternScan::Scan("636344656275674D656E75") > 0);
		if (isDebug) cout << "NS4Framework :: Debug version detected" << endl;
		else cout << "NS4Framework :: Release version detected" << endl;

		if (isDebug == false)
		{
			msgHookLength = 19;
			fc_msgtostring = (PatternScan::Scan("48xxxxxx48xxxx74xx48xxxx48xxxxxxxxxxxxE8xxxxxxxx48xxxx74xx48xxxxxx48xxxx") - moduleBase);
			fc_msgtostring_3 = (PatternScan::Scan("48xxxxxx48xxxx74xx48xxxx48xxxxxxxxxxxxE8xxxxxxxx48xxxx48xxxxxxxxxxxx48xxxx74xx48xxxxxx48xxxx") - moduleBase);
		}
		else
		{
			msgHookLength = 14;
			fc_msgtostring = (PatternScan::Scan("48xxxxxxxx48xxxxxxB9xxxxxxxxE8xxxxxxxx85xx74xxE8xxxxxxxx48xxxxE8xxxxxxxx48xxxxxxxx48xxxxE8xxxxxxxx83xxxxxxxxxxxx74xx48xxxxxxxx") - moduleBase);
			fc_msgtostring_3 = (PatternScan::Scan("48xxxxxxxx48xxxxxxB9xxxxxxxxE8xxxxxxxx85xx74xxE8xxxxxxxx48xxxxE8xxxxxxxx48xxxxxxxx48xxxxE8xxxxxxxx83xxxxxxxxxxxx74xx48xxxxxxxx", moduleBase + fc_msgtostring + 1) - moduleBase);
		}

		cout << "NS4Framework :: Pattern scanning has finished." << endl;
	}
	else
	{
		msgHookLength = 19;
		fc_msgtostring = 0xAB8720;
		fc_msgtostring_3 = 0xAB87D0;
	}

	memcpy(originalMsgInfo, (void*)(moduleBase + HookFunctions::fc_msgtostring), msgHookLength);
	HookFunctions::DoMessageInfoHook(msgHookLength);

	memcpy(originalMsgInfo2, (void*)(moduleBase + HookFunctions::fc_msgtostring_3), msgHookLength);
	HookFunctions::DoMessageInfoHook2(msgHookLength);

	// Hook Cpk Load
	if (gameVersion == "1.09")
	{
		HookFunctions::Hook((void*)(moduleBase + 0x854F3C), CpkLoader::LoadCpkInitial, 15);
		SpecialConditionManager::SpecialCondFunctions();
	}

	// Partner function
	__int64 partnerFunctionAddress = PatternScan::Scan("33xx48xxxxxxxxxxxx3Bxx74xx4Cxxxxxxxxxxxx48xxxxxxFFxx49xxxx7Cxx");
	if(partnerFunctionAddress > 1) HookFunctions::Hook((void*)(partnerFunctionAddress), PartnerManager::CreatePartner, 20);

	// Initialize plugin hooks
	InitializePluginHooks();
}

// Iterate through all the plugins, and apply their hooks.
void HookFunctions::InitializePluginHooks()
{
	std::vector<Mod*> modList = ModManager::GetModList();
	int modCount = modList.size();
	for (int mod = 0; mod < modCount; mod++)
	{
		Mod * m = modList[mod];

		std::vector<Plugin*> pluginList = m->pluginList;
		int pluginCount = pluginList.size();
		for (int plugin = 0; plugin < pluginCount; plugin++)
		{
			Plugin * p = pluginList[plugin];
			HINSTANCE hGetProcIDDLL = (HINSTANCE)(p->hInstance);

			typedef void(__stdcall *hookfunct)(__int64 moduleBase, __int64 hookFunction);
			hookfunct funct = (hookfunct)GetProcAddress(hGetProcIDDLL, "InitializeHooks");
			if (funct) funct(moduleBase, (__int64)HookFunctions::HookPlugin);
		}
	}
}

// This function is used for adding custom game messages. Perhaps not the most effective way to do it, as we're hooking and unhooking every time we need to translate a message.
void HookFunctions::DoMessageInfoHook(int length)
{
	HookFunctions::Hook((void*)(moduleBase + fc_msgtostring), (void*)ccGeneralGameFunctions::Hook_MsgToString, length);
}

void HookFunctions::UndoMessageInfoHook(int length)
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(moduleBase + fc_msgtostring), length, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(moduleBase + fc_msgtostring), originalMsgInfo, length);
	VirtualProtect((void*)(moduleBase + fc_msgtostring), length, dwOld, &dwOld);
}

// This function is also used for adding custom game messages. Functionality is the same as the two functions above.
void HookFunctions::DoMessageInfoHook2(int length)
{
	HookFunctions::Hook((void*)(moduleBase + fc_msgtostring_3), (void*)ccGeneralGameFunctions::Hook_MsgToString_Alt, length);
}

// Fixed
void HookFunctions::UndoMessageInfoHook2(int length)
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(moduleBase + fc_msgtostring_3), length, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(moduleBase + fc_msgtostring_3), originalMsgInfo2, length);
	VirtualProtect((void*)(moduleBase + fc_msgtostring_3), length, dwOld, &dwOld);
}

std::vector<__int64> HookFunctions::PluginHookAddress;
std::vector<__int64> HookFunctions::PluginHookOriginal;
std::vector<int> HookFunctions::PluginHookLength;

// Credits for this function to: GuidedHacking, Broihon, Traxin & A200K
bool HookFunctions::Hook(void * toHook, void * ourFunct, int len, bool isPlugin)
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

	if (isPlugin)
	{
		void* originalBytes = VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		memcpy(originalBytes, toHook, len);

		PluginHookAddress.push_back((__int64)toHook);
		PluginHookOriginal.push_back((__int64)originalBytes);
		PluginHookLength.push_back(len);
	}

	memcpy(toHook, stub, sizeof(stub));

	for (int i = MinLen; i < len; i++)
	{
		*(BYTE*)((DWORD_PTR)toHook + i) = 0x90;
	}
	VirtualProtect(toHook, len, dwOld, &dwOld);

	return true;
}

// Function used to hook
bool HookFunctions::HookPlugin(void * toHook, void * ourFunct, int len)
{
	return Hook(toHook, ourFunct, len, true);
}

void HookFunctions::UnhookPlugins()
{
	for (int x = 0; x < PluginHookAddress.size(); x++)
	{
		void* address = (void*)PluginHookAddress[x];
		void* bytes = (void*)PluginHookOriginal[x];
		int len = PluginHookLength[x];

		DWORD dwOld = 0;
		VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy(address, bytes, len);
		VirtualProtect(address, len, dwOld, &dwOld);

		VirtualFree((void*)PluginHookOriginal[x], len, MEM_RESET);
	}

	PluginHookAddress.clear();
	PluginHookOriginal.clear();
	PluginHookLength.clear();
}