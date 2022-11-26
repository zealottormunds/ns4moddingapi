#pragma once
#include <string>
#include <basetsd.h>

class Plugin
{
public:
	__int64 hInstance;
	__int64 afterBoot = 0;
	__int64 fileParser = 0;

	__int64 unload = 0;
	__int64 gameLoop = 0;
	__int64 prerender = 0;
	__int64 postrender = 0;
	__int64 ongui = 0;
	std::string pluginPath = "";
	std::string pluginName = "";

	void __stdcall FreePlugin();
	void __stdcall ReloadLibrary();

	void __stdcall Unload()
	{
		typedef void(__stdcall *fc)();
		fc funct = (fc)(unload);
		if (funct) funct();
	}

	void __stdcall Update()
	{
		typedef void(__stdcall *loopfunct)();
		loopfunct funct = (loopfunct)(gameLoop);
		if (funct) funct();
	}

	void __stdcall PreRender()
	{
		typedef void(__stdcall *loopfunct)();
		loopfunct funct = (loopfunct)(prerender);
		if (funct) funct();
	}

	void __stdcall PostRender()
	{
		typedef void(__stdcall *loopfunct)();
		loopfunct funct = (loopfunct)(postrender);
		if (funct) funct();
	}

	void __stdcall OnGUI(bool s, __int64 hwnd, __int64 imguiContext)
	{
		typedef void(__stdcall *loopfunct)(bool s, __int64 hwnd, __int64 imguiContext);
		loopfunct funct = (loopfunct)(ongui);
		if (funct) funct(s, hwnd, imguiContext);
	}
};