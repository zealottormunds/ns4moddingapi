#ifndef HOOKFUNCTIONS_H 
#define HOOKFUNCTIONS_H
#pragma once

#include <vector>

namespace moddingApi
{
	class HookFunctions
	{
	public:
		static void InitializeHooks();

		static void DoMessageInfoHook();
		static void UndoMessageInfoHook();

		static void DoMessageInfoHook2();
		static void UndoMessageInfoHook2();

		static void DoMessageInfoHook3();
		static void UndoMessageInfoHook3();

		static bool Hook(void*, void*, int);

		static void HookFade();
		static uintptr_t HookQuick(char* a1);

		//static void DoHook(uintptr_t address, void* originalDest, int len, void* funct);
		//static void UndoHook(uintptr_t address, void* originalDest, int len);
	};
}

#endif