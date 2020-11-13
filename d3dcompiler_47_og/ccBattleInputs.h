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
		static vector<float> leftStick;
		static vector<float> rightStick;
		static vector<bool> dpadAxis;
		static vector<bool> stickBtns;

		// Face Buttons
		static bool jumpBtn;
		static bool chakBtn;
		static bool atkBtn;
		static bool kunaiBtn;

		// Front Buttons
		static vector<bool> assistBtn;
		static bool guardBtn;
		static bool subBtn;

		// Additional Buttons
		static bool selectBtn;
		static bool startBtn;

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