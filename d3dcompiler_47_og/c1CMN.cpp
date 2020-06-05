#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ccPlayer.h"
#include "c1CMN.h"

using namespace moddingApi;
using namespace std;

c1CMN::c1CMN(int c)
{
}

void c1CMN::PreLoop(int pln)
{
	ccPlayer c;
	int en = GetPointers(c, pln, 1);
}
void c1CMN::PostLoop(int pln)
{
	ccPlayer c;
	int en = GetPointers(c, pln, 1);
}

int c1CMN::GetPointers(ccPlayer c, int pl, int en)
{
	if (pl == 1) en = 0;
	uintptr_t p = c.GetPlayerInfo(pl);
	uintptr_t s = c.GetPlayerStatus(pl);
	uintptr_t ep = c.GetPlayerInfo(en);
	uintptr_t es = c.GetPlayerStatus(en);

}