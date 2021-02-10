#ifndef CCGENERALGAMEFUNCTIONS_H 
#define CCGENERALGAMEFUNCTIONS_H
#pragma once

#include <vector>

namespace moddingApi
{
	class ccGeneralGameFunctions
	{
	public:
		static int GetVersionNumber();
		static char* MessageToString(char *);

		// Dictionary
		static std::vector<std::string> MessageID;
		static std::vector<std::string> MessageStr;
		static char ViewMessageConversions;

		static uintptr_t Hook_MsgToString(uintptr_t);
		static uintptr_t Hook_MsgToString_Alt(uintptr_t);

		// Gamepad
		static bool TestButton(unsigned short);
		static signed __int64 enablePads();

		static int GetCurrentFrame();
		static int GetFPS();
		static bool IsFocus();
	};
}

#endif