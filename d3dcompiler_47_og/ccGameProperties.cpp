#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ccGameProperties.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"

using namespace std;
using namespace moddingApi;

// GAME PROPERTIES

typedef int(__fastcall * initializegameproperties)(uintptr_t);
initializegameproperties InitGameProperties;
uintptr_t InitGameProperties_Address = 0x52FDE4;

BYTE OriginalGameProperties[15];
uintptr_t ccGameProperties::GlobalPointer = -1;

int GamePropertiesAPI(uintptr_t);

void ccGameProperties::DoGamePropertiesHook()
{
	memcpy(OriginalGameProperties, (void*)(d3dcompiler_47_og::moduleBase + InitGameProperties_Address), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + InitGameProperties_Address), (void*)GamePropertiesAPI, 15);
}

void UndoGamePropertiesHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + InitGameProperties_Address), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + InitGameProperties_Address), OriginalGameProperties, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + InitGameProperties_Address), 15, dwOld, &dwOld);
}

int GamePropertiesAPI(uintptr_t a1)
{
	ccGameProperties::GlobalPointer = a1;

	cout << "Global pointer = " << std::hex << ccGameProperties::GlobalPointer << endl;

	UndoGamePropertiesHook();
	InitGameProperties = (initializegameproperties)(d3dcompiler_47_og::moduleBase + InitGameProperties_Address);
	int a = InitGameProperties(a1);
	ccGameProperties::DoGamePropertiesHook();

	return a;
}

void ccGameProperties::ReloadProperties()
{
	if (ccGameProperties::GlobalPointer != -1)
	{
		//UndoGamePropertiesHook();
		
		cout << "Reloading properties..." << endl;
		InitGameProperties = (initializegameproperties)(d3dcompiler_47_og::moduleBase + InitGameProperties_Address);
		cout << "In process..." << endl;
		InitGameProperties(ccGameProperties::GlobalPointer);
		cout << "Properties reloaded successfully" << endl;
		//ccGameProperties::DoGamePropertiesHook();
	}
	else
	{
		cout << "Cannot reload properties" << endl;
	}
}

// GAME INITIALIZATION
typedef uintptr_t(__fastcall * initg)(uintptr_t);
initg InitGame;
uintptr_t InitGame_Address = 0x85175C;

BYTE OriginalInitFunction[14];
uintptr_t ccGameProperties::InitMemory = -1;

uintptr_t InitGameAPI(uintptr_t);

void ccGameProperties::DoInitHook()
{
	memcpy(OriginalInitFunction, (void*)(d3dcompiler_47_og::moduleBase + InitGame_Address), 14);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + InitGame_Address), (void*)InitGameAPI, 14);
}

void UndoInitHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + InitGame_Address), 14, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + InitGame_Address), OriginalInitFunction, 14);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + InitGame_Address), 14, dwOld, &dwOld);
}

uintptr_t InitGameAPI(uintptr_t a1)
{
	ccGameProperties::InitMemory = a1;

	cout << "Init memory = " << std::hex << a1 << endl;

	UndoInitHook();
	InitGame = (initg)(d3dcompiler_47_og::moduleBase + InitGame_Address);
	uintptr_t a = InitGame(a1);
	ccGameProperties::DoInitHook();

	return a;
}

void ccGameProperties::ReloadInit()
{
	if (ccGameProperties::InitMemory != -1)
	{
		UndoInitHook();
		InitGame = (initg)(d3dcompiler_47_og::moduleBase + InitGame_Address);
		InitGame(ccGameProperties::InitMemory);
		ccGameProperties::DoInitHook();
	}
	else
	{
		cout << "Cannot reload init" << endl;
	}
}

// SCENE LOADING STUFF
typedef uintptr_t(__fastcall * ccSceneAutoSaveCaution)(char*);
ccSceneAutoSaveCaution ccsceneautosavecaution;
uintptr_t ccsceneautosavecaution_address = 0x6E0620;

typedef uintptr_t(__fastcall * ccScene__)(char*);
ccScene__ ccscene__;
uintptr_t ccscene___address = 0x6E06C0;

BYTE originalAutoSave[20];

uintptr_t ccSceneAutoSaveCautionAPI(char* a1);

void ccGameProperties::DoAutoSaveHook()
{
	memcpy(originalAutoSave, (void*)(d3dcompiler_47_og::moduleBase + ccsceneautosavecaution_address), 20);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + ccsceneautosavecaution_address), (void*)ccSceneAutoSaveCautionAPI, 20);
}

void UndoAutoSaveHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + ccsceneautosavecaution_address), 20, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + ccsceneautosavecaution_address), originalAutoSave, 20);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + ccsceneautosavecaution_address), 20, dwOld, &dwOld);
}

uintptr_t ccSceneAutoSaveCautionAPI(char* a1)
{
	ccsceneautosavecaution = (ccSceneAutoSaveCaution)(d3dcompiler_47_og::moduleBase + ccsceneautosavecaution_address);
	ccscene__ = (ccScene__)(d3dcompiler_47_og::moduleBase + ccscene___address);

	cout << "ccScene = " << a1 << endl;

	UndoAutoSaveHook();
	uintptr_t ret = ccsceneautosavecaution(a1);
	//uintptr_t ret = ccscene__("ccSceneOpeningMovie");
	ccGameProperties::DoAutoSaveHook();

	return ret;
}

void ccGameProperties::ccLoadScene(std::string sceneName)
{
	if (sceneName == "ccSceneAutoSaveCaution")
	{
		cout << "Loading scene..." << endl;

		ccsceneautosavecaution = (ccSceneAutoSaveCaution)(d3dcompiler_47_og::moduleBase + ccsceneautosavecaution_address);
		ccsceneautosavecaution("ccSceneAutoSaveCaution");
	}
	else
	{
		cout << "Scene not found" << endl;
	}
}