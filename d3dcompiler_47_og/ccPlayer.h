#ifndef CCPLAYER_H 
#define CCPLAYER_H
#pragma once

#include <stdio.h>
#include "Vector3.h"

namespace moddingApi
{
	class ccPlayer
	{
	public:
		static uintptr_t plMain[6];
		static int plMainId[6];
		static void ccPlayer::Start();
		static void ccPlayer::Loop();

		static void ccPlayer::InitializeCharacter(int c, int plNum);
		static void ccPlayer::DeleteCharacter(int c, int plNum);
		static void ccPlayer::DoCharacterLoop(int c, int plNum);

		static uintptr_t ccPlayer::GetPlayerStatus(int n);
		static uintptr_t ccPlayer::GetPlayerInfo(int n);
		static int ccPlayer::GetPlayerStatusNumber(uintptr_t s);
		static int ccPlayer::GetPlayerInfoNumber(uintptr_t s);

		static int* ccPlayer::GetPlayerIntPointer(uintptr_t p, uintptr_t s, char* prop);
		static int ccPlayer::GetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop);
		static void ccPlayer::SetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop, int value);

		static float* ccPlayer::GetPlayerFloatPointer(uintptr_t p, uintptr_t s, char* prop);
		static float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop);
		static void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value);

		static Vector3 ccPlayer::GetPlayerPosition(uintptr_t p, uintptr_t s);
		static float ccPlayer::GetPlayerDistance(uintptr_t p, uintptr_t s, uintptr_t ep, uintptr_t es);

		static __int64 __fastcall meTest(__int64 a1, __int64 a2);
	};
}

#endif