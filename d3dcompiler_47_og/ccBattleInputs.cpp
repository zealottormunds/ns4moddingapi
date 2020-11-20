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
vector<float> ccBattleInputs::p1leftStick;
vector<float> ccBattleInputs::p1rightStick;
vector<bool> ccBattleInputs::p1dpadAxis;
vector<bool> ccBattleInputs::p1stickBtns;
bool ccBattleInputs::p1jumpBtn;
bool ccBattleInputs::p1chakBtn;
bool ccBattleInputs::p1atkBtn;
bool ccBattleInputs::p1kunaiBtn;
vector<bool> ccBattleInputs::p1assistBtn;
bool ccBattleInputs::p1guardBtn;
bool ccBattleInputs::p1subBtn;
bool ccBattleInputs::p1selectBtn;
bool ccBattleInputs::p1startBtn;
vector<float> ccBattleInputs::p2leftStick;
vector<float> ccBattleInputs::p2rightStick;
vector<bool> ccBattleInputs::p2dpadAxis;
vector<bool> ccBattleInputs::p2stickBtns;
bool ccBattleInputs::p2jumpBtn;
bool ccBattleInputs::p2chakBtn;
bool ccBattleInputs::p2atkBtn;
bool ccBattleInputs::p2kunaiBtn;
vector<bool> ccBattleInputs::p2assistBtn;
bool ccBattleInputs::p2guardBtn;
bool ccBattleInputs::p2subBtn;
bool ccBattleInputs::p2selectBtn;
bool ccBattleInputs::p2startBtn;

void ccBattleInputs::InitializeValues() {
	p1leftStick = { 0, 0 };
	p1rightStick = { 0, 0 };
	p1dpadAxis = { false, false, false, false };
	p1stickBtns = { false, false };
	p1jumpBtn = false;
	p1chakBtn = false;
	p1atkBtn = false;
	p1kunaiBtn = false;
	p1assistBtn = { false,false };
	p1guardBtn = false;
	p1subBtn = false;
	p1selectBtn = false;
	p1startBtn = false;
	p2leftStick = { 0, 0 };
	p2rightStick = { 0, 0 };
	p2dpadAxis = { false, false, false, false };
	p2stickBtns = { false, false };
	p2jumpBtn = false;
	p2chakBtn = false;
	p2atkBtn = false;
	p2kunaiBtn = false;
	p2assistBtn = { false,false };
	p2guardBtn = false;
	p2subBtn = false;
	p2selectBtn = false;
	p2startBtn = false;
}
#pragma endregion

ccBattleInputs::ccBattleInputs() { InitializeValues(); }

void ccBattleInputs::GetGamepadState(int n) {
	uintptr_t p1dpad_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA8;
	uintptr_t p1btn_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA7;
	uintptr_t p1lstick_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA6;
	uintptr_t p1rstick_ptr = ccPlayer::GetSystemInfo() - 0x2D1FA5;
	uintptr_t p2dpad_ptr = ccPlayer::GetSystemInfo() - 0x2D1F8C;
	uintptr_t p2btn_ptr = ccPlayer::GetSystemInfo() - 0x2D1F8B;
	uintptr_t p2lstick_ptr = ccPlayer::GetSystemInfo() - 0x2D1F8A;
	uintptr_t p2rstick_ptr = ccPlayer::GetSystemInfo() - 0x2D1F89;

	std::byte p1dpad = *(std::byte*)p1dpad_ptr;
	std::byte p1btn = *(std::byte*)p1btn_ptr;
	std::byte p1lstick = *(std::byte*)p1lstick_ptr;
	std::byte p1rstick = *(std::byte*)p1rstick_ptr;
	std::byte p2dpad = *(std::byte*)p2dpad_ptr;
	std::byte p2btn = *(std::byte*)p2btn_ptr;
	std::byte p2lstick = *(std::byte*)p2lstick_ptr;
	std::byte p2rstick = *(std::byte*)p2rstick_ptr;

	int p1dpadI = int(p1dpad);
	if (p1dpadI >= 0x80) { p1dpadAxis[3] = true; p1dpadI -= 0x80; }
	if (p1dpadI >= 0x40) { p1dpadAxis[2] = true; p1dpadI -= 0x40; }
	if (p1dpadI >= 0x20) { p1dpadAxis[1] = true; p1dpadI -= 0x20; }
	if (p1dpadI >= 0x10) { p1dpadAxis[0] = true; p1dpadI -= 0x10; }
	if (p1dpadI >= 0x8) { p1startBtn = true;     p1dpadI -= 0x8; }
	if (p1dpadI >= 0x4) { p1stickBtns[1] = true; p1dpadI -= 0x4; }
	if (p1dpadI >= 0x2) { p1stickBtns[0] = true; p1dpadI -= 0x2; }
	if (p1dpadI >= 0x1) { p1selectBtn = true;    p1dpadI -= 0x1; }

	int p1btnI = int(p1btn);
	if (p1btnI >= 0x80) { p1assistBtn[0] = true; p1btnI -= 0x80; }
	if (p1btnI >= 0x40) { p1jumpBtn = true;      p1btnI -= 0x40; }
	if (p1btnI >= 0x20) { p1assistBtn[1] = true; p1btnI -= 0x20; }
	if (p1btnI >= 0x10) { p1chakBtn = true;      p1btnI -= 0x10; }
	if (p1btnI >= 0x8) { p1atkBtn = true;        p1btnI -= 0x8;  }
	if (p1btnI >= 0x4) { p1kunaiBtn = true;      p1btnI -= 0x4;  }
	if (p1btnI >= 0x2) { p1guardBtn = true;      p1btnI -= 0x2;  }
	if (p1btnI >= 0x1) { p1subBtn = true;        p1btnI -= 0x1;  }

	int p1lstickI = int(p1lstick);
	if (p1lstickI >= 0x80) { p1leftStick[0] += 1; p1lstickI -= 0x80; }
	if (p1lstickI >= 0x40) { p1leftStick[0] -= 1; p1lstickI -= 0x40; }
	if (p1lstickI >= 0x20) { p1leftStick[1] -= 1; p1lstickI -= 0x20; }
	if (p1lstickI >= 0x10) { p1leftStick[1] += 1; p1lstickI -= 0x10; }

	int p1rstickI = int(p1rstick);
	if (p1rstickI >= 0x8) { p1rightStick[0] += 1; p1rstickI -= 0x8; }
	if (p1rstickI >= 0x4) { p1rightStick[0] -= 1; p1rstickI -= 0x4; }
	if (p1rstickI >= 0x2) { p1rightStick[1] -= 1; p1rstickI -= 0x2; }
	if (p1rstickI >= 0x1) { p1rightStick[1] += 1; p1rstickI -= 0x1; }

	int p2dpadI = int(p2dpad);
	if (p2dpadI >= 0x80) { p2dpadAxis[3] = true; p2dpadI -= 0x80; }
	if (p2dpadI >= 0x40) { p2dpadAxis[2] = true; p2dpadI -= 0x40; }
	if (p2dpadI >= 0x20) { p2dpadAxis[1] = true; p2dpadI -= 0x20; }
	if (p2dpadI >= 0x10) { p2dpadAxis[0] = true; p2dpadI -= 0x10; }
	if (p2dpadI >= 0x8) { p2startBtn = true;     p2dpadI -= 0x8; }
	if (p2dpadI >= 0x4) { p2stickBtns[1] = true; p2dpadI -= 0x4; }
	if (p2dpadI >= 0x2) { p2stickBtns[0] = true; p2dpadI -= 0x2; }
	if (p2dpadI >= 0x1) { p2selectBtn = true;    p2dpadI -= 0x1; }

	int p2btnI = int(p2btn);
	if (p2btnI >= 0x80) { p2assistBtn[0] = true; p2btnI -= 0x80; }
	if (p2btnI >= 0x40) { p2jumpBtn = true;      p2btnI -= 0x40; }
	if (p2btnI >= 0x20) { p2assistBtn[1] = true; p2btnI -= 0x20; }
	if (p2btnI >= 0x10) { p2chakBtn = true;      p2btnI -= 0x10; }
	if (p2btnI >= 0x8) { p2atkBtn = true;        p2btnI -= 0x8;  }
	if (p2btnI >= 0x4) { p2kunaiBtn = true;      p2btnI -= 0x4;  }
	if (p2btnI >= 0x2) { p2guardBtn = true;      p2btnI -= 0x2;  }
	if (p2btnI >= 0x1) { p2subBtn = true;        p2btnI -= 0x1;  }

	int p2lstickI = int(p2lstick);
	if (p2lstickI >= 0x80) { p2leftStick[0] += 1; p2lstickI -= 0x80; }
	if (p2lstickI >= 0x40) { p2leftStick[0] -= 1; p2lstickI -= 0x40; }
	if (p2lstickI >= 0x20) { p2leftStick[1] -= 1; p2lstickI -= 0x20; }
	if (p2lstickI >= 0x10) { p2leftStick[1] += 1; p2lstickI -= 0x10; }

	int p2rstickI = int(p2rstick);
	if (p2rstickI >= 0x8) { p2rightStick[0] += 1; p2rstickI -= 0x8; }
	if (p2rstickI >= 0x4) { p2rightStick[0] -= 1; p2rstickI -= 0x4; }
	if (p2rstickI >= 0x2) { p2rightStick[1] -= 1; p2rstickI -= 0x2; }
	if (p2rstickI >= 0x1) { p2rightStick[1] += 1; p2rstickI -= 0x1; }
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

	if (debugger[0]) cout << "D-Pad:\t" << "(" << p1dpadAxis[0] << "," << p1dpadAxis[1] << "," << p1dpadAxis[2] << "," << p1dpadAxis[3] << ")" << endl;
	if (debugger[1]) cout << "Buttons:\t" << btn << endl;
	if (debugger[2]) cout << "Left Stick:\t" << "(" << p1leftStick[0] << "," << p1leftStick[1] << ")" << endl;
	if (debugger[3]) cout << "Right Stick:\t" << "(" << p1rightStick[0] << "," << p1rightStick[1] << ")" << endl;
	cout << endl;
}

string ccBattleInputs::Btn2Str() {
	string result = "";
	if (p1jumpBtn) result += "Jump, ";
	if (p1atkBtn) result += "Attack, ";
	if (p1kunaiBtn) result += "Kunai, ";
	if (p1chakBtn) result += "Chakra, ";

	if (p1assistBtn[0]) result += "Assist1, ";
	if (p1assistBtn[1]) result += "Assist2, ";
	if (p1guardBtn) result += "Guard, ";
	if (p1subBtn) result += "Sub, ";

	if (p1stickBtns[0]) result += "L3, ";
	if (p1stickBtns[1]) result += "R3, ";
	if (p1selectBtn) result += "Select, ";
	if (p1startBtn) result += "Start";

	if (result[result.length() - 1] == ' ') result = result.substr(0, result.length() - 2);

	return result;
}