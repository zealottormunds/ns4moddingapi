#pragma once
#include <string>
#include <vector>

class SpecialConditionManager
{
public:
	struct GameCondition
	{
		std::string COND_TYPE = "";
		__int64 address = 0;
	};

	struct Condition
	{
		int characode = -1;
		__int64 address = 0;
	};

	static std::vector<GameCondition*> condList;
	static std::vector<Condition*> charCondList;
	static __int64 condAlloc;

	static void ReadSpecialConditionParam(std::string _file);
	static void SpecialCondFunctions();
};