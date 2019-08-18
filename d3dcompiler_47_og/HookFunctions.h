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

		//static vector<string> HookID;
		//static vector<vector<BYTE>> HookBytes;
		//static vector<uintptr_t> HookAddress;
		static void DoHook(void*, void*, int, string);
		static void UndoHook(string);
	};
}