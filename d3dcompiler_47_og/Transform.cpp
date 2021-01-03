#include <math.h>
#include "Transform.h"

using namespace std;
using namespace moddingApi;

Vector3 Transform::forward()
{
	float x = (10 * cos(rotx));
	float y = (10 * sin(rotx));
	float z = 0;

	return Vector3(x, y, z);
}

Vector3 Transform::right()
{
	float x = (10 * sin(rotx));
	float y = -(10 * cos(rotx));
	float z = 0;

	return Vector3(x, y, z);
}

Vector3 Transform::up()
{
	float x = 0;
	float y = 0;
	float z = 10;

	return Vector3(x, y, z);
}