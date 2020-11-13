#pragma once

#include <vector>
#include "Vector3.h"

namespace moddingApi
{
	class Transform
	{
	public:
		Transform() : position(Vector3(0,0,0)), rotx(0), roty(0)
		{

		}

		Vector3 position;
		float rotx;
		float roty;

		Vector3 forward();
		Vector3 right();
		Vector3 up();
	};
}