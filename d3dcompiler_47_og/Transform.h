#ifndef TRANSFORM_H 
#define TRANSFORM_H
#pragma once

#include "Vector3.h"

namespace moddingApi
{
	class Transform
	{
	public:
		Transform() : position(Vector3(0, 0, 0)), rotx(0), roty(0)
		{

		}

		Transform(Vector3 pos, float rx = 0, float ry = 0) : position(Vector3(pos.x, pos.y, pos.z)), rotx(rx), roty(ry)
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

#endif