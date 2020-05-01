#pragma once

#include <vector>
using namespace std;

namespace moddingApi
{
	class LuaHook
	{
	public:
		static signed __int64 __fastcall funct_getArgument_number(__int64 a1, unsigned int a2, int a3, __int64 a4);
		static signed __int64 __fastcall funct_getArgument_string(__int64 a1, unsigned int a2, int a3, __int64 pointer);
		static signed __int64 __fastcall funct_getArgument_noobject(__int64 a1, int a2, __int64 a3);
		static signed __int64 __fastcall funct_returnArgument_string(__int64 a1, unsigned int a2, __int64 a3);

		static void HookDeclareFunction();

		static bool GetPadState(char *);

		static uintptr_t __fastcall ccGroupBattleEventCameraBegin();
		static int __fastcall ccGroupBattleEventCameraMovePosBegin(float x, float z, float y, float a);
		static int __fastcall ccGroupBattleEventCameraMoveLookBegin(float x, float z, float y, float a);
	};
}