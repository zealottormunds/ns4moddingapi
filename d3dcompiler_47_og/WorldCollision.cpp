#include <math.h>
#include "Transform.h"
#include "WorldCollision.h"

using namespace std;
using namespace moddingApi;

BYTE WorldCollision::world[100][100][50]{ {{0}} };
int WorldCollision::world_offset_x = 15;
int WorldCollision::world_offset_y = 20;
int WorldCollision::world_offset_z = 0;

#include "LuaHook.h"

void WorldCollision::setblock(int x, int y, int z, int s)
{
	WorldCollision::world[world_offset_x + x][world_offset_y + y][world_offset_z + z] = s;

	/*string a = "col_";
	a = a + to_string(x) + to_string(y) + to_string(z);
	LuaHook::fc_ccCreateCastByChunk((char*)a.c_str(), "data/st/st_efp.xfbin", "st_e_memo");
	LuaHook::fc_ccSetCastPosition((char*)a.c_str(), x * 100, y * 100, z * 100);*/
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
	else if (world == "Scene_PrisonPrologue")
	{
		WorldCollision::world_offset_x = 2;
		WorldCollision::world_offset_y = 32;
		WorldCollision::world_offset_z = 10;

		// Walls jail
		WorldCollision::setblocks(-2, -3, 0, -2, 3, 3, 1);
		WorldCollision::setblocks(2, -3, 0, 2, 1, 3, 1);
		WorldCollision::setblocks(-2, -3, 0, 2, -3, 3, 1);
		WorldCollision::setblocks(-2, 3, 0, 2, 3, 3, 1);
		// Floor jail
		WorldCollision::setblocks(-1, -2, -2, 2, 2, -1, 1);

		// Trigger jump cutscene
		WorldCollision::setblocks(7, -3, 0, 7, 3, 3, 2);

		// Walls hub
		WorldCollision::setblocks(2, -4, 0, 9, -4, 3, 1);
		WorldCollision::setblocks(2, 4, 0, 9, 4, 3, 1);
		// Floor hub
		WorldCollision::setblocks(3, -3, -2, 8, 3, -1, 1);

		// Platforms
		WorldCollision::setblock(9, 0, -1, 1);
		WorldCollision::setblock(10, 0, -1, 1);
		WorldCollision::setblock(16, 0, -1, 1);
		WorldCollision::setblock(17, 0, -1, 1);
		WorldCollision::setblock(23, 0, -1, 1);
		WorldCollision::setblock(24, 0, -1, 1);
		WorldCollision::setblock(30, 0, -1, 1);
		WorldCollision::setblock(31, 0, -1, 1);

		// Platforms right
		WorldCollision::setblocks(19, -6, -2, 21, -4, -1, 1);
		WorldCollision::setblocks(19, -12, -2, 21, -10, -1, 1);
		WorldCollision::setblocks(19, -18, -2, 21, -16, -1, 1);
		WorldCollision::setblocks(13, -32, -2, 27, -19, -1, 1);

		// Platforms left
		WorldCollision::setblocks(19, 4, -2, 21, 6, -1, 1);
		WorldCollision::setblocks(19, 10, -2, 21, 12, -1, 1);
		WorldCollision::setblocks(19, 16, -2, 21, 18, -1, 1);

		// Floor 2nd room
		WorldCollision::setblocks(32, -3, -2, 37, 3, -1, 1);
		// Trigger door cutscene
		WorldCollision::setblocks(32, -3, 0, 32, 3, 3, 3);
	}
	else if (world == "Scene_InnSmoothTea")
	{
		WorldCollision::world_offset_x = 25;
		WorldCollision::world_offset_y = 25;
		WorldCollision::world_offset_z = 10;

		// Floor jail
		WorldCollision::setblocks(-25, -25, -2, 25, 25, -1, 1);
	}

	/*// Konoha door
	WorldCollision::setblocks(-7, -10, 0, 7, -10, 6, 1);

	// Floor
	WorldCollision::setblocks(-15, -18, 0, 15, 32, 0, 1);
	WorldCollision::setblocks(-15, 33, -1, 15, 37, -1, 1);
	WorldCollision::setblocks(-15, 38, -2, 15, 43, -2, 1);
	WorldCollision::setblocks(-15, 44, -3, 15, 48, -3, 1);*/
}