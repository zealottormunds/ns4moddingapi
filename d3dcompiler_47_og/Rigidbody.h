#pragma once

#include <vector>
#include "Vector3.h"
#include "Transform.h"
#include "WorldCollision.h"
#include "BoxCollider.h"

namespace moddingApi
{
	class Rigidbody
	{
	public:
		Rigidbody(Transform& a, BoxCollider& b) : transform(a), timeSinceCollision(0), collider(b)
		{

		}

		static float gravity;
		BoxCollider collider;
		Transform transform;
		Vector3 actualForce = Vector3(0, 0, 0);

		float timeSinceCollision = 0;
		void physics();
		int actualBlock();
		bool canTranslate(Vector3 a);
		static Vector3 translatePosition(Vector3 from, Vector3 to, Transform t);
	};
}