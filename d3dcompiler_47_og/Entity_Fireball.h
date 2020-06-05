#pragma once

namespace moddingApi
{
	class Entity_Fireball
	{
	public:
		Entity_Fireball(uintptr_t gObj) : gameObjectPtr(gObj)
		{

		}

		uintptr_t gameObjectPtr = 0;

		void Loop();
	};
}