#pragma once

#include <vector>
using namespace std;

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

		static bool Hook(void*, void*, int);

		//static void DoHook(uintptr_t address, void* originalDest, int len, void* funct);
		//static void UndoHook(uintptr_t address, void* originalDest, int len);
	};
}