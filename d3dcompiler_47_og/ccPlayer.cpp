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
#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)

using namespace std;
using namespace moddingApi;

int prevFrame = 0;
int prevBattle = 0;

void ccPlayer::Loop()
{
	// Separately loop between both players
	for (int x = 0; x < 2; x++)
	{
		// Get the status of the currently selected player
		uintptr_t s = GetPlayerStatus(x);
		uintptr_t p = GetPlayerInfo(x);

		// If the player status or info is invalid, stop executing functions for this loop iteration
		if (s == 0 || p == 0) return;

		// Get the HP value of the currently selected player
		float h = GetPlayerFloatProperty(p, s, "health");
		if (h <= 0) return;

		// Get the Chakra value of the currently selected player
		float c = GetPlayerFloatProperty(p, s, "chakra");
		SetPlayerFloatProperty(p, s, "modelscale", c / 100);
	}

	/*
		if (isOnBattle() != prevBattle)
		{
			prevBattle = isOnBattle();
			if (prevBattle == 0)
			{
				cout << "Quit battle" << endl;

				for (int x = 0; x < 2; x++)
				{
					DWORD s = GetPlayerStatus(x);
					if (GetPlayerHealth(s) <= 0) return; // If player is dead or there's no player, stop code
					DWORD p = GetPlayerInfo(x);
					if (p == 0) return;
					int charaid = GetCharaID(p);

					DeleteCharacters(charaid, x);
				}
			}
			else
			{
				cout << "Entered battle" << endl;

				for (int x = 0; x < 2; x++)
				{
					DWORD s = GetPlayerStatus(x);
					if (GetPlayerHealth(s) <= 0) return; // If player is dead or there's no player, stop code
					DWORD p = GetPlayerInfo(x);
					if (p == 0) return;
					int charaid = GetCharaID(p);
					InitializeCharacters(charaid, x);
				}
			}
		}

		if (isOnBattle() == 0) return;

		for (int x = 0; x < 2; x++)
		{
			DWORD s = GetPlayerStatus(x);

			if (GetPlayerHealth(s) <= 0) return; // If player is dead or there's no player, stop code

			DWORD p = GetPlayerInfo(x);
			cout << "p: " << hex << p << endl;

			if (p == 0) return;

			// Character specific
			//if (isOnMenu() == false && prevFrame != GetCurrentFrame()) DoCharacterLoop(GetCharaID(p), x);
		}
		prevFrame = GetCurrentFrame();
	*/
}

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

float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop)
{
	// Instantiate variables for memcpy and the return value
	float result = -1;
	int offset = -1;
	uintptr_t ptr = 0;

	// If either pointer is invalid, return -1
	if (s == 0 || p == 0) return result;

	switch (ccPlayer::str2int(prop))
	{
		case ccPlayer::str2int("posx"): offset = 0x70; ptr = p; break;
		case ccPlayer::str2int("posz"): offset = 0x74; ptr = p; break;
		case ccPlayer::str2int("posy"): offset = 0x78; ptr = p; break;
		case ccPlayer::str2int("health"): offset = 0x00; ptr = s; break;
		case ccPlayer::str2int("maxhealth"): offset = 0x04; ptr = s; break;
		case ccPlayer::str2int("chakra"): offset = 0x08; ptr = s; break;
		case ccPlayer::str2int("maxchakra"): offset = 0x0C; ptr = s; break;
		case ccPlayer::str2int("sub"): offset = 0x10; ptr = s; break;
		case ccPlayer::str2int("maxsub"): offset = 0x14; ptr = s; break;
		case ccPlayer::str2int("modelscale"): offset = 0x200; ptr = p; break;
		case ccPlayer::str2int("anmspeed"): offset = 0x214; ptr = p; break;
		case ccPlayer::str2int("movespeed"): offset = 0x14174; ptr = p; break;
	}

	// If a case from above is fulfilled, copy the corresponding value of ptr + offset from memory and return it
	if(offset != -1 && ptr != 0) memcpy(&result, (void*)(ptr + offset), 4);
	return result;
}
#pragma endregion

#pragma region SetPlayer Functions
void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value)
{
	uintptr_t ptr = 0;

	if (s == 0 || p == 0) return;

	switch (ccPlayer::str2int(prop))
	{
		case ccPlayer::str2int("posx"): ptr = p + 0x70; break;
		case ccPlayer::str2int("posz"): ptr = p + 0x74; break;
		case ccPlayer::str2int("posy"): ptr = p + 0x78; break;
		case ccPlayer::str2int("health"): ptr = s + 0x00; break;
		case ccPlayer::str2int("maxhealth"): ptr = s + 0x04; break;
		case ccPlayer::str2int("chakra"): ptr = s + 0x08; break;
		case ccPlayer::str2int("maxchakra"): ptr = s + 0x0C; break;
		case ccPlayer::str2int("sub"): ptr = s + 0x10; break;
		case ccPlayer::str2int("maxsub"): ptr = s + 0x14; break;
		case ccPlayer::str2int("modelscale"): ptr = p + 0x200; break;
		case ccPlayer::str2int("anmspeed"): ptr = p + 0x214; break;
		case ccPlayer::str2int("movespeed"): ptr = p + 0x14174; break;
	}

	DWORD dwOld = 0;
	VirtualProtect((void*)(ptr), 4, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(ptr), &value, 4);
	VirtualProtect((void*)(ptr), 4, dwOld, &dwOld);
}
#pragma endregion
