#pragma warning( disable: 4307 )
#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
#pragma region Standard Imports
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
#pragma endregion
#pragma region Character Imports
#include "c1CMN.h"
#pragma endregion

using namespace std;
using namespace moddingApi;

int prevFrame = 0;
int prevBattle = 0;

void ccPlayer::Start()
{
	// Currently this function does nothing.
}

// This function is ran every frame all the time. 
void ccPlayer::Loop()
{
	// Get keyboard keys and update their state. This is useful for using keyboard hooks, like pressing a key to do a certain function.
	Input::UpdateKeys();

	// If the state of isOnBattle is different, then it means we entered/quitted a battle
	if (ccGameProperties::isOnBattle() != prevBattle)
	{
		prevBattle = ccGameProperties::isOnBattle();
		if (prevBattle == 0)
		{
			// Code for when we quit a battle
			for (int x = 0; x < 2; x++)
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
			for (int x = 0; x < 2; x++)
			{
				uintptr_t s = GetPlayerStatus(x);
				uintptr_t p = GetPlayerInfo(x);

				if (s != 0 && p != 0)
				{
					int charaid = GetPlayerIntProperty(p, s, "characode");
					InitializeCharacter(charaid, x);
				}
			}
		}
	}

	// If we're not in a battle, stop the code
	if (ccGameProperties::isOnBattle() == 0) return;

	// This is the loop code for every player.
	for (int x = 0; x < 2; x++)
	{
		// Get player x info
		uintptr_t s = GetPlayerStatus(x);
		uintptr_t p = GetPlayerInfo(x);

		// Get enemy info
		uintptr_t es = GetPlayerStatus(1 - x);
		uintptr_t ep = GetPlayerInfo(1 - x);

		// If pointers are null, stop the function.
		if (s == 0 || p == 0) return;

		// If pointers aren't null, let's check the health of the current player.
		float h = GetPlayerFloatProperty(p, s, "health");
		if (h <= 0) return; // If the health is 0 or less than 0, stop the code.

		// This disables armor break
		if (GetPlayerFloatProperty(p, s, "armorbreak") < 45) { SetPlayerFloatProperty(p, s, "armorbreak", 45); }

		// Custom player code in here
		if (ccGameProperties::isOnMenu() == false && prevFrame != ccGeneralGameFunctions::GetCurrentFrame()) DoCharacterLoop(GetPlayerIntProperty(p, s, "characode"), x);
	}
	// Get next frame
	prevFrame = ccGeneralGameFunctions::GetCurrentFrame();
}

uintptr_t ccPlayer::plMain[6] = { 0, 0, 0, 0, 0, 0 };
int ccPlayer::plMainId[6] = { 0, 0, 0, 0, 0, 0 };

#pragma region General Functions
vector<uintptr_t> ccPlayer::memcpy_verify(vector<uintptr_t> ptrs, vector<uintptr_t> offsets, size_t size) {
	// Validate that the proper data is being passed to the function
	if (!ptrs.empty() && !offsets.empty() && ptrs.size() == offsets.size() && size > 0) {
		uintptr_t off = 0; // Temporary offset variable to add to non-beginning offset values

		// Loop through the pointer list
		for (int i = 0; i < int(ptrs.size()); i++) {
			if (off == 0) memcpy(&ptrs[i], (void*)offsets[i], size); // memcpy on the first pointer
			else memcpy(&ptrs[i], (void*)(off + offsets[i]), size); // memcpy on the non-beginning pointers

			if (ptrs[i] == 0) break; // Stop any operations when a pointer is 0
			off = ptrs[i]; // If everything looks good, set the temporary offset var to the currently copied pointer.
		}
		return ptrs; // Return the resulting pointer list
	}
	else {
		return vector<uintptr_t>(ptrs.size(), 0); // If there's an error, return a list of 0 pointers
	}
}
int ccPlayer::LoopForNum(int loopAmt, uintptr_t compare, uintptr_t (*f)(int)) {
	int n = -1;
	for (int x = 0; x < loopAmt; x++)
	{
		if (compare == f(x)) n = x;
	}
	return n;
}
constexpr unsigned int ccPlayer::str2int(const char* str, int h = 0) { return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h]; }
#pragma endregion

#pragma region GetPlayer Functions
uintptr_t ccPlayer::GetPlayerStatus(int n)
{
	// Initialize pointers and the core offset
	uintptr_t p1 = 0, p2 = 0, p3 = 0, p4 = 0;
	uintptr_t mb_offset = d3dcompiler_47_og::moduleBase - 0xC00 + 0x161B738;
	vector<uintptr_t> ptrs, offsets;

	// Depending on whether "n" is set to 1 or not will change which offsets we use
	switch (n)
	{
		case 1: offsets = { mb_offset, 0x20, 0xA0 }; break;
		default: offsets = { mb_offset, 0x20, 0x00 }; break;
	}
	// Execute memory copy/verification functionalities
	ptrs = memcpy_verify({ p1, p2, p3 }, offsets, 8);
	p1 = ptrs[0], p2 = ptrs[1], p3 = ptrs[2];
	if (p1 == 0 || p2 == 0 || p3 == 0) return 0;

	// If the memory pointers all copied properly, return the resulting pointer offset by 0x38, if valid
	p4 = p3 + 0x38;
	return !(p4 == 0) ? p4 : 0;
}

uintptr_t ccPlayer::GetPlayerInfo(int n)
{
	uintptr_t a = ccPlayer::GetPlayerStatus(n);
	if (a == 0) return 0;
	uintptr_t b = a - 8;
	uintptr_t c = 0;
	memcpy(&c, (void*)b, 8);
	return c;
}

int ccPlayer::GetPlayerStatusNumber(uintptr_t s) { return LoopForNum(2, s, ccPlayer::GetPlayerStatus); }
int ccPlayer::GetPlayerInfoNumber(uintptr_t p) { return LoopForNum(2, p, ccPlayer::GetPlayerInfo); }



// The function below gets a float pointer from the player.
float* ccPlayer::GetPlayerFloatPointer(uintptr_t p, uintptr_t s, char* prop)
{
	float* result;

	if (s == 0 || p == 0) return 0;

	switch (ccGameProperties::str2int(prop))
	{
		case ccPlayer::str2int("posx"): result = (float*)(p + 0x70); break;
		case ccPlayer::str2int("posz"): result = (float*)(p + 0x74); break;
		case ccPlayer::str2int("posy"): result = (float*)(p + 0x78); break;
		case ccPlayer::str2int("health"): result = (float*)(s + 0x00); break;
		case ccPlayer::str2int("maxhealth"): result = (float*)(s + 0x04); break;
		case ccPlayer::str2int("chakra"): result = (float*)(s + 0x08); break;
		case ccPlayer::str2int("maxchakra"): result = (float*)(s + 0x0C); break;
		case ccPlayer::str2int("sub"): result = (float*)(s + 0x10); break;
		case ccPlayer::str2int("maxsub"): result = (float*)(s + 0x10); break;
		case ccPlayer::str2int("armorbreak"): result = (float*)(s + 0x20); break;
		case ccPlayer::str2int("modelscale"): result = (float*)(p + 0x200); break;
		case ccPlayer::str2int("anmspeed"): result = (float*)(p + 0x210); break;
		case ccPlayer::str2int("movespeed"): result = (float*)(p + 0x14174); break;
		case ccPlayer::str2int("armor"): result = (float*)(p + 0x14A60); break;
	}

	return result;
}

float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop)
{
	float* ptr = GetPlayerFloatPointer(p, s, prop);

	if (ptr == 0) return 0;

	return *ptr;
}

int* ccPlayer::GetPlayerIntPointer(uintptr_t p, uintptr_t s, char* prop)
{
	int* val;

	switch (ccPlayer::str2int(prop))
	{
		case ccPlayer::str2int("characode"): val = (int*)(p + 0xC8C); break;
		case ccPlayer::str2int("enablechar"): val = (int*)(p + 0xCA8); break;
		case ccPlayer::str2int("cancontrol"): val = (int*)(p + 0xCAC); break;
		case ccPlayer::str2int("enableanm"): val = (int*)(p + 0xCB0); break;
		case ccPlayer::str2int("displaymdl"): val = (int*)(p + 0xCB8); break;
		case ccPlayer::str2int("atkid"): val = (int*)(p + 0xCC0); break;
		case ccPlayer::str2int("prevatkid"): val = (int*)(p + 0xCC4); break;
	}

	return val;
}

int ccPlayer::GetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop)
{
	int* val = GetPlayerIntPointer(p, s, prop);
	return *val;
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
	return Vector3::Distance(GetPlayerPosition(p, s), GetPlayerPosition(ep, es));
}
#pragma endregion

#pragma region SetPlayer Functions
// The function below sets a float property from the player to a specific value
void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value)
{
	float* ptr = GetPlayerFloatPointer(p, s, prop);

	if (ptr == 0) return;

	*ptr = value;
}

void ccPlayer::SetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop, int value)
{
	int* val = GetPlayerIntPointer(p, s, prop);
	*val = value;
}
#pragma endregion

#pragma region Character Functions
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

#pragma endregion
