#pragma once

#include <vector>

namespace moddingApi
{
	class Interactive_Examine
	{
	public:
		Interactive_Examine(uintptr_t gObj) : gameObjectPtr(gObj)
		{

		}

		uintptr_t gameObjectPtr = 0;
		void StartAction();
		int actualState = 0;
		std::vector<uintptr_t> message1Ptr;
		std::vector<uintptr_t> message2Ptr;
		void AddText(uintptr_t msg1, uintptr_t msg2);
	};
}