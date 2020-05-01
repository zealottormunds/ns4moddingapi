#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "MultiMatch.h"
#include "LuaHook_Commands.h"
#include "LuaHook.h"
#include "ccCharacterFunctions.h"

#include "d3dcompiler_47_og.h"

using namespace std;
using namespace moddingApi;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

typedef struct
{
	float x;
	float z;
	float y;
}Vector3;

Vector3* c_Vector3(float x, float z, float y)
{
	Vector3* a = (Vector3*)malloc(sizeof(Vector3));
	a->x = x;
	a->z = z;
	a->y = y;

	return a;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int MultiMatch::p_BaseStock[4];
int MultiMatch::p_UsedStock[4];
char* MultiMatch::p_Chars[4];

int MultiMatch::ccInitializeMultiMatch(__int64 a1)
{
	__int64 ptr;
	if (LuaHook::funct_getArgument_noobject(a1, 1, (__int64)&ptr))
	{
		// Initial values
		MultiMatch::p_BaseStock[0] = 3;
		MultiMatch::p_BaseStock[1] = 3;
		MultiMatch::p_BaseStock[2] = 3;
		MultiMatch::p_BaseStock[3] = 3;

		MultiMatch::p_UsedStock[0] = 0;
		MultiMatch::p_UsedStock[1] = 0;
		MultiMatch::p_UsedStock[2] = 0;
		MultiMatch::p_UsedStock[3] = 0;

		MultiMatch::p_Chars[0] = "GP_CHAR_ID_2NRT";
		MultiMatch::p_Chars[1] = "GP_CHAR_ID_2FOU";
		MultiMatch::p_Chars[2] = "GP_CHAR_ID_2SKR";
		MultiMatch::p_Chars[3] = "GP_CHAR_ID_2DDR";

		ccCharacterFunctions::EnableControl(0, 0);

		// Initialize characters
		for (int x = 1; x < 4; x++)
		{
			// Create spawn for char
			LuaHook_Commands::ccPlayerPoolSet(p_Chars[x], 1);
			LuaHook_Commands::ccEntryReSpawnID(p_Chars[x], 1, 0);
			LuaHook_Commands::ccEntryGroupBattleChar(p_Chars[x], true, true, 0, 0, 0, 0, 1, "", -1);
			p_UsedStock[x] = 1;

			// Init pads
			//ccCharacterFunctions::EnableControl(x, x);

			__int64 characterPointer = ccCharacterFunctions::charPointer[x];
			float * posX = (float*)(characterPointer + 0x70);
			float * posZ = (float*)(characterPointer + 0x74);
			float * posY = (float*)(characterPointer + 0x78);

			Vector3* spawnList[4] = { c_Vector3(1000, 1000, 0), c_Vector3(1000, -1000, 0), c_Vector3(-1000, 1000, 0), c_Vector3(-1000, -1000, 0) };

			Vector3* a = spawnList[x];
			*posX = a->x;
			*posZ = a->z;
			*posY = a->y;
		}
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

float DistancePoint(float a1, float a2, float a3, float a4, float a5, float a6)
{
	return sqrt(
		pow(a1 - a4, 2) +
		pow(a2 - a5, 2) +
		pow(a3 - a6, 2)
	);
}

float DistanceCoord(float a1, float a2)
{
	return sqrt(pow(a1 - a2, 2));
}

int MultiMatch::ccMultiMatchCameraLoop()
{
	int playerCount = ccCharacterFunctions::charPointer.size();

	float px = 0;
	float pz = 0;
	float py = 0;
	float pa = 0.8f;

	vector<float> positions;

	for (int a = 0; a < playerCount; a++)
	{
		float act_x = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float act_z = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float act_y = *(float*)(ccCharacterFunctions::charPointer[a] + 0x78);

		px = px + act_x;
		pz = pz + act_z;
		py = py + act_y;
	}

	px = px / playerCount;
	pz = pz / playerCount;
	py = py / playerCount;

	float maxDistCenter = 0;
	float maxDistCenterPoint[3] = { 0, 0, 0 };

	for (int a = 0; a < playerCount; a++)
	{
		float act_x = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float act_z = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float act_y = *(float*)(ccCharacterFunctions::charPointer[a] + 0x78);

		float actual = sqrt(
			pow(act_x, 2) +
			pow(act_z, 2) +
			pow(act_y, 2)
		);

		if (actual > maxDistCenter)
		{
			maxDistCenter = actual;
			maxDistCenterPoint[0] = act_x;
			maxDistCenterPoint[1] = act_z;
			maxDistCenterPoint[2] = act_y;
		};
	}

	float maxDistPlayer = 0;
	float maxDistPlayerPoint[3] = { 0, 0, 0 };

	for (int a = 0; a < playerCount; a++)
	{
		float act_x = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float act_z = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float act_y = *(float*)(ccCharacterFunctions::charPointer[a] + 0x78);

		float actual = sqrt(
			pow(act_x - maxDistCenterPoint[0], 2) +
			pow(act_z - maxDistCenterPoint[1], 2) +
			pow(act_y - maxDistCenterPoint[2], 2)
		);

		if (actual > maxDistPlayer)
		{
			maxDistPlayer = actual;
			maxDistPlayerPoint[0] = act_x;
			maxDistPlayerPoint[1] = act_z;
			maxDistPlayerPoint[2] = act_y;
		};
	}

	// Get furthest to center x, get furthest x to it
	float x_p0 = 0;
	float x_p0_dc = 0;
	int x_p0_n = -1;
	for (int a = 0; a < playerCount; a++)
	{
		float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float dst = DistanceCoord(act, 0);

		if (dst > x_p0_dc)
		{
			x_p0_dc = dst;
			x_p0 = act;
			x_p0_n = a;
		}
	}
	float x_p1 = 0;
	float x_p1_dp0 = 0;
	for (int a = 0; a < playerCount; a++)
	{
		if (a != x_p0_n)
		{
			float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
			float dst = DistanceCoord(act, x_p0);

			if (dst > x_p1_dp0)
			{
				x_p1_dp0 = dst;
				x_p1 = act;
			}
		}
	}

	// Get furthest to center z, get furthest z to it
	float z_p0 = 0;
	float z_p0_dc = 0;
	int z_p0_n = -1;
	for (int a = 0; a < playerCount; a++)
	{
		float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float dst = DistanceCoord(act, 0);

		if (dst > z_p0_dc)
		{
			z_p0_dc = dst;
			z_p0 = act;
			z_p0_n = a;
		}
	}
	float z_p1 = 0;
	float z_p1_dp0 = 0;
	for (int a = 0; a < playerCount; a++)
	{
		if (a != z_p0_n)
		{
			float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
			float dst = DistanceCoord(act, z_p0);

			if (dst > z_p1_dp0)
			{
				z_p1_dp0 = dst;
				z_p1 = act;
			}
		}
	}

	float px_m = (x_p0 + x_p1) / 2;
	float pz_m = (z_p0 + z_p1) / 2;

	float dist = 500 + (maxDistPlayer * 1.1f);
	LuaHook::ccGroupBattleEventCameraMovePosBegin(px_m, pz_m - (400 + (dist * 1.3f)), dist, pa);
	LuaHook::ccGroupBattleEventCameraMoveLookBegin(px_m, pz_m + 400, 100, pa);

	return 0;
}

string FloatToString(float f)
{
	string a = "";

	if (f > 99)
	{
		a = to_string(f).substr(0, 3);
	}
	else if(f > 9)
	{
		a = to_string(f).substr(0, 2);
	}
	else
	{
		a = to_string(f).substr(0, 1);
	}

	return a;
}

int lastseconds = 0;
int seconds = 0;
int MultiMatch::ccMultiMatchShowPlayerStatus(__int64 a1)
{
	__int64 ptr;
	if (LuaHook::funct_getArgument_number(a1, 1, 0, (__int64)&ptr) && LuaHook::funct_getArgument_noobject(a1, 2, (__int64)&ptr))
	{
		seconds = stoi(string((char*)LuaHook::funct_returnArgument_string(a1, 1, 0)));
		//cout << seconds << endl;

		if (seconds > lastseconds + 1)
		{
			//cout << "Done" << endl;
			lastseconds = seconds;

			float p2 = LuaHook_Commands::ccGetGroupBattleEnemyLife("GP_CHAR_ID_2FOU");
			float p3 = LuaHook_Commands::ccGetGroupBattleEnemyLife("GP_CHAR_ID_2SKR");
			float p4 = LuaHook_Commands::ccGetGroupBattleEnemyLife("GP_CHAR_ID_2DDR");

			//cout << p2 << " / " << p3 << " / " << p4 << endl;

			string p2str = "+P2 - HP: " + FloatToString(p2) + "% / CKR: " + FloatToString(100) + "%";
			string p3str = "+P3 - HP: " + FloatToString(p3) + "% / CKR: " + FloatToString(100) + "%";
			string p4str = "+<color red>P4</color> - HP: " + FloatToString(p4) + "% / CKR: " + FloatToString(100) + "%";

			LuaHook_Commands::ccEntryNameTelop((char*)p2str.c_str(), "", 570, -500, 0, 0, 10);
			LuaHook_Commands::ccEntryNameTelop((char*)p3str.c_str(), "", -570, 500, 0, 0, 10);
			LuaHook_Commands::ccEntryNameTelop((char*)p4str.c_str(), "", 570, 500, 0, 0, 10);
		}
	}

	return 0;
}

/*
int MultiMatch::ccMultiMatchCameraLoop()
{
	int playerCount = ccCharacterFunctions::charPointer.size();

	float px = 0;
	float pz = 0;
	float py = 0;
	float pa = 0.8f;

	vector<float> positions;

	for (int a = 0; a < playerCount; a++)
	{
		float act_x = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float act_z = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float act_y = *(float*)(ccCharacterFunctions::charPointer[a] + 0x78);

		px = px + act_x;
		pz = pz + act_z;
		py = py + act_y;
	}

	px = px / playerCount;
	pz = pz / playerCount;
	py = py / playerCount;

	float maxDistCenter = 0;
	float maxDistCenterPoint[3] = { 0, 0, 0 };

	for (int a = 0; a < playerCount; a++)
	{
		float act_x = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float act_z = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float act_y = *(float*)(ccCharacterFunctions::charPointer[a] + 0x78);

		float actual = sqrt(
			pow(act_x, 2) +
			pow(act_z, 2) +
			pow(act_y, 2)
		);

		if (actual > maxDistCenter)
		{
			maxDistCenter = actual;
			maxDistCenterPoint[0] = act_x;
			maxDistCenterPoint[1] = act_z;
			maxDistCenterPoint[2] = act_y;
		};
	}

	float maxDistPlayer = 0;
	float maxDistPlayerPoint[3] = { 0, 0, 0 };

	for (int a = 0; a < playerCount; a++)
	{
		float act_x = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float act_z = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float act_y = *(float*)(ccCharacterFunctions::charPointer[a] + 0x78);

		float actual = sqrt(
			pow(act_x - maxDistCenterPoint[0], 2) +
			pow(act_z - maxDistCenterPoint[1], 2) +
			pow(act_y - maxDistCenterPoint[2], 2)
		);

		if (actual > maxDistPlayer)
		{
			maxDistPlayer = actual;
			maxDistPlayerPoint[0] = act_x;
			maxDistPlayerPoint[1] = act_z;
			maxDistPlayerPoint[2] = act_y;
		};
	}

	// Get furthest to center x, get furthest x to it
	float x_p0 = 0;
	float x_p0_dc = 0;
	int x_p0_n = -1;
	for (int a = 0; a < playerCount; a++)
	{
		float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
		float dst = DistanceCoord(act, 0);

		if (dst > x_p0_dc)
		{
			x_p0_dc = dst;
			x_p0 = act;
			x_p0_n = a;
		}
	}
	float x_p1 = 0;
	float x_p1_dp0 = 0;
	for (int a = 0; a < playerCount; a++)
	{
		if (a != x_p0_n)
		{
			float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x70);
			float dst = DistanceCoord(act, x_p0);

			if (dst > x_p1_dp0)
			{
				x_p1_dp0 = dst;
				x_p1 = act;
			}
		}
	}

	// Get furthest to center z, get furthest z to it
	float z_p0 = 0;
	float z_p0_dc = 0;
	int z_p0_n = -1;
	for (int a = 0; a < playerCount; a++)
	{
		float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
		float dst = DistanceCoord(act, 0);

		if (dst > z_p0_dc)
		{
			z_p0_dc = dst;
			z_p0 = act;
			z_p0_n = a;
		}
	}
	float z_p1 = 0;
	float z_p1_dp0 = 0;
	for (int a = 0; a < playerCount; a++)
	{
		if (a != z_p0_n)
		{
			float act = *(float*)(ccCharacterFunctions::charPointer[a] + 0x74);
			float dst = DistanceCoord(act, z_p0);

			if (dst > z_p1_dp0)
			{
				z_p1_dp0 = dst;
				z_p1 = act;
			}
		}
	}

	float px_m = (x_p0 + x_p1) / 2;
	float pz_m = (z_p0 + z_p1) / 2;

	float dist = 1000 + (maxDistPlayer * 2);
	LuaHook::ccGroupBattleEventCameraMovePosBegin(px_m, pz_m - (400 + (dist * 2)), dist, pa);
	LuaHook::ccGroupBattleEventCameraMoveLookBegin(px_m, pz_m, 100, pa);

	return 0;
}*/

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

typedef __int64(__fastcall * GetGpPtr)();
GetGpPtr g_GetGpPtr;
__int64 MultiMatch::fc_GetGpPtr()
{
	g_GetGpPtr = (GetGpPtr)(d3dcompiler_47_og::moduleBase + 0x44FC68);
	__int64 result = g_GetGpPtr();

	return result;
}