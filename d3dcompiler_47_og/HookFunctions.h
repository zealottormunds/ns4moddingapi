#ifndef HOOKFUNCTIONS_H 
#define HOOKFUNCTIONS_H
#pragma once

#include <vector>

class HookFunctions
{
public:
	static void InitializeHooks();
	static void InitializePluginHooks();

	static __int64 fc_msgtostring;
	static __int64 fc_msgtostring_3;

	static void DoMessageInfoHook(int length);
	static void UndoMessageInfoHook(int length);

	static void DoMessageInfoHook2(int length);
	static void UndoMessageInfoHook2(int length);

	static bool Hook(void*, void*, int, bool isPlugin = false);
	static bool HookPlugin(void*, void*, int);
	static void UnhookPlugins();

	static std::vector<__int64> PluginHookAddress;
	static std::vector<__int64> PluginHookOriginal;
	static std::vector<int> PluginHookLength;
};

#endif