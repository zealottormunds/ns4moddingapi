#ifndef PRMFUNCTIONS_H 
#define PRMFUNCTIONS_H
#pragma once

#include <string>

namespace moddingApi
{
	class PrmFunctions
	{
	public:
		static char OriginalFunctions[];
		static void ImplementFunctions();

		static const int NEW_ME_ID = 0x121;
		static __int64 FUNCTION_ADDRESS[];

		static __int64 __fastcall ME_HEAL_PLAYER(__int64 a1);
		static __int64 __fastcall ME_COUT_TEST(__int64 a1);
	};
}

#endif