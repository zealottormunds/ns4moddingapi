#include <WinSock2.h>
#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Psapi.h>

#include "Common.h"
#include "xinput9_1_0.h"
#include "NS4Framework.h"

#pragma warning( disable: 4305 )
#pragma warning( disable: 4307 )

using namespace std;

__int64 moduleBase = 0;
__int64 moduleLength = 0;
__int64 st_hModule = 0;
__int64 datasection = 0;

std::string gameVersion = "null";
bool isDebug = false;

HINSTANCE mHinst = 0, mHinstDLL = 0;
extern "C" UINT_PTR mProcs[5] = { 0 };

LPCSTR mImportNames[] = { "DllMain", "XInputGetCapabilities", "XInputGetDSoundAudioDeviceGuids", "XInputGetState", "XInputSetState" };
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved, HMODULE hModule)
{
	mHinst = hinstDLL;

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		mHinstDLL = LoadLibrary("xinput9_1_0_o.dll");
		if (!mHinstDLL) return (FALSE);
		for (int i = 0; i < 5; i++) mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);

		MODULEINFO mInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &mInfo, sizeof(MODULEINFO));

		moduleBase = (uintptr_t)GetModuleHandle(NULL) + 0xC00;
		moduleLength = mInfo.SizeOfImage;
		st_hModule = (uintptr_t)hModule;
		datasection = (uintptr_t)GetModuleHandle(NULL) + 0x13B6000; // Needs to be fixed

		// Start API
		NS4Framework::Main();
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(mHinstDLL);
	}

	return (TRUE);
}

extern "C" void DllMain_wrapper();
extern "C" void XInputGetCapabilities_wrapper();
extern "C" void XInputGetDSoundAudioDeviceGuids_wrapper();
extern "C" void XInputGetState_wrapper();
extern "C" void XInputSetState_wrapper();