#include <Winsock2.h>
#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#pragma comment(lib, "XInput.lib")
#include <Xinput.h>

#include "LuaHook.h"
#include "d3dcompiler_47_og.h"
#include "ccMain.h"
#include "ccGeneralGameFunctions.h"
#include "MultiMatch.h"
#include "ccGameProperties.h"
#include "ztRpgMain.h"

using namespace std;
using namespace moddingApi;

// Creates a new lua state
signed __int64 LuaHook::tolua_tolua_open(__int64 a1)
{
	typedef __int64(__fastcall * fc_funct)(__int64  a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x848828);
	return fc_cc_funct(a1);
}

// Functions for lua
signed __int64 __fastcall LuaHook::funct_getArgument_number(__int64 a1, unsigned int a2, int a3, __int64 a4)
{
	typedef __int64(__fastcall * getArgument_number)(__int64 a1, unsigned int a2, int a3, __int64 a4);
	getArgument_number fc_getArgument_number;
	fc_getArgument_number = (getArgument_number)(d3dcompiler_47_og::moduleBase + 0x9A9CF0); // UPDATED
	return fc_getArgument_number(a1, a2, a3, a4);
}

signed __int64 __fastcall LuaHook::funct_getArgument_string(__int64 a1, unsigned int a2, int a3, __int64 pointer)
{
	typedef __int64(__fastcall * getArgument_string)(__int64 a1, unsigned int a2, int a3, __int64 pointer);
	getArgument_string fc_getArgument_string;
	fc_getArgument_string = (getArgument_string)(d3dcompiler_47_og::moduleBase + 0x9A9D70); // UPDATED
	return fc_getArgument_string(a1, a2, a3, pointer);
}

signed __int64 __fastcall LuaHook::funct_getArgument_noobject(__int64 a1, int a2, __int64 a3)
{
	typedef __int64(__fastcall * getArgument_noobject)(__int64 a1, int a2, __int64 a3);
	getArgument_noobject fc_getArgument_noobject;
	fc_getArgument_noobject = (getArgument_noobject)(d3dcompiler_47_og::moduleBase + 0x9A9C90); // UPDATED
	return fc_getArgument_noobject(a1, a2, a3);
}

signed __int64 __fastcall LuaHook::funct_returnArgument_string(__int64 a1, unsigned int a2, __int64 a3)
{
	typedef __int64(__fastcall * returnArgument_string)(__int64 a1, unsigned int a2, __int64 a3);
	returnArgument_string fc_returnArgument_string;
	fc_returnArgument_string = (returnArgument_string)(d3dcompiler_47_og::moduleBase + 0x9AB5E0); // UPDATED
	return fc_returnArgument_string(a1, a2, a3);
}

int __fastcall LuaHook::funct_sendStringToLua(__int64 a1, __int64 a2)
{
	typedef int(__fastcall * sendStringLua)(__int64 a1, __int64 a2);
	sendStringLua fc_sendStringLua;
	fc_sendStringLua = (sendStringLua)(d3dcompiler_47_og::moduleBase + 0x9AB300); // UPDATED
	return fc_sendStringLua(a1, a2);
}

int __fastcall LuaHook::funct_sendIntToLua(__int64 a1, __int64 a2)
{
	typedef int(__fastcall * sendIntLua)(__int64 a1, __int64 a2);
	sendIntLua fc_sendIntLua;
	fc_sendIntLua = (sendIntLua)(d3dcompiler_47_og::moduleBase + 0x9AB2F0); // UPDATED
	return fc_sendIntLua(a1, a2);
}

////////////////////////////////////////////////////////////////////////

// These are some C++ equivalents of Lua commands that you can use from the API. Most of them are useful only on specific instances, though.

uintptr_t __fastcall LuaHook::ccGroupBattleEventCameraBegin()
{
	typedef uintptr_t *(__fastcall * fc_ccGroupBattleEventCameraBegin)();
	fc_ccGroupBattleEventCameraBegin cc_ccGroupBattleEventCameraBegin;
	cc_ccGroupBattleEventCameraBegin = (fc_ccGroupBattleEventCameraBegin)(d3dcompiler_47_og::moduleBase + 0x450CAC); // UPDATED
	cc_ccGroupBattleEventCameraBegin();

	return 0;
}

int __fastcall LuaHook::ccGroupBattleEventCameraMovePosBegin(float x, float z, float y, float a)
{
	typedef int *(__fastcall * fc_ccGroupBattleEventCameraMovePosBegin)(float, float, float, float);
	fc_ccGroupBattleEventCameraMovePosBegin cc_ccGroupBattleEventCameraMovePosBegin;
	cc_ccGroupBattleEventCameraMovePosBegin = (fc_ccGroupBattleEventCameraMovePosBegin)(d3dcompiler_47_og::moduleBase + 0x450C40);
	cc_ccGroupBattleEventCameraMovePosBegin(x, z, y, a);

	return 0;
}

int __fastcall LuaHook::ccGroupBattleEventCameraMoveLookBegin(float x, float z, float y, float a)
{
	typedef int *(__fastcall * fc_ccGroupBattleEventCameraMoveLookBegin)(float, float, float);
	fc_ccGroupBattleEventCameraMoveLookBegin cc_ccGroupBattleEventCameraMoveLookBegin;
	cc_ccGroupBattleEventCameraMoveLookBegin = (fc_ccGroupBattleEventCameraMoveLookBegin)(d3dcompiler_47_og::moduleBase + 0x450BA4);
	cc_ccGroupBattleEventCameraMoveLookBegin(x, z, y);

	return 0;
}

int __fastcall funct_temp_subtitlefunc(__int64 a1)
{
	typedef int(__fastcall * temp_subtitlefunc)(__int64 a1);
	temp_subtitlefunc fc_temp_subtitlefunc;
	fc_temp_subtitlefunc = (temp_subtitlefunc)(d3dcompiler_47_og::moduleBase + 0x4519CC); // UPDATED
	return fc_temp_subtitlefunc(a1);
}

// Creates an animated object in the rpg cutscene mode.
// Usage: fc_ccCreateAnmObject(name, path, modelname)
// Example: fc_ccCreateAnmObject("this_is_a_test", "data/spc/1nrtbod1.xfbin", "1nrtbod1")
int __fastcall LuaHook::fc_ccCreateAnmObject(char* a1, char* a2, char* a3)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2, char* a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4B9690); // UPDATED
	return fc_cc_funct(a1, a2, a3);
}

// Sets the position of an animated object in the rpg cutscene mode.
// Usage: fc_ccSetAnmPosition("this_is_a_test", 0, 0, 0)
int __fastcall LuaHook::fc_ccSetAnmPosition(char* a1, float a2, float a3, float a4)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4B9A54); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4);
}

// Enables the camera in the rpg cutscene mode.
// Usage: fc_ccStartCamera(0)
int __fastcall LuaHook::fc_ccStartCamera(int a1)
{
	typedef int(__fastcall * fc_funct)(int a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5316E8); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccSetCameraByCoord(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8)
{
	typedef int(__fastcall * fc_funct)(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x53167C); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4, a5, a6, a7, a8);
}

int __fastcall LuaHook::fc_ccMoveCameraByCoord(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10)
{
	typedef int(__fastcall * fc_funct)(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5313C4); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

int __fastcall LuaHook::fc_ccScriptWaitStartFrame(int a1)
{
	typedef int(__fastcall * fc_funct)(int a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5391C0); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccScriptWait(int a1)
{
	typedef int(__fastcall * fc_funct)(int a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x539118); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccSetWindowFrameParam(char* a1, char* a2, char* a3, float a4, float a5, float a6)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2, char* a3, float a4, float a5, float a6);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x535D4C); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4, a5, a6);
}

int __fastcall LuaHook::fc_ccSetBalloonWindowEnableDrawButton(bool a1)
{
	typedef int(__fastcall * fc_funct)(bool a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x535B90); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccSetManualStringCaptionById(uintptr_t a1)
{
	typedef int(__fastcall * fc_funct)(uintptr_t a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x535C6C); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccSetCloseBalloonWindowForce(bool a1)
{
	typedef int(__fastcall * fc_funct)(bool a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x535BBC); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccCloseMwssageWindow()
{
	typedef int(__fastcall * fc_funct)();
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5359F8); // UPDATED
	return fc_cc_funct();
}

int __fastcall LuaHook::fc_ccScriptWaitWindowClose()
{
	typedef int(__fastcall * fc_funct)();
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5391EC); // UPDATED
	return fc_cc_funct();
}

int __fastcall LuaHook::fc_ccDeleteAutoStringCaption()
{
	typedef int(__fastcall * fc_funct)();
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x535A1C); // UPDATED
	return fc_cc_funct();
}

int __fastcall LuaHook::fc_ccCreateCastByChunk(char* id, char* path, char* meshname)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2, char* a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x531D98); // UPDATED
	return fc_cc_funct(id, path, meshname);
}

int __fastcall LuaHook::fc_ccSetIsLipSyncAutoClear(char* a1, bool a2)
{
	typedef int(__fastcall * fc_funct)(char* a1, bool a2);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x533988); // UPDATED
	return fc_cc_funct(a1, a2);
}

int __fastcall LuaHook::fc_ccSetCastPosition(char* a1, float a2, float a3, float a4)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x533440); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4);
}

int __fastcall LuaHook::fc_ccSetCastDirection(char* a1, float a2, float a3, float a4)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x532574); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4);
}

int __fastcall LuaHook::fc_ccSetCastDirectionByDeg(char* a1, float a2, float a3, float a4)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x532664); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4);
}

int __fastcall LuaHook::fc_ccSetCastMotion(char* a1, char* a2, char* a3)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2, char* a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x532F5C); // UPDATED
	return fc_cc_funct(a1, a2, a3);
}

int __fastcall LuaHook::fc_ccSetCastFaceMotion(char* a1, char* a2, char* a3)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2, char* a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x53279C); // UPDATED
	return fc_cc_funct(a1, a2, a3);
}

int __fastcall LuaHook::fc_ccSetFaceDirection(char* a1, float a2, float a3, float a4)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x53396C); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4);
}

int __fastcall LuaHook::fc_ccMoveFaceDirection(char* a1, float a2, float a3, float a4, float a5, float a6)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4, float a5, float a6);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5322DC); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4, a5, a6);
}

int __fastcall LuaHook::fc_ccMoveCast(char* a1, float a2, float a3, float a4, float a5, float a6)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4, float a5, float a6);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x531F64); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4, a5, a6);
}

int __fastcall LuaHook::fc_ccMoveDirection(char* a1, float a2, float a3, float a4, float a5, float a6)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3, float a4, float a5, float a6);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x532090); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4, a5, a6);
}

int __fastcall LuaHook::fc_ccSetCastMotionWithInterpolation(char* a1, char* a2, char* a3, float a4)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2, char* a3, float a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5333CC); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4);
}

int __fastcall LuaHook::fc_ccDispCast(char* a1, bool a2)
{
	typedef int(__fastcall * fc_funct)(char* a1, bool a2);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x531E78); // UPDATED
	return fc_cc_funct(a1, a2);
}

int __fastcall LuaHook::fc_ccDeleteCast(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x531E14); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccDeleteAnm(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4B97FC); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccEndStandDemoMode()
{
	typedef int(__fastcall * fc_funct)();
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4DE630); // UPDATED
	return fc_cc_funct();
}

uintptr_t __fastcall LuaHook::fc_ccGetCastPointer(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x530E7C);
	return fc_cc_funct(a1) & 0xFFFFFFFF;
}

int __fastcall LuaHook::fc_ccSetLuaGlobalString(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4E3588); // UPDATE
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccSetLuaGlobalInt(int a1)
{
	typedef int(__fastcall * fc_funct)(int a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4E353C); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccChangeBattleById(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4DD018); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccStartStandDemoMode()
{
	/*uintptr_t p1 = 0;
	uintptr_t p2 = 0;
	uintptr_t p3 = 0;
	uintptr_t p4 = 0;
	uintptr_t p5 = 0;
	uintptr_t p6 = 0;
	uintptr_t p7 = 0;
	uintptr_t p8 = 0;

	memcpy(&p1, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x0161B7E0), 8);
	if (p1 == 0) return 0;

	memcpy(&p2, (void*)(p1 + 0x20), 8);
	if (p2 == 0) return 0;

	memcpy(&p3, (void*)(p2 + 0x0), 8);
	if (p3 == 0) return 0;

	memcpy(&p4, (void*)(p3 + 0x20), 8);
	if (p4 == 0) return 0;

	memcpy(&p5, (void*)(p4 + 0x0), 8);
	if (p5 == 0) return 0;

	memcpy(&p6, (void*)(p5 + 0xC80), 8);
	if (p6 == 0) return 0;

	p7 = p6 + 0xB00;
	if (p7 == 0) return 0;

	cout << std::hex << p7 << endl;*/

	typedef int(__fastcall * fc_funct)(__int64 a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4E6ED8); // UPDATED
	//return fc_cc_funct(p4);
	return 0;
}

void __fastcall LuaHook::fc_ccStartFreeDemoMode()
{
	typedef void(__fastcall * fc_funct)();
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4E6C80); // UPDATED
	fc_cc_funct();
}

int __fastcall LuaHook::fc_ccPlayStandDemo(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4E0E18); // UPDATED
	return fc_cc_funct(a1);
}

int __stdcall LuaHook::fc_ccPlayPtDemo(char* a1)
{
	typedef int(__stdcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4E0D64); // UPDATED
	return fc_cc_funct(a1);
}


int __fastcall LuaHook::fc_ccCreateSprite(char* a1, char* a2, char* a3)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2, char* a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4B9D84); // UPDATED
	return fc_cc_funct(a1, a2, a3);
}

int __fastcall LuaHook::fc_ccDeleteSprite(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4B9DF4); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccSetSpritePosition(char* a1, float a2, float a3)
{
	typedef int(__fastcall * fc_funct)(char* a1, float a2, float a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4B9F1C); // UPDATED
	return fc_cc_funct(a1, a2, a3);
}

int __fastcall LuaHook::fc_ccSetSpriteFade(char* a1, int a2, int a3, int a4)
{
	typedef int(__fastcall * fc_funct)(char* a1, int a2, int a3, int a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4B9ED0); // UPDATED
	return fc_cc_funct(a1, a2, a3, a4);
}

__int64 __fastcall LuaHook::fc_ccSetEnableLensFlare(char a1)
{
	typedef __int64(__fastcall * fc_funct)(char a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x537440); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccLoadFile(char* a1)
{
	typedef int(__fastcall * fc_funct)(char* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x534FF4); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccAdvStopStageBgm()
{
	typedef int(__fastcall * fc_funct)();
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4DCE40); // UPDATED
	return fc_cc_funct();
}

int __fastcall fc_ccLoadStage(int a1)
{
	typedef int(__fastcall * fc_funct)(int a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5353F4); // UPDATED
	return fc_cc_funct(a1);
}

int __fastcall LuaHook::fc_ccCreateStage(__int64 a1, bool a2)
{
	typedef int(__fastcall * fc_funct)(__int64  a1, bool a2);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x5383DC); // UPDATED
	return fc_cc_funct(a1, a2);
}


////////////////////////////////////////////////////////////////////////

// My RPG engine
int lua_test(__int64 a1)
{
	__int64 ptr;

	if (LuaHook::funct_getArgument_string(a1, 1, 0, (__int64)&ptr) && LuaHook::funct_getArgument_noobject(a1, 2, (__int64)&ptr))
	{
		char * a2 = (char*)LuaHook::funct_returnArgument_string(a1, 1, 0);
		cout << a2 << endl;
	}

	return 0;
}

// Function to get inputs from XINPUT
bool __fastcall LuaHook::GetPadState(char * a)
{
	bool ToReturn = false;
	string st = (string)a;

	//cout << "Doing stuff..." << endl;
	//cout << st << endl;

	if (st == "BUTTON_A")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_A) != 0) ToReturn = true;
	}
	else if (st == "BUTTON_B")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_B) != 0) ToReturn = true;
	}
	else if (st == "BUTTON_X")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_X) != 0) ToReturn = true;
	}
	else if (st == "BUTTON_Y")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_Y) != 0) ToReturn = true;
	}
	else if (st == "DPAD_UP")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_DPAD_UP) != 0) ToReturn = true;
	}
	else if (st == "DPAD_DOWN")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_DPAD_DOWN) != 0) ToReturn = true;
	}
	else if (st == "DPAD_LEFT")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_DPAD_LEFT) != 0) ToReturn = true;
	}
	else if (st == "DPAD_RIGHT")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_DPAD_RIGHT) != 0) ToReturn = true;
	}
	else if (st == "START")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_START) != 0) ToReturn = true;
	}
	else if (st == "BACK")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_BACK) != 0) ToReturn = true;
	}
	else if (st == "LEFT_SHOULDER")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_LEFT_SHOULDER) != 0) ToReturn = true;
	}
	else if (st == "RIGHT_SHOULDER")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) ToReturn = true;
	}
	else if (st == "LEFT_THUMB")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_LEFT_THUMB) != 0) ToReturn = true;
	}
	else if (st == "RIGHT_THUMB")
	{
		if (ccGeneralGameFunctions::TestButton(XINPUT_GAMEPAD_RIGHT_THUMB) != 0) ToReturn = true;
	}
	else if (st == "LEFT_TRIGGER")
	{
		if (ccGeneralGameFunctions::TestButton(0x5000) != 0) ToReturn = true;
	}
	else if (st == "RIGHT_TRIGGER")
	{
		if (ccGeneralGameFunctions::TestButton(0x6000) != 0) ToReturn = true;
	}

	return ToReturn;
}

// This function is useless.
int ccSetEntryModelPath(__int64 a1)
{
	__int64 ptr;

	if (LuaHook::funct_getArgument_string(a1, 1, 0, (__int64)&ptr) &&
		LuaHook::funct_getArgument_string(a1, 2, 0, (__int64)&ptr) &&
		LuaHook::funct_getArgument_string(a1, 3, 0, (__int64)&ptr) &&
		LuaHook::funct_getArgument_string(a1, 4, 0, (__int64)&ptr) &&
		LuaHook::funct_getArgument_noobject(a1, 5, (__int64)&ptr))
	{
		string modelPath = string((char*)LuaHook::funct_returnArgument_string(a1, 1, 0));
		string modelAnmPath = string((char*)LuaHook::funct_returnArgument_string(a1, 2, 0));
		string modelName = string((char*)LuaHook::funct_returnArgument_string(a1, 3, 0));
		string modelAnmName = string((char*)LuaHook::funct_returnArgument_string(a1, 4, 0));

		if (modelPath.length() <= 0x1B	&&
			modelAnmPath.length() <= 0x21 &&
			modelName.length() <= 0x8 &&
			modelAnmName.length() <= 0x8)
		{
			BYTE modelPathBytes[0x1B];
			char* modelPathC = (char*)modelPath.c_str();
			for (int x = 0; x < modelPath.length(); x++) modelPathBytes[x] = modelPathC[x];
			for (int x = modelPath.length(); x < 0x1B; x++) modelPathBytes[x] = 0x0;

			BYTE modelAnmPathBytes[0x21];
			char* modelAnmPathC = (char*)modelAnmPath.c_str();
			for (int x = 0; x < modelAnmPath.length(); x++) modelAnmPathBytes[x] = modelAnmPathC[x];
			for (int x = modelAnmPath.length(); x < 0x21; x++) modelAnmPathBytes[x] = 0x0;

			BYTE modelNameBytes[0x8];
			char* modelNameC = (char*)modelName.c_str();
			for (int x = 0; x < modelName.length(); x++) modelNameBytes[x] = modelNameC[x];
			for (int x = modelName.length(); x < 0x8; x++) modelNameBytes[x] = 0x0;

			BYTE modelAnmNameBytes[0x8];
			char* modelAnmNameC = (char*)modelAnmName.c_str();
			for (int x = 0; x < modelAnmName.length(); x++) modelAnmNameBytes[x] = modelAnmNameC[x];
			for (int x = modelAnmName.length(); x < 0x8; x++) modelAnmNameBytes[x] = 0x0;

			DWORD dwOld = 0;
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DD8), 0x1B, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xF36DD8), modelPathBytes, 0x1B);
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DD8), 0x1B, dwOld, &dwOld);

			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DF8), 0x21, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xF36DF8), modelAnmPathBytes, 0x21);
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DF8), 0x21, dwOld, &dwOld);

			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC28), 0x8, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC28), modelNameBytes, 0x8);
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC28), 0x8, dwOld, &dwOld);

			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC38), 0x8, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC38), modelAnmNameBytes, 0x8);
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC38), 0x8, dwOld, &dwOld);

			cout << "Replaced model" << endl;
		}
		else
		{
			cout << "Incorrect sizes" << endl;
		}

	}

	return 0;
}

// This function is also useless.
int ccRestoreEntryModelPath(__int64 a1)
{
	__int64 ptr;

	string modelPath = "data/boss/02/gfsabod1.xfbin";
	string modelAnmPath = "data/boss/02/b0203_gfsa_anm.xfbin";
	string modelName = "gfsabod1";
	string modelAnmName = "gfsanut0";

	if (modelPath.length() <= 0x1B &&
		modelAnmPath.length() <= 0x21 &&
		modelName.length() <= 0x8 &&
		modelAnmName.length() <= 0x8)
	{
		BYTE modelPathBytes[0x1B];
		char* modelPathC = (char*)modelPath.c_str();
		for (int x = 0; x < modelPath.length(); x++) modelPathBytes[x] = modelPathC[x];
		for (int x = modelPath.length(); x < 0x1B; x++) modelPathBytes[x] = 0x0;

		BYTE modelAnmPathBytes[0x21];
		char* modelAnmPathC = (char*)modelAnmPath.c_str();
		for (int x = 0; x < modelAnmPath.length(); x++) modelAnmPathBytes[x] = modelAnmPathC[x];
		for (int x = modelAnmPath.length(); x < 0x21; x++) modelAnmPathBytes[x] = 0x0;

		BYTE modelNameBytes[0x8];
		char* modelNameC = (char*)modelName.c_str();
		for (int x = 0; x < modelName.length(); x++) modelNameBytes[x] = modelNameC[x];
		for (int x = modelName.length(); x < 0x8; x++) modelNameBytes[x] = 0x0;

		BYTE modelAnmNameBytes[0x8];
		char* modelAnmNameC = (char*)modelAnmName.c_str();
		for (int x = 0; x < modelAnmName.length(); x++) modelAnmNameBytes[x] = modelAnmNameC[x];
		for (int x = modelAnmName.length(); x < 0x8; x++) modelAnmNameBytes[x] = 0x0;

		DWORD dwOld = 0;
		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DD8), 0x1B, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xF36DD8), modelPathBytes, 0x1B);
		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DD8), 0x1B, dwOld, &dwOld);

		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DF8), 0x21, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xF36DF8), modelAnmPathBytes, 0x21);
		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xF36DF8), 0x21, dwOld, &dwOld);

		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC28), 0x8, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC28), modelNameBytes, 0x8);
		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC28), 0x8, dwOld, &dwOld);

		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC38), 0x8, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC38), modelAnmNameBytes, 0x8);
		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xFEFC38), 0x8, dwOld, &dwOld);

		cout << "Restored original model" << endl;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

vector<string> commandList;
vector<INT64> functionList;
// Adds a custom Lua function to lua_state*
void LuaAddFunct(string command, void* function)
{
	commandList.push_back((char*)command.c_str());
	functionList.push_back((INT64)function);
}

// Print a Lua value through cout
int ccCoutLua(__int64 a1)
{
	__int64 ptr;

	if (LuaHook::funct_getArgument_string(a1, 1, 0, (__int64)&ptr))
	{
		string coutstr = string((char*)LuaHook::funct_returnArgument_string(a1, 1, 0));

		cout << hex << coutstr << endl;
	}

	return 0;
}

// Declare the custom Lua functions
void UnhookDeclareFunction();
INT64 __fastcall DeclareFunctionAPI(INT64 a1, char* a2, INT64 a3)
{
	typedef INT64(__fastcall * LuaDeclareFunction)(INT64 a1, char* a2, INT64 a3);
	LuaDeclareFunction ccLuaDeclareFunction;

	bool isLast = false;
	string functionName(a2);
	if (functionName == "ccSetKillAttackTime") isLast = true;

	UnhookDeclareFunction();
	ccLuaDeclareFunction = (LuaDeclareFunction)(d3dcompiler_47_og::moduleBase + 0x9AA9C0); // UPDATED
	INT64 result = ccLuaDeclareFunction(a1, a2, a3);

	// Declare all new Lua functions
	if (isLast)
	{
		LuaAddFunct("ccHelloWorld", (void*)lua_test);
		LuaAddFunct("ccTestRpg", (void*)ztRpgMain::rpg_test);
		LuaAddFunct("ccCout", (void*)ccCoutLua);
		LuaAddFunct("ztGetLoadStageName", (void*)LuaHook::ztGetLoadStageName);
		LuaAddFunct("ztGetStringArraySize", (void*)LuaHook::ztGetStringArraySize);
		LuaAddFunct("ztGetStringArray", (void*)LuaHook::ztGetStringArray);
		LuaAddFunct("ztRestartSt", (void*)LuaHook::ztRestartSt);
		LuaAddFunct("ztLoadFiles", (void*)LuaHook::ztLoadFiles);
		LuaAddFunct("ztGetGlobalInt", (void*)LuaHook::ztGetGlobalInt);
		LuaAddFunct("SetLuaState", (void*)LuaHook::SetLuaState);

		// Old multimatch functions. These will be updated eventually.
		//LuaAddFunct("ccInitializeMultiMatch", (void*)MultiMatch::ccInitializeMultiMatch);
		//LuaAddFunct("ccMultiMatchCameraLoop", (void*)MultiMatch::ccMultiMatchCameraLoop);
		//LuaAddFunct("ccSetEntryModelPath", (void*)ccSetEntryModelPath);
		//LuaAddFunct("ccRestoreEntryModelPath", (void*)ccRestoreEntryModelPath);
		//LuaAddFunct("ccMultiMatchShowPlayerStatus", (void*)MultiMatch::ccMultiMatchShowPlayerStatus);

		for (int x = 0; x < functionList.size(); x++)
		{
			INT64 result = ccLuaDeclareFunction(a1, (char*)commandList[x].c_str(), functionList[x]);
			cout << "Declared lua function: " << commandList[x] << endl;
		}

		//cout << "Set lua_State to " << std::hex << a1;
		ccGameProperties::LStateGame = a1;
		ccGameProperties::LState = a1;
		ccGameProperties::ExecuteLuaInitial();
	}

	LuaHook::HookDeclareFunction();

	return result;
}

#include "HookFunctions.h"
BYTE DeclareFunctionBytes[16];
int LuaHook_ToLua_DeclareFunction = 0x9AA9C0;
void LuaHook::HookDeclareFunction()
{
	//cout << "Hooking declare function" << endl;
	memcpy(DeclareFunctionBytes, (void*)(d3dcompiler_47_og::moduleBase + LuaHook_ToLua_DeclareFunction), 16);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + LuaHook_ToLua_DeclareFunction), (void*)DeclareFunctionAPI, 16);
}

void UnhookDeclareFunction()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + LuaHook_ToLua_DeclareFunction), 16, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + LuaHook_ToLua_DeclareFunction), DeclareFunctionBytes, 16);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + LuaHook_ToLua_DeclareFunction), 16, dwOld, &dwOld);
}

char* LuaHook::ztLoadStageName = "";

void LuaHook::ztSetLoadStageName(char* s)
{
	LuaHook::ztLoadStageName = s;
	cout << "Set load stage name to " << s << endl;
}

int LuaHook::ztGetLoadStageName(__int64 a1)
{
	__int64 ptr;
	__int64 asd = (__int64)(malloc(100));

	if (LuaHook::funct_getArgument_noobject(a1, 1, asd))
	{
		LuaHook::funct_sendStringToLua(a1, (__int64)(LuaHook::ztLoadStageName));
	}

	return 1;
}

std::vector<std::string> LuaHook::ztStringArray = std::vector<std::string>();
int LuaHook::ztGetStringArraySize(__int64 a1)
{
	__int64 ptr;
	__int64 asd = (__int64)(malloc(100));

	if (LuaHook::funct_getArgument_noobject(a1, 1, asd))
	{
		cout << "Returned " << ztStringArray.size() << endl;
		int n = ztStringArray.size();
		LuaHook::funct_sendIntToLua(a1, (__int64)(&n));
	}

	return 1;
}

int actualst = 0;
int LuaHook::ztGetStringArray(__int64 a1)
{
	__int64 ptr;
	__int64 asd = (__int64)(malloc(4));

	int v4;
	v4 = actualst;

	cout << "Getting string number " << v4 << endl;
	if (v4 < ztStringArray.size())
	{
		char* b = (char*)(ztStringArray[v4].c_str());
		LuaHook::funct_sendStringToLua(a1, (__int64)(&b));
	}
	else
	{
		char* a = "data/rpg/rnrtbod4.xfbin";
		LuaHook::funct_sendStringToLua(a1, (__int64)(&a));
	}

	actualst++;

	return 1;
}

int LuaHook::ztRestartSt(__int64 a1)
{
	__int64 ptr;
	
	if (LuaHook::funct_getArgument_noobject(a1, 1, (__int64)&ptr))
	{
		actualst = 0;
		cout << "Restarted st" << endl;
	}

	return 1;
}

#include "Scene.h"
int LuaHook::ztLoadFiles(__int64 a1)
{
	__int64 ptr;
	
	if (LuaHook::funct_getArgument_noobject(a1, 1, (__int64)&ptr))
	{
		Scene::LoadSceneFiles();
	}

	return 1;
}

int LuaHook::ztGlobalInt = 0;

int LuaHook::ztGetGlobalInt(__int64 a1)
{
	__int64 ptr;
	__int64 asd = (__int64)(malloc(4));

	cout << "Getting global int: " << ztGlobalInt << endl;
	LuaHook::funct_sendIntToLua(a1, (__int64)&ztGlobalInt);

	return 1;
}

int LuaHook::SetLuaState(__int64 a1)
{
	cout << "Lua state set to " << std::hex << a1 << endl;
	ccGameProperties::LStateGame = a1;
	return 1;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////