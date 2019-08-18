#pragma once

#include <stdio.h>
#include <windows.h>

using namespace std;

namespace moddingApi
{
	class ccPlayer
	{
	public:
		static int AfterCharacterCollision(uintptr_t);

		static BYTE CtrlBytes[15];
		static int Ctrl(uintptr_t, uintptr_t);
		static void DoCtrlHook();
		static void UndoCtrlHook();

		static int CtrlCounterSimul(uintptr_t);
		static int Draw(uintptr_t);
		static int PostCtrl(uintptr_t);

		static void DoMovementHook();
		static void UndoMovementHook();

		// Awakening funtions:
		static BYTE OriginalAwakeningFunction[20];
		static void InitAwakening();
		static bool AwakeDebugEnabled;
		static char** GetAwakeningID(int);
		static void DoGetAwakeningIDHook();
		static void UndoGetAwakeningIDHook();
	};
}