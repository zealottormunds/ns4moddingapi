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

using namespace std;
using namespace moddingApi;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// TO CREATE LUA FUNCTIONS
typedef __int64(__fastcall * getArgument_number)(__int64 a1, unsigned int a2, int a3, __int64 a4);
getArgument_number fc_getArgument_number;
signed __int64 __fastcall LuaHook::funct_getArgument_number(__int64 a1, unsigned int a2, int a3, __int64 a4)
{
	fc_getArgument_number = (getArgument_number)(d3dcompiler_47_og::moduleBase + 0x9A5A50);
	return fc_getArgument_number(a1, a2, a3, a4);
}

typedef __int64(__fastcall * getArgument_string)(__int64 a1, unsigned int a2, int a3, __int64 pointer);
getArgument_string fc_getArgument_string;
signed __int64 __fastcall LuaHook::funct_getArgument_string(__int64 a1, unsigned int a2, int a3, __int64 pointer)
{
	fc_getArgument_string = (getArgument_string)(d3dcompiler_47_og::moduleBase + 0x9A5AD0);
	return fc_getArgument_string(a1, a2, a3, pointer);
}

typedef __int64(__fastcall * getArgument_noobject)(__int64 a1, int a2, __int64 a3);
getArgument_noobject fc_getArgument_noobject;
signed __int64 __fastcall LuaHook::funct_getArgument_noobject(__int64 a1, int a2, __int64 a3)
{
	fc_getArgument_noobject = (getArgument_noobject)(d3dcompiler_47_og::moduleBase + 0x9A59F0);
	return fc_getArgument_noobject(a1, a2, a3);
}

typedef __int64(__fastcall * returnArgument_string)(__int64 a1, unsigned int a2, __int64 a3);
returnArgument_string fc_returnArgument_string;
signed __int64 __fastcall LuaHook::funct_returnArgument_string(__int64 a1, unsigned int a2, __int64 a3)
{
	fc_returnArgument_string = (returnArgument_string)(d3dcompiler_47_og::moduleBase + 0x9A7350);
	return fc_returnArgument_string(a1, a2, a3);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

typedef uintptr_t *(__fastcall * fc_ccGroupBattleEventCameraBegin)();
fc_ccGroupBattleEventCameraBegin cc_ccGroupBattleEventCameraBegin;
uintptr_t __fastcall LuaHook::ccGroupBattleEventCameraBegin()
{
	cc_ccGroupBattleEventCameraBegin = (fc_ccGroupBattleEventCameraBegin)(d3dcompiler_47_og::moduleBase + 0x450170);
	cc_ccGroupBattleEventCameraBegin();

	return 0;
}

typedef int *(__fastcall * fc_ccGroupBattleEventCameraMovePosBegin)(float, float, float, float);
fc_ccGroupBattleEventCameraMovePosBegin cc_ccGroupBattleEventCameraMovePosBegin;
int __fastcall LuaHook::ccGroupBattleEventCameraMovePosBegin(float x, float z, float y, float a)
{
	cc_ccGroupBattleEventCameraMovePosBegin = (fc_ccGroupBattleEventCameraMovePosBegin)(d3dcompiler_47_og::moduleBase + 0x4503A4);
	cc_ccGroupBattleEventCameraMovePosBegin(x, z, y, a);

	return 0;
}

typedef int *(__fastcall * fc_ccGroupBattleEventCameraMoveLookBegin)(float, float, float);
fc_ccGroupBattleEventCameraMoveLookBegin cc_ccGroupBattleEventCameraMoveLookBegin;
int __fastcall LuaHook::ccGroupBattleEventCameraMoveLookBegin(float x, float z, float y, float a)
{
	cc_ccGroupBattleEventCameraMoveLookBegin = (fc_ccGroupBattleEventCameraMoveLookBegin)(d3dcompiler_47_og::moduleBase + 0x450308);
	cc_ccGroupBattleEventCameraMoveLookBegin(x, z, y);

	return 0;
}

typedef int(__fastcall * temp_subtitlefunc)(__int64 a1);
temp_subtitlefunc fc_temp_subtitlefunc;
int __fastcall funct_temp_subtitlefunc(__int64 a1)
{
	fc_temp_subtitlefunc = (temp_subtitlefunc)(d3dcompiler_47_og::moduleBase + 0x450E90);
	return fc_temp_subtitlefunc(a1);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// FUNCTIONS FOR LUA
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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

vector<string> commandList;
vector<INT64> functionList;
void LuaAddFunct(string command, void* function)
{
	commandList.push_back((char*)command.c_str());
	functionList.push_back((INT64)function);
}

// DECLARE LUA FUNCTIONS
void UnhookDeclareFunction();
typedef INT64(__fastcall * LuaDeclareFunction)(INT64 a1, char* a2, INT64 a3);
LuaDeclareFunction ccLuaDeclareFunction;
INT64 __fastcall DeclareFunctionAPI(INT64 a1, char* a2, INT64 a3)
{
	bool isLast = false;
	string functionName(a2);
	if (functionName == "ccSetKillAttackTime") isLast = true;

	UnhookDeclareFunction();
	ccLuaDeclareFunction = (LuaDeclareFunction)(d3dcompiler_47_og::moduleBase + 0x9A6730);

	// Declare game function
	INT64 result = ccLuaDeclareFunction(a1, a2, a3);
	//cout << "Declared lua function: " << functionName << endl;

	// Declare my functions
	if (isLast)
	{
		LuaAddFunct("ccHelloWorld", (void*)lua_test);
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
	}

	LuaHook::HookDeclareFunction();

	return result;
}

#include "HookFunctions.h"
BYTE DeclareFunctionBytes[16];
void LuaHook::HookDeclareFunction()
{
	memcpy(DeclareFunctionBytes, (void*)(d3dcompiler_47_og::moduleBase + 0x9A6730), 16);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x9A6730), (void*)DeclareFunctionAPI, 16);
}

void UnhookDeclareFunction()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x9A6730), 16, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x9A6730), DeclareFunctionBytes, 16);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x9A6730), 16, dwOld, &dwOld);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////