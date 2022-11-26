#ifndef CCGENERALGAMEFUNCTIONS_H 
#define CCGENERALGAMEFUNCTIONS_H
#pragma once

#include <vector>

namespace moddingApi
{
	class ccGeneralGameFunctions
	{
	public:
		static char* MessageToString(char *);

		// Dictionary
		static char ViewMessageConversions;

		static uintptr_t Hook_MsgToString(uintptr_t);
		static uintptr_t Hook_MsgToString_Alt(uintptr_t);
	};
}

#endif