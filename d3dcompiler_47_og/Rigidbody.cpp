#include <math.h>
#include "Rigidbody.h"

using namespace std;
using namespace moddingApi;

float Rigidbody::gravity = 25;

void Rigidbody::physics()
{
	Vector3& pos = transform.position;
	//cout << "tx: " << pos.x << ", ty: " << pos.y << ", tz: " << pos.z << endl;
	Vector3 block = Vector3::getBlockPos(Vector3::add(pos, Vector3(0, 0, -5)));
	Vector3 rigidbodyPosition = block;
	//cout << "bx: " << rigidbodyPosition.x << ", by: " << rigidbodyPosition.y << ", bz: " << rigidbodyPosition.z << endl;

	int offset_x = WorldCollision::world_offset_x;
	int offset_y = WorldCollision::world_offset_y;
	int offset_z = WorldCollision::world_offset_z;

	//Vector3 phy = Vector3(0, 0, 0);

	switch (WorldCollision::world[(int)rigidbodyPosition.x + offset_x][(int)rigidbodyPosition.y + offset_y][(int)rigidbodyPosition.z + offset_z])
	{
	default:
		timeSinceCollision = timeSinceCollision + 1;
		actualForce.z = -Rigidbody::gravity * (timeSinceCollision / 100);
		break;
	case 1:
		timeSinceCollision = 0;
		break;
	case 2:
		timeSinceCollision = 0;
		break;
	}

	//return phy;
}

int Rigidbody::actualBlock()
{
	Vector3& pos = transform.position;
	Vector3 block = Vector3::getBlockPos(pos);
	Vector3 rigidbodyPosition = block;

	int offset_x = WorldCollision::world_offset_x;
	int offset_y = WorldCollision::world_offset_y;
	int offset_z = WorldCollision::world_offset_z;

	return WorldCollision::world[(int)rigidbodyPosition.x + offset_x][(int)rigidbodyPosition.y + offset_y][(int)rigidbodyPosition.z + offset_z];
}

bool Rigidbody::canTranslate(Vector3 a)
{
	bool can = false;

	Vector3 rigidbodyPosition = Vector3::getBlockPos(a);

	int offset_x = WorldCollision::world_offset_x;
	int offset_y = WorldCollision::world_offset_y;
	int offset_z = WorldCollision::world_offset_z;

	switch (WorldCollision::world[(int)rigidbodyPosition.x + offset_x][(int)rigidbodyPosition.y + offset_y][(int)rigidbodyPosition.z + offset_z])
	{
	default:
		can = true;
		break;
	case 1:
		can = false;
		break;
	}

	return can;
}

Vector3 Rigidbody::translatePosition(Vector3 from, Vector3 to, Transform t)
{
	Vector3 result = Vector3(to.x, to.y, to.z);
	Vector3 rigidbodyPosition = Vector3::getBlockPos(to);

	Vector3 dirVector = Vector3(to.x - from.x, to.y - from.y, to.z - from.z);

	Vector3 fromPosition = Vector3::getBlockPos(from
		//Vector3::add(
		//	from,
		//	Vector3::mag(dirVector, 25)
		//)
	);

	int offset_x = WorldCollision::world_offset_x;
	int offset_y = WorldCollision::world_offset_y;
	int offset_z = WorldCollision::world_offset_z;

	BYTE toblock = WorldCollision::world[(int)rigidbodyPosition.x + offset_x][(int)rigidbodyPosition.y + offset_y][(int)rigidbodyPosition.z + offset_z + 1]; // +1 cus z
	
	if (toblock == 0) return result;

	result.x = from.x;
	result.y = from.y;
	result.z = from.z;

	BYTE toblocknox = WorldCollision::world[(int)rigidbodyPosition.x + offset_x][(int)fromPosition.y + offset_y][(int)fromPosition.z + offset_z + 1]; // +1 cus z
	BYTE toblocknoy = WorldCollision::world[(int)fromPosition.x + offset_x][(int)rigidbodyPosition.y + offset_y][(int)fromPosition.z + offset_z + 1]; // +1 cus z
	BYTE toblocknoz = WorldCollision::world[(int)fromPosition.x + offset_x][(int)fromPosition.y + offset_y][(int)rigidbodyPosition.z + offset_z + 1]; // +1 cus z

	if (toblocknox != 1)
	{
		result.x = to.x;
	}

	if (toblocknoy != 1)
	{
		result.y = to.y;
	}

	if (toblocknoz != 1)
	{
		result.z = to.z;
	}

	return result;
}