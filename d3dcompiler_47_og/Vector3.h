#pragma once

#include <vector>

namespace moddingApi
{
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
		{

		}

		static float Distance(Vector3 a, Vector3 b);
		static Vector3 zero();
		static Vector3 one();
		static Vector3 add(Vector3 a, Vector3 b);
		static Vector3 sub(Vector3 a, Vector3 b);
		static Vector3 mag(Vector3 a, float b);
		static bool cmp(Vector3 a, Vector3 b);
	
		static Vector3 getBlockPos(Vector3 a);
		static float magnitude(Vector3 a);
		static Vector3 normalize(Vector3 a);
		static Vector3 lerp(Vector3 a, Vector3 b, float m);
	};
}