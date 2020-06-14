#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ccPlayer.h"
#include "c3MNT.h"

using namespace moddingApi;
using namespace std;

c3MNT::c3MNT(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);

	maxSub = 25;
	totalSub = 25;
	playerSpeed = 1.6;
	init = false;
	if (c.matchup[0] == "2mdr" || c.matchup[1] == "2mdr") hasMDR = true;
	else hasMDR = false;
}

void c3MNT::Loop(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);

	c.SetPlayerFloatProperty(p, s, "movespeed", playerSpeed);

	if (init == false)
	{
		c.SetPlayerFloatProperty(p, s, "maxsub", maxSub);
		c.SetPlayerFloatProperty(p, s, "sub", totalSub);
		init = true;
	}
	else
	{
		if (c.GetPlayerFloatProperty(p, s, "sub") < c.GetPlayerFloatProperty(p, s, "maxsub"))
		{
			c.SetPlayerFloatProperty(p, s, "maxsub", c.GetPlayerFloatProperty(p, s, "sub"));
		}

		/*
		if ((c.GetMaxSubState(s)) > maxSub)
		{
			c.SetMaxSubState(s, maxSub);
		}

		if ((c.GetSubState(s)) > totalSub)
		{
			c.SetSubState(s, totalSub);
		}
		else if (c.GetSubState(s) < totalSub)
		{
			totalSub = c.GetSubState(s);
		}
		*/
	}
	if (hasMDR) {
		c.SetPlayerFloatProperty(p, s, "maxsub", 0);
		c.SetPlayerFloatProperty(p, s, "sub", 0);
	}
}
