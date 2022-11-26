#pragma once

#include <string>
class PatternScan
{
public:
	static __int64 Scan(std::string pattern, __int64 startIndex = 0, bool backwards = false);
};