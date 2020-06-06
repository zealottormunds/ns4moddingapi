#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ccPlayer.h"
#include "c7SSK.h"

using namespace moddingApi;
using namespace std;

c7SSK::c7SSK(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);
}

void c7SSK::Loop(int pln)
{
	ccPlayer c;
	int en = 1;
	if (pln == 1) en = 0;

	uintptr_t p = c.GetPlayerInfo(pln);
	uintptr_t s = c.GetPlayerStatus(pln);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);
}
