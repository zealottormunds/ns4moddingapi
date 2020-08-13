#include <math.h>
#include "Vector3.h"

using namespace std;
using namespace moddingApi;

float x = 0;
float y = 0;
float z = 0;

float Vector3::Distance(Vector3 a, Vector3 b)
{
	float d = sqrtf(
		pow((b.x - a.x), 2) + 
		pow((b.y - a.y), 2) + 
		pow((b.z - a.z), 2)
	);
	return d;
}

Vector3 Vector3::zero()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::one()
{
	return Vector3(0, 0, 0);
}

Vector3 Vector3::add(Vector3 a, Vector3 b)
{
	Vector3 c = Vector3::zero();
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

Vector3 Vector3::sub(Vector3 a, Vector3 b)
{
	Vector3 c = Vector3::zero();
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

bool Vector3::cmp(Vector3 a, Vector3 b)
{
	bool equal = false;

	if (a.x == b.x && a.y == b.y && a.z == b.z) equal = true;

	return equal;
}

Vector3 Vector3::mag(Vector3 a, float b)
{
	return Vector3(a.x * b, a.y * b, a.z * b);
}

int RoundDown(int toRound)
{
	return toRound - toRound % 100;
}

Vector3 Vector3::getBlockPos(Vector3 a)
{
	Vector3 n = Vector3(0, 0, 0);

	n.x = RoundDown(int(a.x)) / 100;
	n.y = RoundDown(int(a.y)) / 100;
	n.z = RoundDown(int(a.z)) / 100;

	return n;
}

float Vector3::magnitude(Vector3 a)
{
	if (a.x == 0 && a.y == 0 && a.z == 0) return 0;

	float mag = sqrtf(
		pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)
	);
	
	return mag;
}

Vector3 Vector3::normalize(Vector3 a)
{
	float mag = Vector3::magnitude(a);

	Vector3 normalized = Vector3(a.x / mag, a.y / mag, a.z / mag);
	return normalized;
}

Vector3 Vector3::lerp(Vector3 a, Vector3 b, float m)
{
	float addtox = b.x - a.x;
	float addtoy = b.y - a.y;
	float addtoz = b.z - a.z;

	return Vector3
	(
		a.x + (addtox * m),
		a.y + (addtoy * m),
		a.z + (addtoz * m)
	);
}

bool Vector3::operator==(const Vector3& vector) const
{
	bool equal = false;

	if (x == vector.x && y == vector.y && z == vector.z) equal = true;

	return equal;
}

Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator-(const Vector3 & vector) const
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator*(const float mag) const
{
	return Vector3(x * mag, y * mag, z * mag);
}

Vector3 Vector3::operator/(const float mag) const
{
	return Vector3(x / mag, y / mag, z / mag);
}