#pragma once

#include <stdio.h>
#include <windows.h>
#include "Vector3.h"

using namespace std;

namespace moddingApi
{
	class ccBattleInputs
	{
	public:
		// Axes + L3/R3
		static vector<float> p1leftStick;
		static vector<float> p1rightStick;
		static vector<bool> p1dpadAxis;
		static vector<bool> p1stickBtns;

		// Face Buttons
		static bool p1jumpBtn;
		static bool p1chakBtn;
		static bool p1atkBtn;
		static bool p1kunaiBtn;

		// Front Buttons
		static vector<bool> p1assistBtn;
		static bool p1guardBtn;
		static bool p1subBtn;

		// Additional Buttons
		static bool p1selectBtn;
		static bool p1startBtn;

		// Axes + L3/R3
		static vector<float> p2leftStick;
		static vector<float> p2rightStick;
		static vector<bool> p2dpadAxis;
		static vector<bool> p2stickBtns;

		// Face Buttons
		static bool p2jumpBtn;
		static bool p2chakBtn;
		static bool p2atkBtn;
		static bool p2kunaiBtn;

		// Front Buttons
		static vector<bool> p2assistBtn;
		static bool p2guardBtn;
		static bool p2subBtn;

		// Additional Buttons
		static bool p2selectBtn;
		static bool p2startBtn;

		// Functions
		ccBattleInputs();
		static void ccBattleInputs::Loop(int n);
		static void ccBattleInputs::Loop(int n, std::vector<bool> debugger);
	private:
		static void ccBattleInputs::InitializeValues();
		static void ccBattleInputs::GetGamepadState(int n);
		static string ccBattleInputs::Btn2Str();
	};
}