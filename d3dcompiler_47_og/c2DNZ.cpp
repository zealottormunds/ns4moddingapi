#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ccPlayer.h"
#include "c2DNZ.h"

using namespace moddingApi;
using namespace std;

c2DNZ::c2DNZ(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);

	totalSub = 25;
	maxSub = 100;
	subsLeft = 10;
	init = false;
	prevState = -1;
	prevSub = c.GetPlayerFloatProperty(p, s, "maxsub");
}

void c2DNZ::Loop(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);


	if (init == false)
	{
		c.SetPlayerFloatProperty(p, s, "maxsub", maxSub);
		c.SetPlayerFloatProperty(p, s, "sub", totalSub);
		init = true;
	}
	else
	{
		if (c.GetPlayerFloatProperty(p, s, "maxsub") > maxSub)   c.SetPlayerFloatProperty(p, s, "maxsub", maxSub);
		if (c.GetPlayerFloatProperty(p, s, "maxsub") > totalSub) c.SetPlayerFloatProperty(p, s, "maxsub", maxSub);

		if (c.GetPlayerFloatProperty(p, s, "sub") < totalSub)
		{
			subsLeft = subsLeft - 1;
			if (subsLeft <= 0)
			{
				subsLeft = 0;
				totalSub = 0;
			}
			c.SetPlayerFloatProperty(p, s, "sub", totalSub);
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

		/*
		if ((c.GetSubState(s)) < prevSub)
		{
			totalSub = totalSub - 25;
			if (totalSub < 0) totalSub = 0;

			c.SetSubState(s, totalSub);
		}

		prevSub = c.GetSubState(s);
		*/
	}
}
