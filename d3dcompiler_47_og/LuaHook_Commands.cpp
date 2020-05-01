#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "d3dcompiler_47_og.h"
#include "LuaHook_Commands.h"

using namespace std;
using namespace moddingApi;

typedef void *(__fastcall * fc_ccSetGroupBattleCharPos)(float a1, string a2, float a3, float a4, float a5, float a6, float a7, float a8);
fc_ccSetGroupBattleCharPos cc_ccSetGroupBattleCharPos;
void __fastcall LuaHook_Commands::ccSetGroupBattleCharPos(float a1, string a2, float a3, float a4, float a5, float a6, float a7, float a8)
{
	cc_ccSetGroupBattleCharPos = (fc_ccSetGroupBattleCharPos)(d3dcompiler_47_og::moduleBase + 0x4516B4);
	cc_ccSetGroupBattleCharPos(a1, a2, a3, a4, a5, a6, a7, a8);
}

typedef int *(__fastcall * fc_ccPlayerPoolSet)(char*, unsigned int);
fc_ccPlayerPoolSet cc_ccPlayerPoolSet;
int __fastcall LuaHook_Commands::ccPlayerPoolSet(char* CharacterName, unsigned int CharacterNumber)
{
	cc_ccPlayerPoolSet = (fc_ccPlayerPoolSet)(d3dcompiler_47_og::moduleBase + 0x450F24);
	return (int)cc_ccPlayerPoolSet(CharacterName, CharacterNumber);
}

typedef int *(__fastcall * fc_ccEntryReSpawnID)(char* a1, unsigned int a2, unsigned int a3);
fc_ccEntryReSpawnID cc_ccEntryReSpawnID;
int __fastcall LuaHook_Commands::ccEntryReSpawnID(char* a1, unsigned int a2, unsigned int a3)
{
	cc_ccEntryReSpawnID = (fc_ccEntryReSpawnID)(d3dcompiler_47_og::moduleBase + 0x44F7D4);
	return (int)cc_ccEntryReSpawnID(a1, a2, a3);
}

typedef int *(__fastcall * fc_ccEntryGroupBattleChar)(char* GP_CHAR_ID, bool BOOL1, bool BOOL2, float POSX, float POSZ, float POSY, int a7, int a8, char* UNKSTRING, int a10);
fc_ccEntryGroupBattleChar cc_ccEntryGroupBattleChar;
int __fastcall LuaHook_Commands::ccEntryGroupBattleChar(char* GP_CHAR_ID, bool BOOL1, bool BOOL2, float POSX, float POSZ, float POSY, int a7, int a8, char* UNKSTRING, int a10)
{
	cc_ccEntryGroupBattleChar = (fc_ccEntryGroupBattleChar)(d3dcompiler_47_og::moduleBase + 0x44ECDC);
	return (int)cc_ccEntryGroupBattleChar(GP_CHAR_ID, BOOL1, BOOL2, POSX, POSZ, POSY, a7, a8, UNKSTRING, a10);
}

typedef float (__fastcall * fc_ccGetGroupBattleEnemyLife)(char* a1);
fc_ccGetGroupBattleEnemyLife cc_ccGetGroupBattleEnemyLife;
float __fastcall LuaHook_Commands::ccGetGroupBattleEnemyLife(char* a1)
{
	cc_ccGetGroupBattleEnemyLife = (fc_ccGetGroupBattleEnemyLife)(d3dcompiler_47_og::moduleBase + 0x44F8B4);
	return cc_ccGetGroupBattleEnemyLife(a1);
}

typedef signed __int64(__fastcall * fc_ret_qword_7FF68DF26C70)();
fc_ret_qword_7FF68DF26C70 cc_fc_ret_qword_7FF68DF26C70;
signed __int64 cc_ccfc_ret_qword_7FF68DF26C70()
{
	cc_fc_ret_qword_7FF68DF26C70 = (fc_ret_qword_7FF68DF26C70)(d3dcompiler_47_og::moduleBase + 0x84E810);
	return cc_fc_ret_qword_7FF68DF26C70();
}

typedef signed __int64(__fastcall * fc_ccEntryNameTelop)(char* topString, char* botString, float a1, float a2, float a3, float a4, int a5);
fc_ccEntryNameTelop cc_ccEntryNameTelop;
unsigned __int64 __fastcall LuaHook_Commands::ccEntryNameTelop(char* topString, char* botString, float a1, float a2, float a3, float a4, int a5)
{
	//__int64 a0 = cc_ccfc_ret_qword_7FF68DF26C70();
	cc_ccEntryNameTelop = (fc_ccEntryNameTelop)(d3dcompiler_47_og::moduleBase + 0x534CA4);
	__int64 a = 0;
	return cc_ccEntryNameTelop(topString, botString, a1, a2, a3, a4, a5);
}