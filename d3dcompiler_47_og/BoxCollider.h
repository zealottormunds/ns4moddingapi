#pragma once
#include "Vector3.h"
#include <cstdint>

namespace moddingApi
{
	class BoxCollider
	{
	public:
		uintptr_t gameObjectPtr;
		Vector3 center;
		Vector3 scale;

		BoxCollider(uintptr_t gameObject, Vector3 _center, Vector3 _scale) : gameObjectPtr(gameObject), center(_center), scale(_scale)
		{

		}

		static bool isColliding(BoxCollider a, BoxCollider b);
	};
}