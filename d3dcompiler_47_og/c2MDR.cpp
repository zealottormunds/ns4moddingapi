#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ccPlayer.h"
#include "c2MDR.h"

using namespace moddingApi;
using namespace std;

c2MDR::c2MDR(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);
}

void c2MDR::Loop(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);
}
