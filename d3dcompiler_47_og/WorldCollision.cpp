#include <math.h>
#include "Transform.h"
#include "WorldCollision.h"

using namespace std;
using namespace moddingApi;

BYTE WorldCollision::world[100][100][50]{{{0}}};
int WorldCollision::world_offset_x = 15;
int WorldCollision::world_offset_y = 20;
int WorldCollision::world_offset_z = 0;

#include "LuaHook.h"

void WorldCollision::setblock(int x, int y, int z, int s)
{
	WorldCollision::world[world_offset_x + x][world_offset_y + y][world_offset_z + z] = s;
}

void WorldCollision::setblocks(int x1, int y1, int z1, int x2, int y2, int z2, int s)
{
	for (int x = x1; x <= x2; x++)
	{
		for (int y = y1; y <= y2; y++)
		{
			for (int z = z1; z <= z2; z++)
			{
				WorldCollision::setblock(x, y, z, s);
			}
		}
	}
}

void WorldCollision::Initialize(std::string world)
{
	// Restart
	std::memset(WorldCollision::world, 0, sizeof WorldCollision::world);

	if (world == "Scene_PlayerHouse")
	{
		WorldCollision::world_offset_x = 6;
		WorldCollision::world_offset_y = 6;
		WorldCollision::world_offset_z = 0;

		// Walls
		WorldCollision::setblocks(4, -5, 0, 4, 5, 3, 1);
		WorldCollision::setblocks(-4, -5, 0, -4, 5, 3, 1);
		WorldCollision::setblocks(-5, -4, 0, 5, -4, 3, 1);

		// Walls door
		WorldCollision::setblocks(1, 4, 0, 5, 4, 3, 1);
		WorldCollision::setblocks(-5, 4, 0, -1, 4, 3, 1);
		WorldCollision::setblocks(-5, 5, 0, 5, 5, 3, 1);

		// Furniture 1
		WorldCollision::setblocks(-4, 3, 0, -1, 4, 3, 1);

		// Bed
		WorldCollision::setblocks(2, 0, 0, 4, 4, 3, 1);

		// Furniture 2
		WorldCollision::setblocks(-4, -4, 0, -2, -4, 3, 1);
	}
}