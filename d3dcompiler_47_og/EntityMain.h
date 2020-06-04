#pragma once

#include <vector>

namespace moddingApi
{
	class EntityMain
	{
	public:
		EntityMain(uintptr_t gObj) : gameObjectPtr(gObj)
		{

		}

		uintptr_t gameObjectPtr = 0;

		enum EntityType
		{
			Null,
			Fireball
		};

		EntityType entity = Null;
		void Loop();
	};
}