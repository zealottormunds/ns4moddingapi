#pragma once

#include <vector>

namespace moddingApi
{
	class InteractiveMain
	{
	public:
		InteractiveMain(uintptr_t gObj) : gameObjectPtr(gObj)
		{

		}

		uintptr_t gameObjectPtr = 0;

		enum InteractiveType
		{
			Null,
			Examine,
			Door,
			Item,
			NPC,
			Breakable,
			Enemy
		};

		InteractiveType interaction = Null;
		void StartAction();
		void StartActionAlt();
	};
}