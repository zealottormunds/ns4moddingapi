#ifndef CCMAIN_H 
#define CCMAIN_H
#pragma once

#include <vector>

class NS4Framework
{
public:
	static int __stdcall Main();
	static int __stdcall LoopConsole();
	static int __stdcall LoopGame();

	static void Update();
	static void PreRender();
	static void PostRender();
	static void OnGUI(bool s, __int64 hwnd, __int64 imguiContext);

	static void ReadFrameworkFiles(bool isReloading = false);
	static void UnloadPlugins();
};

#endif