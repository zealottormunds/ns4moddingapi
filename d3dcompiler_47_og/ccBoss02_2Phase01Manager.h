#ifndef DECOMP_CCBOSS02_2PHASE01MANAGER_H 
#define DECOMP_CCBOSS02_2PHASE01MANAGER_H
#pragma once

#include <stdio.h>
#include <vector>

namespace moddingApi
{
	class ccBoss02_2Phase01Manager
	{
	public:
		static __int64 __fastcall fc_DoFunction(__int64 a1, __int64 a2);
		static void __fastcall BossBattleBKKU_Loop00(__int64 a1);
		static void __fastcall BossBattleBKKU_Loop01(__int64 a1);
	};
}

#endif