#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "d3dcompiler_47_og.h"
#include "LuaUtilities.h"

using namespace std;
using namespace moddingApi;

int moddingApi::ccSetFade(int initialColor, int finalColor)
{
	typedef int(__fastcall * funct)(int a1, int a2);
	funct fc;
	fc = (funct)(d3dcompiler_47_og::moduleBase + 0x537470); // UPDATED
	return fc(initialColor, finalColor);
}

int moddingApi::ccLoadTitleUi()
{
	typedef int(__fastcall * funct)(int a1, int a2);
	funct fc;
	fc = (funct)(d3dcompiler_47_og::moduleBase + 0x535494); // UPDATED
	return fc(0, 0);
}

int moddingApi::ccOpenTitleUi()
{
	typedef int(__fastcall * funct)();
	funct fc;
	fc = (funct)(d3dcompiler_47_og::moduleBase + 0x4B9988); // UPDATED
	return fc();
}

int moddingApi::ccCloseTitleUi()
{
	typedef int(__fastcall * funct)();
	funct fc;
	fc = (funct)(d3dcompiler_47_og::moduleBase + 0x4B95FC); // UPDATED
	return fc();
}

int moddingApi::ccAdvPlaySound_2D(int sound)
{
	typedef int(__fastcall * funct)(int a);
	funct fc;
	fc = (funct)(d3dcompiler_47_og::moduleBase + 0x4DC7D0); // UPDATED
	return fc(sound);
}

int moddingApi::ccAdvYesNoSelectWindowOpen(char * title)
{
	typedef int(__fastcall * funct)(char* a);
	funct fc;
	fc = (funct)(d3dcompiler_47_og::moduleBase + 0x4DCE4C); // UPDATED
	return fc(title);
}

int moddingApi::ccAdvSelectWindowAddItem(char * item)
{
	typedef int(__fastcall * funct)(char* a);
	funct fc;
	fc = (funct)(d3dcompiler_47_og::moduleBase + 0x4DCA2C); // UPDATED
	return fc(item);
}
