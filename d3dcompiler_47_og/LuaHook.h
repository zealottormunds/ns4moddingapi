#pragma once

#include <vector>
#include <string>
namespace moddingApi
{
	class LuaHook
	{
	public:
		static signed __int64 tolua_tolua_open(__int64 L);

		static signed __int64 __fastcall funct_getArgument_number(__int64 a1, unsigned int a2, int a3, __int64 a4);
		static signed __int64 __fastcall funct_getArgument_string(__int64 a1, unsigned int a2, int a3, __int64 pointer);
		static signed __int64 __fastcall funct_getArgument_noobject(__int64 a1, int a2, __int64 a3);
		static signed __int64 __fastcall funct_returnArgument_string(__int64 a1, unsigned int a2, __int64 a3);
		static int __fastcall funct_sendStringToLua(__int64 a1, __int64 a2);
		static int __fastcall funct_sendIntToLua(__int64 a1, __int64 a2);

		static void HookDeclareFunction();

		static bool GetPadState(char *);

		static uintptr_t __fastcall ccGroupBattleEventCameraBegin();
		static int __fastcall ccGroupBattleEventCameraMovePosBegin(float x, float z, float y, float a);
		static int __fastcall ccGroupBattleEventCameraMoveLookBegin(float x, float z, float y, float a);

		static int __fastcall fc_ccCreateAnmObject(char* a1, char* a2, char* a3);
		static int __fastcall fc_ccSetAnmPosition(char* a1, float a2, float a3, float a4);
		static int __fastcall fc_ccStartCamera(int a1);
		static int __fastcall fc_ccSetCameraByCoord(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8);
		static int __fastcall fc_ccMoveCameraByCoord(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10);
		static int __fastcall fc_ccScriptWaitStartFrame(int a1);
		static int __fastcall fc_ccScriptWait(int a1);
		static int __fastcall fc_ccSetWindowFrameParam(char* a1, char* a2, char* a3, float a4, float a5, float a6);
		static int __fastcall fc_ccSetBalloonWindowEnableDrawButton(bool a1);
		static int __fastcall fc_ccSetManualStringCaptionById(uintptr_t a1);
		static int __fastcall fc_ccSetCloseBalloonWindowForce(bool a1);
		static int __fastcall fc_ccCloseMwssageWindow();
		static int __fastcall fc_ccScriptWaitWindowClose();
		static int __fastcall fc_ccDeleteAutoStringCaption();
		static int __fastcall fc_ccCreateCastByChunk(char* a1, char* a2, char* a3);
		static int __fastcall fc_ccSetIsLipSyncAutoClear(char* a1, bool a2);
		static int __fastcall fc_ccSetCastPosition(char* a1, float a2, float a3, float a4);
		static int __fastcall fc_ccSetCastDirection(char* a1, float a2, float a3, float a4);
		static int __fastcall fc_ccSetCastDirectionByDeg(char* a1, float a2, float a3, float a4);
		static int __fastcall fc_ccSetCastMotion(char* a1, char* a2, char* a3);
		static int __fastcall fc_ccSetCastFaceMotion(char* a1, char* a2, char* a3);
		static int __fastcall fc_ccSetFaceDirection(char* a1, float a2, float a3, float a4);
		static int __fastcall fc_ccMoveFaceDirection(char* a1, float a2, float a3, float a4, float a5, float a6);
		static int __fastcall fc_ccMoveCast(char* a1, float a2, float a3, float a4, float a5, float a6);
		static int __fastcall fc_ccSetCastMotionWithInterpolation(char* a1, char* a2, char* a3, float a4);
		static int __fastcall fc_ccDispCast(char* a1, bool a2);
		static int __fastcall fc_ccDeleteCast(char* a1);
		static int __fastcall fc_ccDeleteAnm(char* a1);
		static int __fastcall fc_ccEndStandDemoMode();
		static int __fastcall fc_ccChangeBattleById(char* a1);

		static int __fastcall fc_ccStartStandDemoMode();
		static void __fastcall fc_ccStartFreeDemoMode();
		static int __fastcall fc_ccPlayStandDemo(char* a1);
		static int __fastcall fc_ccPlayPtDemo(char* a1);

		static int __fastcall fc_ccCreateSprite(char* a1, char* a2, char* a3);
		static int __fastcall fc_ccDeleteSprite(char* a1);
		static int __fastcall fc_ccSetSpritePosition(char* a1, float a2, float a3);
		static int __fastcall fc_ccSetSpriteFade(char* a1, int a2, int a3, int a4);
		static __int64 __fastcall fc_ccSetEnableLensFlare(char a1);

		static uintptr_t __fastcall LuaHook::fc_ccGetCastPointer(char* a1);
		static int __fastcall LuaHook::fc_ccSetLuaGlobalString(char* a1);
		static int __fastcall LuaHook::fc_ccSetLuaGlobalInt(int a1);

		static int __fastcall fc_ccLoadFile(char* a1);
		static int __fastcall fc_ccCreateStage(__int64 a1, bool a2);
		static int __fastcall fc_ccAdvStopStageBgm();
		//static int __fastcall fc_ccLoadStage(UINT32 a1);

		static char* ztLoadStageName;
		static void ztSetLoadStageName(char* s);
		static int ztGetLoadStageName(__int64 a1);
		
		static std::vector<std::string> ztStringArray;
		static int ztGetStringArraySize(__int64 a1);
		static int ztGetStringArray(__int64 a1);
		static int ztRestartSt(__int64 a1);
	};
}