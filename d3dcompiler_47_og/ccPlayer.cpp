#pragma warning( disable: 4307 )
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

using namespace std;
using namespace moddingApi;

#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
int prevFrame = 0;
int prevBattle = 0;

void ccPlayer::Loop()
{
	for (int x = 0; x < 2; x++)
	{
		uintptr_t s = GetPlayerStatus(x);
		uintptr_t p = GetPlayerInfo(x);
		if (s == 0 || p == 0) return;
		float h = GetPlayerFloatProperty(p, s, "health");

		if (h <= 0) return;

		float c = GetPlayerFloatProperty(p, s, "chakra");
		SetPlayerFloatProperty(p, s, "modelscale", c / 100);
		/*if (GetPlayerFloatProperty(p, s, "health") > 50)
		{
			SetPlayerFloatProperty(p, s,)
		}*/
	}
	//cout << "p: " << hex << p << endl;

	/*if (isOnBattle() != prevBattle)
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
	prevFrame = GetCurrentFrame();*/
}

uintptr_t ccPlayer::GetPlayerStatus(int n)
{
	uintptr_t p1 = 0;
	uintptr_t p2 = 0;
	uintptr_t p3 = 0;
	uintptr_t p4 = 0;

	switch (n)
	{
	default:
		memcpy(&p1, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x161B738), 8);
		if (p1 == 0) return 0;

		memcpy(&p2, (void*)(p1 + 0x20), 8);
		if (p2 == 0) return 0;

		memcpy(&p3, (void*)(p2 + 0x00), 8);
		if (p3 == 0) return 0;

		p4 = p3 + 0x38;
		if (p4 == 0) return 0;

		return p4;
	case 1:
		memcpy(&p1, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x161B738), 8);
		if (p1 == 0) return 0;

		memcpy(&p2, (void*)(p1 + 0x20), 8);
		if (p2 == 0) return 0;

		memcpy(&p3, (void*)(p2 + 0xA0), 8);
		if (p3 == 0) return 0;

		p4 = p3 + 0x38;
		if (p4 == 0) return 0;
		return p4;
	}
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

int ccPlayer::GetPlayerStatusNumber(uintptr_t s)
{
	int n = -1;
	for (int x = 0; x < 2; x++)
	{
		if (s == ccPlayer::GetPlayerStatus(x)) n = x;
	}
	return n;
}

int ccPlayer::GetPlayerInfoNumber(uintptr_t p)
{
	int n = -1;
	for (int x = 0; x < 2; x++)
	{
		if (p == ccPlayer::GetPlayerInfo(x)) n = x;
	}
	return n;
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop)
{
	float result = -1;

	if (s == 0 || p == 0) return result;

	switch (str2int(prop))
	{
	case str2int("posx"):
		memcpy(&result, (void*)(p + 0x70), 4);
		break;
	case str2int("posz"):
		memcpy(&result, (void*)(p + 0x74), 4);
		break;
	case str2int("posy"):
		memcpy(&result, (void*)(p + 0x78), 4);
		break;
	case str2int("health"):
		memcpy(&result, (void*)(s + 0x00), 4);
		break;
	case str2int("maxhealth"):
		memcpy(&result, (void*)(s + 0x04), 4);
		break;
	case str2int("chakra"):
		memcpy(&result, (void*)(s + 0x08), 4);
		break;
	case str2int("maxchakra"):
		memcpy(&result, (void*)(s + 0x0C), 4);
		break;
	case str2int("sub"):
		memcpy(&result, (void*)(s + 0x10), 4);
		break;
	case str2int("maxsub"):
		memcpy(&result, (void*)(s + 0x14), 4);
		break;
	case str2int("modelscale"):
		memcpy(&result, (void*)(p + 0x200), 4);
		break;
	case str2int("anmspeed"):
		memcpy(&result, (void*)(p + 0x214), 4);
		break;
	case str2int("movespeed"):
		memcpy(&result, (void*)(p + 0x14174), 4);
		break;
	}

	return result;
}

void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value)
{
	uintptr_t ptr = 0;

	if (s == 0 || p == 0) return;

	switch (str2int(prop))
	{
	case str2int("posx"):
		ptr = p + 0x70;
		break;
	case str2int("posz"):
		ptr = p + 0x74;
		break;
	case str2int("posy"):
		ptr = p + 0x78;
		break;
	case str2int("health"):
		ptr = s + 0x00;
		break;
	case str2int("maxhealth"):
		ptr = s + 0x04;
		break;
	case str2int("chakra"):
		ptr = s + 0x08;
		break;
	case str2int("maxchakra"):
		ptr = s + 0x0C;
		break;
	case str2int("sub"):
		ptr = s + 0x10;
		break;
	case str2int("maxsub"):
		ptr = s + 0x14;
		break;
	case str2int("modelscale"):
		ptr = p + 0x200;
		break;
	case str2int("anmspeed"):
		ptr = p + 0x214;
		break;
	case str2int("movespeed"):
		ptr = p + 0x14174;
		break;
	}

	DWORD dwOld = 0;
	VirtualProtect((void*)(ptr), 4, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(ptr), &value, 4);
	VirtualProtect((void*)(ptr), 4, dwOld, &dwOld);
}