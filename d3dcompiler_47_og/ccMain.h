#ifndef CCMAIN_H 
#define CCMAIN_H
#pragma once

#include <vector>
#include <WinSock2.h>
#include <Windows.h>

namespace moddingApi
{
	class ccMain
	{
	public:
		static DWORD WINAPI Main();
		static DWORD WINAPI LoopConsole();
		static DWORD WINAPI LoopGame();
		static void ReadApiFiles();

		// Mod list variables:
		static int ModCount;
		static std::vector<std::string> ModList;
		static std::vector<std::string> ModDesc;
		static std::vector<std::string> ModAuth;
		static std::vector<BYTE> ModState;

		// Plugins
		static std::vector<HINSTANCE> PluginList;
		static std::vector<__int64> PluginLoop;

		// Reload API files
		static void ReloadParamFiles();
	};
}

#endif