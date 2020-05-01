#pragma once

#include <vector>
using namespace std;

namespace moddingApi
{
	class LuaHook_Commands
	{
	public:
		static void __fastcall ccSetGroupBattleCharPos(float a1, string a2, float a3, float a4, float a5, float a6, float a7, float a8);
		static int __fastcall ccPlayerPoolSet(char* CharacterName, unsigned int CharacterNumber);
		static int __fastcall ccEntryReSpawnID(char* a1, unsigned int a2, unsigned int a3);
		static int __fastcall ccEntryGroupBattleChar(char* GP_CHAR_ID, bool BOOL1, bool BOOL2, float POSX, float POSZ, float POSY, int a7, int a8, char* UNKSTRING, int a10);
		static float __fastcall ccGetGroupBattleEnemyLife(char * a1);
		static unsigned __int64 __fastcall ccEntryNameTelop(char * topString, char * botString, float a4, float xmm3_4_0, float a5, float a6, int a7);
	};
}