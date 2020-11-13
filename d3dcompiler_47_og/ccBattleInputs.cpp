#pragma region Imports
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <bitset>
#include "Vector3.h"
#include "ccPlayer.h"
#include "ccBattleInputs.h"
#include <filesystem>

using namespace std;
using namespace moddingApi;
#pragma endregion
#pragma region Input Definitions
vector<float> ccBattleInputs::leftStick;
vector<float> ccBattleInputs::rightStick;
vector<bool> ccBattleInputs::dpadAxis;
vector<bool> ccBattleInputs::stickBtns;
bool ccBattleInputs::jumpBtn;
bool ccBattleInputs::chakBtn;
bool ccBattleInputs::atkBtn;
bool ccBattleInputs::kunaiBtn;
vector<bool> ccBattleInputs::assistBtn;
bool ccBattleInputs::guardBtn;
bool ccBattleInputs::subBtn;
bool ccBattleInputs::selectBtn;
bool ccBattleInputs::startBtn;
void ccBattleInputs::InitializeValues() {
	leftStick = { 0, 0 };
	rightStick = { 0, 0 };
	dpadAxis = { false, false, false, false };
	stickBtns = { false, false };
	jumpBtn = false;
	chakBtn = false;
	atkBtn = false;
	kunaiBtn = false;
	assistBtn = { false,false };
	guardBtn = false;
	subBtn = false;
	selectBtn = false;
	startBtn = false;
}
#pragma endregion

ccBattleInputs::ccBattleInputs() { InitializeValues(); }

void ccBattleInputs::GetGamepadState(int n) {
	uintptr_t dpad_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA8;
	uintptr_t btn_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA7;
	uintptr_t lstick_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA6;
	uintptr_t rstick_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA5;

	std::byte dpad = *(std::byte*)dpad_ptr;
	std::byte btn = *(std::byte*)btn_ptr;
	std::byte lstick = *(std::byte*)lstick_ptr;
	std::byte rstick = *(std::byte*)rstick_ptr;

	int dpadI = int(dpad);
	if (dpadI >= 0x80) { dpadAxis[3] = true; dpadI -= 0x80; }
	if (dpadI >= 0x40) { dpadAxis[2] = true; dpadI -= 0x40; }
	if (dpadI >= 0x20) { dpadAxis[1] = true; dpadI -= 0x20; }
	if (dpadI >= 0x10) { dpadAxis[0] = true; dpadI -= 0x10; }
	if (dpadI >= 0x8) { startBtn = true;     dpadI -= 0x8; }
	if (dpadI >= 0x4) { stickBtns[1] = true; dpadI -= 0x4; }
	if (dpadI >= 0x2) { stickBtns[0] = true; dpadI -= 0x2; }
	if (dpadI >= 0x1) { selectBtn = true;    dpadI -= 0x1; }

	int btnI = int(btn);
	if (btnI >= 0x80) { assistBtn[0] = true; btnI -= 0x80; }
	if (btnI >= 0x40) { jumpBtn = true;      btnI -= 0x40; }
	if (btnI >= 0x20) { assistBtn[1] = true; btnI -= 0x20; }
	if (btnI >= 0x10) { chakBtn = true;      btnI -= 0x10; }
	if (btnI >= 0x8) { atkBtn = true;        btnI -= 0x8;  }
	if (btnI >= 0x4) { kunaiBtn = true;      btnI -= 0x4;  }
	if (btnI >= 0x2) { guardBtn = true;      btnI -= 0x2;  }
	if (btnI >= 0x1) { subBtn = true;        btnI -= 0x1;  }

	int lstickI = int(lstick);
	if (lstickI >= 0x80) { leftStick[0] += 1; lstickI -= 0x80; }
	if (lstickI >= 0x40) { leftStick[0] -= 1; lstickI -= 0x40; }
	if (lstickI >= 0x20) { leftStick[1] -= 1; lstickI -= 0x20; }
	if (lstickI >= 0x10) { leftStick[1] += 1; lstickI -= 0x10; }

	int rstickI = int(rstick);
	if (rstickI >= 0x8) { rightStick[0] += 1; rstickI -= 0x8; }
	if (rstickI >= 0x4) { rightStick[0] -= 1; rstickI -= 0x4; }
	if (rstickI >= 0x2) { rightStick[1] -= 1; rstickI -= 0x2; }
	if (rstickI >= 0x1) { rightStick[1] += 1; rstickI -= 0x1; }
}

void ccBattleInputs::Loop(int n) {
	InitializeValues();
	GetGamepadState(n);
}

void ccBattleInputs::Loop(int n, std::vector<bool> debugger) {
	InitializeValues();
	GetGamepadState(n);

	string btn = "";
	if (debugger[1]) btn = Btn2Str();

	if (debugger[0]) cout << "D-Pad:\t" << "(" << dpadAxis[0] << "," << dpadAxis[1] << "," << dpadAxis[2] << "," << dpadAxis[3] << ")" << endl;
	if (debugger[1]) cout << "Buttons:\t" << btn << endl;
	if (debugger[2]) cout << "Left Stick:\t" << "(" << leftStick[0] << "," << leftStick[1] << ")" << endl;
	if (debugger[3]) cout << "Right Stick:\t" << "(" << rightStick[0] << "," << rightStick[1] << ")" << endl;
	cout << endl;
}

string ccBattleInputs::Btn2Str() {
	string result = "";
	if (jumpBtn) result += "Jump, ";
	if (atkBtn) result += "Attack, ";
	if (kunaiBtn) result += "Kunai, ";
	if (chakBtn) result += "Chakra, ";

	if (assistBtn[0]) result += "Assist1, ";
	if (assistBtn[1]) result += "Assist2, ";
	if (guardBtn) result += "Guard, ";
	if (subBtn) result += "Sub, ";

	if (stickBtns[0]) result += "L3, ";
	if (stickBtns[1]) result += "R3, ";
	if (selectBtn) result += "Select, ";
	if (startBtn) result += "Start";

	if (result[result.length() - 1] == ' ') result = result.substr(0, result.length() - 2);

	return result;
}