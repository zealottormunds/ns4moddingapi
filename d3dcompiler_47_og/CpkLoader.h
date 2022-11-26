#ifndef DECOMP_GAMESETTINGS_H 
#define DECOMP_GAMESETTINGS_H
#pragma once

#include <stdio.h>
#include <vector>

class CpkLoader
{
public:
	static int LoadCpkInitial();
	static __int64 LoadCpkSecondary(__int64 a1);
	static std::vector<const char*> CpkToLoad;
	static std::vector<int> CpkPriority;

	struct cpkdata
	{
		const char* path;
		__int64 priority;
	};
};

#endif
