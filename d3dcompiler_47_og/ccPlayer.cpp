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

// S1 Character IDs
#include "c1NRT.h"
//#include "ccPlayerMain_1SSK.h"
//#include "ccPlayerMain_1SKR.h"
//#include "ccPlayerMain_1ROC.h"
//#include "ccPlayerMain_1NEJ.h"
//#include "ccPlayerMain_1HNT.h"
//#include "ccPlayerMain_1GAR.h"
//#include "ccPlayerMain_1HKG.h"
//#include "ccPlayerMain_1KMM.h"
//#include "ccPlayerMain_1ZBZ.h"
//#include "ccPlayerMain_1HAK.h"
//#include "ccPlayerMain_1FIR.h"
//#include "ccPlayerMain_1SEC.h"
//#include "ccPlayerMain_1TEN.h"
//#include "ccPlayerMain_1INO.h"
//#include "ccPlayerMain_1SIK.h"
//#include "ccPlayerMain_1TYO.h"
//#include "ccPlayerMain_1KIB.h"
//#include "ccPlayerMain_1AKM.h"
//#include "ccPlayerMain_1SIN.h"
//#include "ccPlayerMain_1TMR.h"
//#include "ccPlayerMain_1KNK.h"
//#include "ccPlayerMain_1KRS.h"
//#include "ccPlayerMain_1KRN.h"
//#include "ccPlayerMain_1ANK.h"
//#include "ccPlayerMain_1SZN.h"
//#include "ccPlayerMain_1JRB.h"
//#include "ccPlayerMain_1KDM.h"
//#include "ccPlayerMain_1SKN.h"
//#include "ccPlayerMain_1TYY.h"
//
//// S2 - Gen Character IDs
//#include "ccPlayerMain_2NRT.h"
//#include "ccPlayerMain_2NRX.h"
//#include "ccPlayerMain_2SSK.h"
//#include "ccPlayerMain_2SSY.h"
//#include "ccPlayerMain_2SKR.h"
//#include "ccPlayerMain_2ROC.h"
//#include "ccPlayerMain_2NEJ.h"
//#include "ccPlayerMain_2TEN.h"
//#include "ccPlayerMain_2INO.h"
//#include "ccPlayerMain_2SIK.h"
//#include "ccPlayerMain_2TYO.h"
//#include "ccPlayerMain_2KIB.h"
//#include "ccPlayerMain_2SIN.h"
//#include "ccPlayerMain_2HNT.h"
//#include "ccPlayerMain_2GAR.h"
//#include "ccPlayerMain_2KNK.h"
//#include "ccPlayerMain_2TMR.h"
//#include "ccPlayerMain_2KKS.h"
//#include "ccPlayerMain_2GUY.h"
//#include "ccPlayerMain_2ASM.h"
//#include "ccPlayerMain_2JRY.h"
//#include "ccPlayerMain_2TND.h"
//#include "ccPlayerMain_2ORC.h"
//#include "ccPlayerMain_2KBT.h"
//#include "ccPlayerMain_2ITC.h"
//#include "ccPlayerMain_2KSM.h"
//#include "ccPlayerMain_2CYB.h"
//#include "ccPlayerMain_2SAI.h"
//#include "ccPlayerMain_2YMT.h"
//#include "ccPlayerMain_2SCO.h"
//#include "ccPlayerMain_2DDR.h"
//#include "ccPlayerMain_2HDN.h"
//#include "ccPlayerMain_2KZU.h"
//#include "ccPlayerMain_2SGT.h"
//#include "ccPlayerMain_2JUG.h"
//#include "ccPlayerMain_2KAR.h"
//#include "ccPlayerMain_2TOB.h"
//#include "ccPlayerMain_2KNN.h"
//#include "ccPlayerMain_2PEA.h"
//#include "ccPlayerMain_2KLB.h"
//#include "ccPlayerMain_2AKM.h"
//#include "ccPlayerMain_2KRS.h"
//#include "ccPlayerMain_2PAR.h"
//#include "ccPlayerMain_2KKG.h"
//#include "ccPlayerMain_2FOU.h"
//#include "ccPlayerMain_2NRG.h"
//#include "ccPlayerMain_2SSZ.h"
//#include "ccPlayerMain_2MDR.h"
//#include "ccPlayerMain_2DNZ.h"
//#include "ccPlayerMain_2RKG.h"
//#include "ccPlayerMain_2TKG.h"
//#include "ccPlayerMain_2MKG.h"
//#include "ccPlayerMain_2KKX.h"
//#include "ccPlayerMain_2OBT.h"
//#include "ccPlayerMain_2KBX.h"
//#include "ccPlayerMain_2SEE.h"
//#include "ccPlayerMain_2TJR.h"
//#include "ccPlayerMain_2AOX.h"
//#include "ccPlayerMain_2KRT.h"
//#include "ccPlayerMain_2AKT.h"
//#include "ccPlayerMain_2FUU.h"
//#include "ccPlayerMain_2TRN.h"
//#include "ccPlayerMain_2SCX.h"
//#include "ccPlayerMain_2SCS.h"
//#include "ccPlayerMain_2GAV.h"
//
//// S3 Character IDs
//#include "ccPlayerMain_3MDR.h"
//#include "ccPlayerMain_3DRI.h"
//#include "ccPlayerMain_3RUS.h"
//#include "ccPlayerMain_3TOB.h"
//#include "ccPlayerMain_3YGR.h"
//#include "ccPlayerMain_3UTK.h"
//#include "ccPlayerMain_3MFN.h"
//#include "ccPlayerMain_3HAN.h"
//#include "ccPlayerMain_3NYG.h"
//#include "ccPlayerMain_3WHO.h"
//#include "ccPlayerMain_3KLB.h"
//#include "ccPlayerMain_3HNZ.h"
//#include "ccPlayerMain_3NGT.h"
//#include "ccPlayerMain_3TYO.h"
//#include "ccPlayerMain_3NRT.h"
//#include "ccPlayerMain_3SSK.h"
//#include "ccPlayerMain_3GAR.h"
//#include "ccPlayerMain_3KKS.h"
//#include "ccPlayerMain_3KHM.h"
//#include "ccPlayerMain_3IRK.h"
//#include "ccPlayerMain_3KBT.h"
//#include "ccPlayerMain_3OBT.h"
//#include "ccPlayerMain_3KSN.h"
//#include "ccPlayerMain_3MNT.h"
//#include "ccPlayerMain_3HSM.h"
//#include "ccPlayerMain_3MDR_2.h"
//
//// Rev Character IDs
//#include "ccPlayerMain_4MKG.h"
//#include "ccPlayerMain_4MUU.h"
//#include "ccPlayerMain_4RKG.h"
//#include "ccPlayerMain_4KKG.h"
//#include "ccPlayerMain_DKCN.h"
//#include "ccPlayerMain_TNRT.h"
//#include "ccPlayerMain_4SSI.h"
//#include "ccPlayerMain_4NRT.h"
//#include "ccPlayerMain_4MNR.h"
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

		//if (x == 0) cout << hex << int(GetPlayerIntProperty(s, p, "characode")) << endl; Sleep(1000);
		//if (GetPlayerIntProperty(p, s, "attackid") == 151) { SetPlayerIntProperty(p, s, "attackid", 74); }

		// Get enemy info
		uintptr_t es = GetPlayerStatus(1 - x);
		uintptr_t ep = GetPlayerInfo(1 - x);


		// If pointers are null, stop the function.
		if (s == 0 || p == 0) return;

		// If pointers aren't null, let's check the health of the current player.
		float h = GetPlayerFloatProperty(p, s, "health");
		if (h <= 0) return; // If the health is 0 or less than 0, stop the code.

		// This disables armor break
		if (GetPlayerFloatProperty(p, s, "armor") < 45) { SetPlayerFloatProperty(p, s, "armor", 45); }

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
		case 2: offsets = { mb_offset, 0x20, 0x08 }; break;
		case 3: offsets = { mb_offset, 0x20, 0x10 }; break;
		case 4: offsets = { mb_offset, 0x20, 0x90 }; break;
		case 5: offsets = { mb_offset, 0x20, 0x98 }; break;
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
	return c + 0x70;
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
		case ccPlayer::str2int("posx"): result = (float*)(p + 0x00); break;
		case ccPlayer::str2int("posz"): result = (float*)(p + 0x04); break;
		case ccPlayer::str2int("posy"): result = (float*)(p + 0x08); break;
		case ccPlayer::str2int("health"): result = (float*)(s + 0x00); break;
		case ccPlayer::str2int("maxhealth"): result = (float*)(s + 0x04); break;
		case ccPlayer::str2int("chakra"): result = (float*)(s + 0x08); break;
		case ccPlayer::str2int("maxchakra"): result = (float*)(s + 0x0C); break;
		case ccPlayer::str2int("sub"): result = (float*)(s + 0x10); break;
		case ccPlayer::str2int("maxsub"): result = (float*)(s + 0x10); break;
		case ccPlayer::str2int("storm"): result = (float*)(s + 0x18); break;
		case ccPlayer::str2int("maxstorm"): result = (float*)(s + 0x1C); break;
		case ccPlayer::str2int("armor"): result = (float*)(s + 0x20); break;
		case ccPlayer::str2int("maxarmor"): result = (float*)(s + 0x24); break;
		case ccPlayer::str2int("uitem"): result = (float*)(s + 0x30); break;
		case ccPlayer::str2int("ditem"): result = (float*)(s + 0x34); break;
		case ccPlayer::str2int("litem"): result = (float*)(s + 0x38); break;
		case ccPlayer::str2int("ritem"): result = (float*)(s + 0x3C); break;
		case ccPlayer::str2int("gravity"): result = (float*)(p + 0xE8); break;
		case ccPlayer::str2int("zmomentum"): result = (float*)(p + 0xEC); break;
		case ccPlayer::str2int("modelscale"): result = (float*)(p + 0x190); break;
		case ccPlayer::str2int("anmspeed"): result = (float*)(p + 0x1A0); break;
		case ccPlayer::str2int("movespeed"): result = (float*)(p + 0x14104); break;
		case ccPlayer::str2int("guard"): result = (float*)(p + 0x149F0); break;
		case ccPlayer::str2int("maxguard"): result = (float*)(p + 0x149F4); break;
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
		case ccPlayer::str2int("characode"): val = (int*)(p + 0xC1C); break;
		case ccPlayer::str2int("enablechar"): val = (int*)(p + 0xC38); break;
		case ccPlayer::str2int("cancontrol"): val = (int*)(p + 0xC3C); break;
		case ccPlayer::str2int("enableanm"): val = (int*)(p + 0xC40); break;
		case ccPlayer::str2int("displaymdl"): val = (int*)(p + 0xC48); break;
		case ccPlayer::str2int("pstate"): val = (int*)(p + 0xC50); break;
		case ccPlayer::str2int("prevpstate"): val = (int*)(p + 0xC54); break;
		case ccPlayer::str2int("attackid"): val = (int*)(p + 0x1010); break;
		case ccPlayer::str2int("prevattackid"): val = (int*)(p + 0x1024); break;
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

	c1CMN* cmn = (new c1CMN(plNum));
	switch (c)
	{
		case 0x2E: c1NRT *c_1nrt = (new c1NRT(plNum)); plm = (DWORD)(c_1nrt); plMain[plNum] = plm; break;
	}
	std::cout << "Created pl at " << hex << plm << "\n";
}
void ccPlayer::DeleteCharacter(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];

	delete &(*(c1CMN*)(plm));
	switch (c)
	{
		case 0x2E: delete &(*(c1NRT*)(plm)); break;
	}
	std::cout << "Deleted pl at " << hex << plm << "\n";
	plMain[plNum] = 0;
}
void ccPlayer::DoCharacterLoop(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];

	(*(c1CMN*)(plm)).PreLoop(plNum);
	switch (c)
	{
		case 0x2E: (*(c1NRT*)(plm)).Loop(plNum); break;
	}
	(*(c1CMN*)(plm)).PostLoop(plNum);
}

#pragma endregion
