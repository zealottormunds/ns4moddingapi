#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

namespace moddingApi
{
	class ccCharacterFunctions
	{
	public:
		int test();
		void static ReloadCharsel();
		void static DoCharacterSelectParamHook();

		int static PartnerCount;

		static vector<uintptr_t> c_partnerFunctions;
		static vector<int> c_partnerCodes;
		static void PartnerFunctions();

		static vector<uintptr_t> c_specialCondFunct;
		static vector<int> c_specialCondCodes;
		static void SpecialCondFunctions();
	};
}