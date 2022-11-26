#include "Plugin.h"
#include <WinSock2.h>
#include <Windows.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Common.h"
#include "HookFunctions.h"

using namespace std;

void __stdcall Plugin::FreePlugin()
{
	Unload();
	std::cout << "NS4Framework :: Freeing " + pluginPath << std::endl;
	FreeLibrary((HMODULE)hInstance);

	hInstance = 0;
	afterBoot = 0;
	fileParser = 0;
	unload = 0;
	gameLoop = 0;
	prerender = 0;
	postrender = 0;
	ongui = 0;
}

void __stdcall Plugin::ReloadLibrary()
{
	std::cout << "NS4Framework :: Attempting to reload " + pluginPath << std::endl;

	HINSTANCE hGetProcIDDLL = LoadLibrary(pluginPath.c_str());
	hInstance = (__int64)hGetProcIDDLL;

	if (hInstance)
	{
		// InitializePlugin
		typedef void(__stdcall *funct)(__int64 moduleBase, std::vector<__int64> deprecated);
		funct InitializePlugin = (funct)GetProcAddress(hGetProcIDDLL, "InitializePlugin");
		std::vector<__int64> a;
		if (InitializePlugin) InitializePlugin(moduleBase, a);
		else cout << "NS4Framework :: InitializePlugin() function not found" << endl;

		// Get GameLoop
		funct functloop = (funct)GetProcAddress(hGetProcIDDLL, "GameLoop");
		if (functloop) gameLoop = (__int64)functloop;

		// Get AfterBoot
		funct functafterboot = (funct)GetProcAddress(hGetProcIDDLL, "AfterBoot");
		if (functafterboot) afterBoot = (__int64)functafterboot;

		// Get Unload
		funct functunload = (funct)GetProcAddress(hGetProcIDDLL, "Unload");
		if (functunload) unload = (__int64)functunload;

		// Get ParseFile
		funct functparsefile = (funct)GetProcAddress(hGetProcIDDLL, "ParseFile");
		if (functparsefile) fileParser = (__int64)functparsefile;

		// Get PreRender
		funct functprerender = (funct)GetProcAddress(hGetProcIDDLL, "PreRender");
		if (functprerender) prerender = (__int64)functprerender;

		// Get OnGUI
		funct functpostrender = (funct)GetProcAddress(hGetProcIDDLL, "PostRender");
		if (functpostrender) postrender = (__int64)functpostrender;

		// Get PostRender
		funct functongui = (funct)GetProcAddress(hGetProcIDDLL, "OnGUI");
		if (functongui) ongui = (__int64)functongui;

		typedef void(__stdcall *hookfunct)(__int64 moduleBase, __int64 hookFunction);
		hookfunct hook = (hookfunct)GetProcAddress(hGetProcIDDLL, "InitializeHooks");
		if (hook) hook(moduleBase, (__int64)HookFunctions::HookPlugin);
	}

	std::cout << "NS4Framework :: Reloaded plugin sucessfully" << std::endl;
}