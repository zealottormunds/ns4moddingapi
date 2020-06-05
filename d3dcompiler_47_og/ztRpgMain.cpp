#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <DirectXMath.h>
#include <math.h>

#include "ztRpgMain.h"
#include "LuaHook.h"
#include "d3dcompiler_47_og.h"
#include "ccMain.h"
#include "ccGeneralGameFunctions.h"
#include "MultiMatch.h"
#include "Transform.h"
#include "GameObject.h"
#include "WorldCollision.h"
#include "LuaHook_Commands.h"

#include "Input.h"
#include "Scene.h"

using namespace std;
using namespace moddingApi;

// Converts a float string to float
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

int DoCustomMode();

// Lua function to loop the API game engine
int ztRpgMain::rpg_test(__int64 a1)
{
	__int64 ptr = a1;
	return DoCustomMode();
}

// Starts the custom game engine
int DoCustomMode()
{
	// If the engine isn't initialized, load a scene
	if (Scene::init == false)
	{
		// Initialize values
		Scene::Init();

		// Load a scene 
		Scene::LoadScene(4);
	}
	
	// If the scene is loaded, update it
	if (Scene::actualScene != -1)
	{
		Scene::Update();
	}
	
	// Wait for next script execution
	Sleep(1);
	
	return 0;
}