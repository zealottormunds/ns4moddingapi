#pragma once

#include <stdio.h>
#include <windows.h>
#include "Vector3.h"
#include "ccBattleInputs.h"

using namespace std;

namespace moddingApi
{
	class ccPlayer
	{
	public:
		static uintptr_t plMain[6];
		static int plMainId[6];
		// static vector<string> matchup;
		static void ccPlayer::Start();
		static void ccPlayer::Loop();

		static void ccPlayer::InitializeCharacter(int c, int plNum);
		static void ccPlayer::DeleteCharacter(int c, int plNum);
		static void ccPlayer::DoCharacterLoop(int c, int plNum);

		static void ccPlayer::GetGamepadState(int n, std::vector<bool> inputs);

		static uintptr_t ccPlayer::GetPlayerStatus(int n);
		static uintptr_t ccPlayer::GetPlayerInfo(int n);
		static uintptr_t ccPlayer::GetSystemInfo();
		static int ccPlayer::GetPlayerStatusNumber(uintptr_t s);
		static int ccPlayer::GetPlayerInfoNumber(uintptr_t s);

		static uintptr_t ccPlayer::GetStormPointer(int n);
		static float ccPlayer::GetStormGauge(int n);
		static void ccPlayer::SetStormGauge(int n, float value);
		static uintptr_t ccPlayer::GetMatchPointer();
		static int ccPlayer::GetMatchCount();
		static void ccPlayer::SetMatchCount(int value);

		static int* ccPlayer::GetPlayerIntPointer(uintptr_t p, uintptr_t s, char* prop);
		static int ccPlayer::GetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop);
		static void ccPlayer::SetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop, int value);
		static void ccPlayer::SetPlayerStatePropertyEasy(uintptr_t p, uintptr_t s, char* prop);
		static void ccPlayer::SetPlayerStateProperty(uintptr_t p, uintptr_t s, int prop);

		static float* ccPlayer::GetPlayerFloatPointer(uintptr_t p, uintptr_t s, char* prop);
		static float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop);
		static void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value);

		static Vector3 ccPlayer::GetPlayerPosition(uintptr_t p, uintptr_t s);
		static float ccPlayer::GetPlayerDistance(uintptr_t p, uintptr_t s, uintptr_t ep, uintptr_t es);

		static string ccPlayer::charcode2str(int charcode);
		static void ccPlayer::SetTimerValue(int timerValue, int maxTimer, bool value);

		// Placeholders, change order when functions are done
		static int ccPlayer::GetCanDoJutsuChakra(uintptr_t p, uintptr_t s);
		static int ccPlayer::GetAwakenedState(uintptr_t p, uintptr_t s);
	private:
		//int prevFrame = 0;
		//int prevBattle = 0;
		static vector<uintptr_t> ccPlayer::memcpy_verify(vector<uintptr_t> ptrs, vector<uintptr_t> offsets, size_t size);
		static int ccPlayer::LoopForNum(int loopAmt, uintptr_t compare, uintptr_t(*f)(int));
		static constexpr unsigned int ccPlayer::str2int(const char* str, int h);
	};
}