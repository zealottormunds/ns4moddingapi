#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ccPlayer.h"
#include "c2TOB.h"

using namespace moddingApi;
using namespace std;

c2TOB::c2TOB(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);

	maxSub = 125;
	totalSub = 125;
	init = false;
}

void c2TOB::Loop(int pln)
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
		c.SetMaxSubState(s, maxSub);
		c.SetSubState(s, totalSub);
		//c.SetPlayerMaxHealth(s, 30);
		c.SetPlayerHealth(s, 30);
		init = true;
		//cout << "Init 2TOB " << pln << endl;
	}
	else
	{
		/*if (c.GetSubState(s) < c.GetMaxSubState(s))
		{
			c.SetMaxSubState(s, c.GetSubState(s));
		}*/

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
			//c.SetMaxSubState(s, c.GetSubState(s));
			totalSub = c.GetSubState(s);
		}
	}
}
