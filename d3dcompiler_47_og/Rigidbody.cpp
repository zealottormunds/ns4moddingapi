#include <math.h>
#include "Rigidbody.h"

using namespace std;
using namespace moddingApi;

float Rigidbody::gravity = 25;

void Rigidbody::physics()
{

}

int Rigidbody::actualBlock()
{
	return 0;
}

bool Rigidbody::canTranslate(Vector3 a)
{
	return false;
}

Vector3 Rigidbody::translatePosition(Vector3 from, Vector3 to, Transform t)
{
	return Vector3(0, 0, 0);
}