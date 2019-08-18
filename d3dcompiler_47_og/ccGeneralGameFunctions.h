#pragma once

#include <vector>

using namespace std;

namespace moddingApi
{
	class ccGeneralGameFunctions
	{
	public:
		static BYTE MAX_GAME_VERSION;

		static void * PTR_GAMEINFO_00;
		static void DoGameInfoHook();
		static uintptr_t SetGameInfoPointer(uintptr_t a1);

		static void CpkLoadList();

		static int SetMaxVersion();
		static int GetVersionNumber();
		static char* GetVersionString();
		static char* GetVersionStringAPI();
		static uintptr_t GetRyoPointer();
		static int GetGameMoney();
		static char* MessageToString(char *);

		// Files
		static int cpkcount;
		static uintptr_t Cpk_LoadXfbin(void *);

		// Adventure
		static int OpenAdvMessageById(char *);

		// Loading
		static int StartLoad();
		static int EndLoad();

		// Dictionary
		static vector<std::string> MessageID;
		static vector<std::string> MessageStr;
		static BYTE ViewMessageConversions;

		static uintptr_t Hook_MsgToString(uintptr_t);
		static uintptr_t Hook_MsgToString_Alt(uintptr_t);

		// Gamepad
		static bool TestButton(WORD);
	};
}