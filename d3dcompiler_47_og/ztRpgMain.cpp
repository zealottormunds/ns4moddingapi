#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <DirectXMath.h>
#include <math.h>

#include "ztRpgMain.h"
#include "d3dcompiler_47_og.h"
#include "Scene.h"

using namespace std;
using namespace moddingApi;

string FloatToString_(float f)
{
	string a = "";

	if (f > 99)
	{
		a = to_string(f).substr(0, 3);
	}
	else if (f > 9)
	{
		a = to_string(f).substr(0, 2);
	}
	else
	{
		a = to_string(f).substr(0, 1);
	}

	return a;
}

int rpg();
bool xd = false;
int ztRpgMain::rpg_test(__int64 a1)
{
	__int64 ptr = a1;
	return rpg();
}

int rpg()
{
	if (Scene::init == false)
	{
		Scene::actualScene = 1;
		Scene::LoadSceneFiles();
	}

	if (Scene::actualScene != -1)
	{
		Scene::Update();
	}

	Sleep(1);

	return 0;
}