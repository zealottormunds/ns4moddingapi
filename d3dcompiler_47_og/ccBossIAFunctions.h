#ifndef BOSSIAFUNCTIONS_H 
#define BOSSIAFUNCTIONS_H
#pragma once

namespace moddingApi
{
	class ccBossIAFunctions
	{
	public:
		static int ccSceneBoss01Phase0Load(uintptr_t);
		static int ccSceneBoss01Phase1Load(uintptr_t);
		static int ccSceneBoss01Phase4Load(uintptr_t);
		static void LoadSwordQTE(uintptr_t, char *, char *);
		static __int64 ccPlayIA(char *);
		static int ccOpenHudMoney();
	};
}

#endif