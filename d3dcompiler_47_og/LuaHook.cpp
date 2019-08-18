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

using namespace std;
using namespace moddingApi;

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