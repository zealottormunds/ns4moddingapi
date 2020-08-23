#include "enet/enet.h"

#include <WinSock2.h>
#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "ccPlayer.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "ccGameProperties.h"
#include "Input.h"
#include "LuaHook.h"
#include "ccMemoryFunctions.h"
#include "ccPlayerStruct.h"
#include "Vector3.h"
#include "ccGeneralGameFunctions.h"
#include "LuaHook_Commands.h"

#pragma warning( disable: 4307 )

using namespace std;
using namespace moddingApi;

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
int prevFrame = 0;
int prevBattle = 0;

void ccPlayer::Start()
{
	// Currently this function does nothing.
}

__int64 __fastcall ccPlayer::meTest(__int64 a1)
{
	cout << "The function works! " << hex << a1 << endl;

	if (ccGameProperties::isOnBattle() == 1)
	{
		// Get player x info
		uintptr_t s = GetPlayerStatus(0);
		uintptr_t p = GetPlayerInfo(0);

		// If pointers are null, stop the function.
		if (s == 0 || p == 0)
		{
			cout << "Null pointers" << endl;
			return 1;
		}

		float h = GetPlayerFloatProperty(p, s, "health");
		SetPlayerFloatProperty(p, s, "health", h + 5);
		//SetPlayerFloatProperty(p, s, "modelscale", 0.5f);
	}
	else
	{
		cout << "Not on battle" << endl;
	}

	return 1;
}

// This function is ran every frame all the time.
void ccPlayer::Loop()
{
	// Get keyboard keys and update their state. This is useful for using keyboard hooks, like pressing a key to do a certain function.
	/*Input::UpdateKeys();

	if (Input::GetKeyDown('U'))
	{
		cout << std::hex << GetPlayerStatus(0) << endl;
	}*/

	// If the state of isOnBattle is different, then it means we entered/quitted a battle
	if (ccGameProperties::isOnBattle() != prevBattle)
	{
		prevBattle = ccGameProperties::isOnBattle();
		if (prevBattle == 0)
		{
			// Code for when we quit a battle
			for (int x = 0; x < 6; x++)
			{
				if (plMain[x] != 0)
				{
					DeleteCharacter(plMainId[x], x);
				}
			}
		}
		else
		{
			// Code for when we enter a battle
			for (int x = 0; x < 6; x++)
			{
				uintptr_t s = GetPlayerStatus(x);
				uintptr_t p = GetPlayerInfo(x);

				if (s != 0 && p != 0)
				{
					int charaid = GetPlayerIntProperty(p, s, "characode");
					InitializeCharacter(charaid, x);
					cout << "P: " << hex << p << endl;
					cout << "S: " << hex << s << endl;
				}
			}
		}
	}

	// If we're not in a battle, stop the code
	if (ccGameProperties::isOnBattle() == 0) return;

	// This is the loop code for every player.
	for (int x = 0; x < 6; x++)
	{
		// Get player x info
		uintptr_t s = GetPlayerStatus(x);
		uintptr_t p = GetPlayerInfo(x);

		// Get enemy info
		uintptr_t es = GetPlayerStatus(1 - x);
		uintptr_t ep = GetPlayerInfo(1 - x);

		// If pointers are null, stop the function.
		if (s == 0 || p == 0) return;

		float h = GetPlayerFloatProperty(p, s, "health"); // If pointers aren't null, let's check the health of the current player.

		if (h <= 0) return; // If the health is 0 or less than 0, stop the code.

		// This disables armor break
		if (GetPlayerFloatProperty(p, s, "armorbreak") < 45.0f)
		{
			SetPlayerFloatProperty(p, s, "armorbreak", 45.0f);
		}

		//SetPlayerFloatProperty(p, s, "modelscale", GetPlayerFloatProperty(p, s, "chakra") / 100);

		// Custom player code in here
		if (ccGameProperties::isOnMenu() == false && prevFrame != ccGeneralGameFunctions::GetCurrentFrame()) DoCharacterLoop(GetPlayerIntProperty(p, s, "characode"), x);
	}
	// Get next frame
	prevFrame = ccGeneralGameFunctions::GetCurrentFrame();
}

uintptr_t ccPlayer::plMain[6] = { 0, 0, 0, 0, 0, 0};
int ccPlayer::plMainId[6] = { 0, 0, 0, 0, 0, 0 };

void ccPlayer::InitializeCharacter(int c, int plNum)
{
	uintptr_t plm = 0;
	switch (c)
	{
	/*case 0x19:
	{
		ccPlayerMain_2ITC *c_2itc = (new ccPlayerMain_2ITC(plNum));
		plm = (DWORD)(c_2itc);
		plMain[plNum] = plm;
		break;
	}*/
	}
	cout << "Created pl at " << hex << plm << "\n";
}

void ccPlayer::DeleteCharacter(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];
	switch (c)
	{
	/*case 0x19:
		delete &(*(ccPlayerMain_2ITC*)(plm));
		break;*/
	}
	cout << "Deleted pl at " << hex << plm << "\n";
	plMain[plNum] = 0;
}

void ccPlayer::DoCharacterLoop(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];
	switch (c)
	{
	case 0x19:
		//(*(ccPlayerMain_2ITC*)(plm)).Loop(plNum);
		break;
	}
}

// This function gets the player status (health, chakra, subs...)
uintptr_t ccPlayer::GetPlayerStatus(int n)
{
	uintptr_t *p1 = 0;
	uintptr_t *p2 = 0;
	uintptr_t *p3 = 0;
	uintptr_t *p4 = 0;
	p1 = (uintptr_t*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x16BDA20);
	if (*p1 == 0) return 0;
	p2 = (uintptr_t*)(*p1 + 0x20);
	if (*p2 == 0) return 0;

	switch (n)
	{
	default:
		p3 = (uintptr_t*)(*p2 + 0x00);
		if (*p3 == 0) return 0;
	case 1:
		p3 = (uintptr_t*)(*p2 + 0xA0);
		if (*p3 == 0) return 0;
	case 2:
		p3 = (uintptr_t*)(*p2 + 0x08);
		if (*p3 == 0) return 0;
	case 3:
		p3 = (uintptr_t*)(*p2 + 0x10);
		if (*p3 == 0) return 0;
	case 4:
		p3 = (uintptr_t*)(*p2 + 0x90);
		if (*p3 == 0) return 0;
	case 5:
		p3 = (uintptr_t*)(*p2 + 0x98);
		if (*p3 == 0) return 0;
	}

	p4 = (uintptr_t*)(*p3 + 0x38);
	if (*p4 == 0) return 0;

	return (uintptr_t)p4;
}

// This function gets the player info (world position, scale, speed...)
uintptr_t ccPlayer::GetPlayerInfo(int n)
{
	uintptr_t a = ccPlayer::GetPlayerStatus(n);
	if (a == 0) return 0;
	uintptr_t b = a - 8;
	uintptr_t c = 0;
	memcpy(&c, (void*)b, 8);
	return c;
}

// Given a player status pointer, get the corresponding player ID
int ccPlayer::GetPlayerStatusNumber(uintptr_t s)
{
	int n = -1;
	for (int x = 0; x < 6; x++)
	{
		if (s == ccPlayer::GetPlayerStatus(x)) n = x;
	}
	return n;
}

// Given a player info pointer, get the corresponding player ID
int ccPlayer::GetPlayerInfoNumber(uintptr_t p)
{
	int n = -1;
	for (int x = 0; x < 6; x++)
	{
		if (p == ccPlayer::GetPlayerInfo(x)) n = x;
	}
	return n;
}

// Function to use strings in a switch statement.
constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

int* ccPlayer::GetPlayerIntPointer(uintptr_t p, uintptr_t s, char* prop)
{
	int * val;

	switch (str2int(prop))
	{
	case str2int("characode"):
		val = (int*)(p + 0xC8C);
		break;
	case str2int("enablechar"):
		val = (int*)(p + 0xCA8);
		break;
	case str2int("cancontrol"):
		val = (int*)(p + 0xCAC);
		break;
	case str2int("enableanm"):
		val = (int*)(p + 0xCB0);
		break;
	case str2int("displaymdl"):
		val = (int*)(p + 0xCB8);
		break;
	case str2int("atkid"):
		val = (int*)(p + 0xCC0);
		break;
	case str2int("prevatkid"):
		val = (int*)(p + 0xCC4);
		break;
	}

	return val;
}

int ccPlayer::GetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop)
{
	int * val = GetPlayerIntPointer(p, s, prop);
	return *val;
}

void ccPlayer::SetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop, int value)
{
	int * val = GetPlayerIntPointer(p, s, prop);
	*val = value;
}

// The function below gets a float pointer from the player.
float * ccPlayer::GetPlayerFloatPointer(uintptr_t p, uintptr_t s, char* prop)
{
	float * result;

	if (s == 0 || p == 0) return 0;

	switch (ccGameProperties::str2int(prop))
	{
	case str2int("posx"):
		result = (float*)(p + 0x70);
		break;
	case str2int("posz"):
		result = (float*)(p + 0x74);
		break;
	case str2int("posy"):
		result = (float*)(p + 0x78);
		break;
	case str2int("health"):
		result = (float*)(s + 0x00);
		break;
	case str2int("maxhealth"):
		result = (float*)(s + 0x04);
		break;
	case str2int("chakra"):
		result = (float*)(s + 0x08);
		break;
	case str2int("maxchakra"):
		result = (float*)(s + 0x0C);
		break;
	case str2int("sub"):
		result = (float*)(s + 0x10);
		break;
	case str2int("maxsub"):
		result = (float*)(s + 0x14);
		break;
	case str2int("armorbreak"):
		result = (float*)(s + 0x20);
		break;
	case str2int("modelscale"):
		result = (float*)(p + 0x200);
		break;
	case str2int("anmspeed"):
		result = (float*)(p + 0x210);
		break;
	case str2int("movespeed"):
		result = (float*)(p + 0x14174);
		break;
	case str2int("armor"):
		result = (float*)(p + 0x14A60);
		break;
	}

	return result;
}

// Get a float property from the player
float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop)
{
	float *ptr = GetPlayerFloatPointer(p, s, prop);

	if (ptr == 0) return 0;

	return *ptr;
}

// The function below sets a float property from the player to a specific value
void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value)
{
	float *ptr = GetPlayerFloatPointer(p, s, prop);

	if (ptr == 0) return;

	*ptr = value;
}

// Gets the player position in a Vector3
Vector3 ccPlayer::GetPlayerPosition(uintptr_t p, uintptr_t s)
{
	return Vector3
	(
		GetPlayerFloatProperty(p, s, "posx"),
		GetPlayerFloatProperty(p, s, "posy"),
		GetPlayerFloatProperty(p, s, "posz")
	);
}

// Calculates the distance between two given players
float ccPlayer::GetPlayerDistance(uintptr_t p, uintptr_t s, uintptr_t ep, uintptr_t es)
{
	return 0;
	//return Vector3::Distance(GetPlayerPosition(p, s), GetPlayerPosition(ep, es));
}