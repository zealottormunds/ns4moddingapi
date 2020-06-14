#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ccPlayer.h"
#include "ccBattleInputs.h"
#include "c2ITC.h"

using namespace moddingApi;
using namespace std;

c2ITC::c2ITC(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);

	chakraCharge = 0;

	// IA and CU1
	effectEnabled = false;
	originalMoveSpeed = -1;
	originalAnmSpeed = -1;
	prevEnemyHealth = -1;
	doneAwk = false;
	doneUj = false;
	frameCounterForUj = 0;
	removedLifeEffect = 0;
	framesToDoCU1 = 0;

	// Amaterasu
	framesToDoCD1 = 0;
	cd1_enableEffect = 0;
}

void c2ITC::Loop(int pln)
{
	ccPlayer c;
	ccBattleInputs inputs;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);

	ccPlayer c;

	bool actualButton = inputs.chakBtn;
	vector<float> actualAxis = inputs.leftStick;

	chakraCharge = c.GetCanDoJutsuChakra(p, s);

	if (framesToDoCU1 > 0)
	{
		// cout << "CU1: " << framesToDoCU1 << endl;
		framesToDoCU1--;
	}
	if (framesToDoCD1 > 0)
	{
		// cout << "CD1: " << framesToDoCD1 << endl;
		framesToDoCD1--;
	}

	if (chakraCharge && inputs.chakBtn)
	{
		if (actualAxis[1] ==  1) framesToDoCU1 = 30;
		if (actualAxis[1] == -1) framesToDoCD1 = 30;
	}

	int Count = c.GetMatchCount();
	if (c.GetPlayerIntProperty(ep, es, "pstate") == 0x77 && c.GetPlayerIntProperty(p, s, "attackid") == 0xCE)
	{
		if (Count > 0) c.SetMatchCount(Count - 10);
		if (Count <= 0) c.SetMatchCount(Count = 0x01);
	}
	/*
	if (actualButton == 0xA0 && actualAxis == 0x10)
	{
		cout << "cu1 10 frames" << endl;
		framesToDoCU1 = 30;
	}
	else if(framesToDoCU1 > 0) framesToDoCU1--;

	if (actualButton == 0xA0 && actualAxis == 0x20)
	{
		cout << "cd1 10 frames" << endl;
		framesToDoCD1 = 30;
	}
	else if (framesToDoCD1 > 0) framesToDoCD1--;
	*/

	////////////////////////////////////////////////////////////////////
	// Awakened bubble for tsukuyomi:
	////////////////////////////////////////////////////////////////////
	if (c.GetAwakenedState(p, s) == 1)
	{
		doneAwk = true;
		effectEnabled = true;
	}
	else
	{
		if (doneAwk == true) doneAwk = false;
		if (doneUj == false) effectEnabled = false;
	}

	if (cd1_enableEffect > 0) cd1_enableEffect - 1;

	if ((c.GetPlayerIntProperty(p, s, "pstate") == 0x89 && c.GetPlayerIntProperty(p, s, "prevpstate") == 0x88) ||
		(c.GetPlayerIntProperty(p, s, "pstate") == 0x40 && c.GetPlayerIntProperty(p, s, "prevpstate") == 0x4E))
	{
		if (framesToDoCU1 > 0)
		{
			doneUj = true; // check for UJ and then count 30 * 9 frames = 270 (that's what the uj lasts)
		}
		if (framesToDoCD1 > 0 && cd1_enableEffect == 0)
		{
			cd1_enableEffect = 15;
			c.SetPlayerFloatProperty(p, s, "health", c.GetPlayerFloatProperty(p, s, "health") - 30);
		}
	}

	/*
	if (doneUj)
	{
		if (frameCounterForUj < 270)
		{
			frameCounterForUj = frameCounterForUj + 1;
		}
		else
		{
			effectEnabled = true;
			cout << "Effect of tsukuyomi is enabled" << endl;
		}
	}
	*/

	if (effectEnabled)
	{
		playerSpeed = 1;
		float actualHealth = c.GetPlayerFloatProperty(p, s, "health");
		if (actualHealth <= 5) playerSpeed = playerSpeed - 0.7;
		else if (actualHealth <= 10) playerSpeed = playerSpeed - 0.60;
		else if (actualHealth <= 25) playerSpeed = playerSpeed - 0.45;
		else if (actualHealth <= 50) playerSpeed = playerSpeed - 0.25;
		c.SetPlayerFloatProperty(p, s, "movespeed", playerSpeed);

		if (originalMoveSpeed == -1) originalMoveSpeed = c.GetPlayerFloatProperty(ep, es, "movespeed");
		if (originalAnmSpeed == -1) originalAnmSpeed = c.GetPlayerFloatProperty(ep, es, "anmspeed");
		//effectEnabled = true;

		float distance = c.GetPlayerDistance(p, s, ep, es);
		float maxDist = 500;
		float minDist = 0;
		//int pCurrState = ccPlayer::GetCurrentState(p);

		//if (pCurrState == 0x50 || pCurrState == 0x51 || pCurrState == 0x89) maxDist = 0;
		//if (pCurrState == 0x50 || pCurrState == 0x51 || pCurrState == 0x89) c.SetPlayerMoveSpeed(ep, -1);
		//if (pCurrState == 0x50 || pCurrState == 0x51 || pCurrState == 0x89) c.SetPlayerAnmSpeed(ep, -1);

		if (distance <= maxDist &&
			prevEnemyHealth != -1 && prevEnemyHealth == c.GetPlayerFloatProperty(ep, es, "health") &&
			c.GetPlayerIntProperty(p, s, "pstate") != 0x50 && c.GetPlayerIntProperty(p, s, "pstate") != 0x51 &&
			c.GetPlayerIntProperty(p, s, "pstate") != 0x89 &&
			c.GetPlayerIntProperty(ep, es, "pstate") != 0x50 && c.GetPlayerIntProperty(ep, es, "pstate") != 0x70 &&
			c.GetPlayerIntProperty(ep, es, "pstate") != 0x77 && c.GetPlayerIntProperty(ep, es, "pstate") != 0x6e &&
			c.GetPlayerIntProperty(ep, es, "pstate") != 0x6b && c.GetPlayerIntProperty(ep, es, "pstate") != 0x89)
			//if (distance <= maxDist && prevEnemyHealth != -1 && prevEnemyHealth == c.GetPlayerHealth(es))
		{
			c.SetPlayerFloatProperty(ep, es, "movespeed", 0.125);
			c.SetPlayerFloatProperty(ep, es, "anmspeed", 0.125);
		}
		else
		{
			c.SetPlayerFloatProperty(ep, es, "movespeed", originalMoveSpeed);
			c.SetPlayerFloatProperty(ep, es, "anmspeed", originalAnmSpeed);
			originalMoveSpeed = -1;
			originalAnmSpeed = -1;
		}

		prevEnemyHealth = c.GetPlayerFloatProperty(ep, es, "health");

		float plHealth = c.GetPlayerFloatProperty(p, s, "health");
		if (plHealth > 1)
		{
			if (doneAwk == false) c.SetPlayerFloatProperty(p, s, "health", plHealth - 0.05);
			else c.SetPlayerFloatProperty(p, s, "health", plHealth - 0.1);
		}
	}
	else
	{
		if (c.GetPlayerFloatProperty(ep, es, "anmspeed") != 1 || c.GetPlayerFloatProperty(ep, es, "movespeed") != 1)
		{
			playerSpeed = 1;
			c.SetPlayerFloatProperty(p, s, "movespeed", 1);

			c.SetPlayerFloatProperty(ep, es, "movespeed", 1);
			c.SetPlayerFloatProperty(ep, es, "anmspeed", 1);
			originalMoveSpeed = -1;
			originalAnmSpeed = -1;
		}
	}

	//if(cd1_enableEffect) Amaterasu(pln, p, s, ep, es);
}
