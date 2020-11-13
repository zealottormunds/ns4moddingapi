#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <DirectXMath.h>
#include <math.h>

namespace moddingApi
{
	class WorldCollision
	{
	public:
		static BYTE world[100][100][50];
		static int world_offset_x;
		static int world_offset_y;
		static int world_offset_z;
		static void Initialize(std::string world);
		static void setblock(int x, int y, int z, int s);
		static void setblocks(int x1, int y1, int z1, int x2, int y2, int z2, int s);
	};
}