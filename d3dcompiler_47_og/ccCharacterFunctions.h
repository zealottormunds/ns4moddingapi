#ifndef CHARAFUNCTIONS_H 
#define CHARAFUNCTIONS_H
#pragma once

#include <vector>

namespace moddingApi
{
	class ccCharacterFunctions
	{
	public:
		int test();
		void static ReloadCharsel();
		void static DoCharacterSelectParamHook();

		int static PartnerCount;

		static std::vector<uintptr_t> c_partnerFunctions;
		static std::vector<int> c_partnerCodes;
		static void PartnerFunctions();

		static std::vector<uintptr_t> c_specialCondFunct;
		static std::vector<int> c_specialCondCodes;
		static void SpecialCondFunctions();

		static std::vector<uintptr_t> charPointer;
		static std::vector<long long> charAllocTime;
		static void Hook_COND_BKKX();
		static void EnableControl(int character, int pad);
	};
}

#endif