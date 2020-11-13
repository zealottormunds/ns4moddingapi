#pragma once

#include <stdio.h>
using namespace std;

namespace moddingApi
{
	class ccBattleFunctions
	{
	public:
		static uintptr_t Battle_FillChakra(uintptr_t a1, int a2, float FillRate);
		static uintptr_t Battle_FillSubstitution(uintptr_t a1, int a2, float FillRate);
		static uintptr_t Battle_FillTemp(uintptr_t a1, int a2, float FillRate);
	};
}