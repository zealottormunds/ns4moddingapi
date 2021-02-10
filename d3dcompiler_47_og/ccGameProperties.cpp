#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ccGameProperties.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "LuaHook.h"

extern "C"
{
	#include "lua/src/lua.h"
	#include "lua/src/lualib.h"
	#include "lua/src/lauxlib.h"
}

using namespace std;
using namespace moddingApi;

int ccGameProperties::isOnMenu()
{
	int v = 0;
	memcpy(&v, (void*)(d3dcompiler_47_og::moduleBase + 0x16191A0 - 0xC00), 4);
	return v;
}

int ccGameProperties::isOnBattle()
{
	int v = 0;
	memcpy(&v, (void*)(d3dcompiler_47_og::moduleBase + 0x155F8E4 - 0xC00), 4);
	return v;
}

string ccGameProperties::GetActiveWindowTitle()
{
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	return wnd_title;
}

constexpr unsigned int ccGameProperties::str2int(const char* str, int h)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

int __fastcall ccGameProperties::lua_pcallk(void* a1, int a2, int a3, int a4)
{
	typedef int(__fastcall * fc_funct)(void* a1, int a2, int a3, int a4);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x9ACA50);
	return fc_cc_funct(a1, a2, a3, a4);
}

int __fastcall ccGameProperties::lua_getfield(void* a1, int idx, const char *k)
{
	typedef int(__fastcall * fc_funct)(void* a1, int idx, const char *k);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x9ACE70);
	return fc_cc_funct(a1, idx, k);
}

int __fastcall ccGameProperties::luaL_loadfile(void* a1, char* file)
{
	typedef int(__fastcall * fc_funct)(void* a1, char* file);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x9AE630);
	return fc_cc_funct(a1, file);
}

int __fastcall ccGameProperties::lua_gettop(void* a1)
{
	typedef int(__fastcall * fc_funct)(void* a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x9AC670);
	return fc_cc_funct(a1);
}

int __fastcall ccGameProperties::lua_call(void* a1, int a2, int a3)
{
	typedef int(__fastcall * fc_funct)(void* a1, int a2, int a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x9AC100);
	return fc_cc_funct(a1, a2, a3);
}

int __fastcall ccGameProperties::menugamefunction(__int64 a1)
{
	typedef int(__fastcall * fc_funct)(__int64 a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x66C8AC);
	return fc_cc_funct(a1);
}

// Open Lua libs
__int64 ccGameProperties::LState = 0;
__int64 ccGameProperties::LStateGame;
void ccGameProperties::ExecuteLuaInitial()
{
	ccGameProperties::GetLuaState();
	luaL_openlibs((lua_State*)ccGameProperties::LState);
}

void ccGameProperties::ExecuteLuaFunction(char* funct)
{
	//cout << funct << endl;
	luaL_dostring((lua_State*)ccGameProperties::LState, funct);
}

void ccGameProperties::ExecuteLuaFile(char* path)
{
	cout << path << endl;
	luaL_dofile((lua_State*)ccGameProperties::LState, path);
}

void* ccGameProperties::GetLuaState()
{
	uintptr_t p1 = 0;
	uintptr_t p2 = 0;
	uintptr_t p3 = 0;
	uintptr_t p4 = 0;
	uintptr_t p5 = 0;
	uintptr_t p6 = 0;
	uintptr_t p7 = 0;
	uintptr_t p8 = 0;

	memcpy(&p1, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x0161B830), 8);
	if (p1 == 0) return 0;

	memcpy(&p2, (void*)(p1 + 0x3A8), 8);
	if (p2 == 0) return 0;

	memcpy(&p3, (void*)(p2 + 0x100), 8);
	if (p3 == 0) return 0;

	memcpy(&p4, (void*)(p3 + 0x228), 8);
	if (p4 == 0) return 0;

	memcpy(&p5, (void*)(p4 + 0xFF8), 8);
	if (p5 == 0) return 0;

	p6 = p5 + 0x0;
	if (p6 == 0) return 0;

	cout << "Lua state: " << std::hex << p6 << endl;

	ccGameProperties::LStateGame = p6;

	return (void*)p6;
}

// Get game properties
int ccGameProperties::GetProperty(char* prop)
{
	int propvalue = -1;

	switch (str2int(prop))
	{
	case str2int("ResolutionX"):
		memcpy(&propvalue, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x1561108), 4);
		break;
	case str2int("ResolutionY"):
		memcpy(&propvalue, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x1561108 + 4), 4);
		break;
	}

	return propvalue;
}

float ccGameProperties::LastSavedTime = 0;
float ccGameProperties::ActualSavedTime = 0;

void ccGameProperties::UpdateTiming()
{
	if (ActualSavedTime == 0)
	{
		ActualSavedTime = GetCurrentGameTime();
	}
	else
	{
		LastSavedTime = ActualSavedTime;
		ActualSavedTime = GetCurrentGameTime();
	}
}

float ccGameProperties::GetCurrentGameTime()
{
	uintptr_t p1 = 0;
	uintptr_t p2 = 0;
	uintptr_t p3 = 0;
	uintptr_t p4 = 0;
	uintptr_t p5 = 0;
	uintptr_t p6 = 0;
	uintptr_t p7 = 0;
	uintptr_t p8 = 0;

	memcpy(&p1, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x0161B830), 8);
	if (p1 == 0) return 0;

	memcpy(&p2, (void*)(p1 + 0x3A8), 8);
	if (p2 == 0) return 0;

	memcpy(&p3, (void*)(p2 + 0x100), 8);
	if (p3 == 0) return 0;

	memcpy(&p4, (void*)(p3 + 0x228), 8);
	if (p4 == 0) return 0;

	memcpy(&p5, (void*)(p4 + 0xFF8), 8);
	if (p5 == 0) return 0;

	p6 = p5 + 0x0;
	if (p6 == 0) return 0;



	float test = 0;

	cout << "Trying to read time" << endl;
	memcpy(&test, (void*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x2965B3D64), 4);
	cout << "Finished reading time" << endl;

	return test;
}

float ccGameProperties::GetDeltaTime()
{
	return ActualSavedTime - LastSavedTime;
}

// Get a QWORD pointer from the game
__int64 ccGameProperties::GetQword(__int64 qw)
{
	__int64 qwr = qw - 0x140000C00;
	return *(__int64*)(d3dcompiler_47_og::moduleBase + qwr);
}

// Get a DWORD pointer from the game
int ccGameProperties::GetDword(__int64 dw)
{
	__int64 dwr = dw - 0x140000C00;
	return *(int*)(d3dcompiler_47_og::moduleBase + dwr);
}

// Get a OFFSET pointer from the game
__int64 ccGameProperties::GetOffset(__int64 of)
{
	__int64 ofr = of - 0xC00 + 0x1000;
	return (d3dcompiler_47_og::moduleBase + ofr);
}

// Game properties
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

__int64 ccGameProperties::loadCpk(__int64 a1)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x56ACE8);
	return fc_cc_funct(a1);
}

__int64 ccGameProperties::temp_malloc_00(size_t a1, char* str)
{
	typedef __int64(__fastcall * fc_funct)(size_t a1, char* str);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x9FFF00);
	return fc_cc_funct(a1, str);
}

__int64 ccGameProperties::spawnmenu(__int64 a1, char* str)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1, char* str);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A1BB0);
	return fc_cc_funct(a1, str);
}

int ccGameProperties::setupmenu(__int64 window, int **a2, char **options, int a4, int a5, int a6)
{
	typedef int(__fastcall * fc_funct)(__int64 window, int **a2, char **options, int a4, int a5, int a6);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A2AB4);
	return fc_cc_funct(window, a2, options, a4, a5, a6);
}

int ccGameProperties::setupmenusimple(__int64 a1, char* a2, int a3)
{
	typedef int(__fastcall * fc_funct)(__int64 a1, char* a2, int a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A391C);
	return fc_cc_funct(a1, a2, a3);
}

int ccGameProperties::setuptitle(__int64 w, char* title, int a3)
{
	typedef int(__fastcall * fc_funct)(__int64 w, char* title, int a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A364C);
	return fc_cc_funct(w, title, a3);
}

int ccGameProperties::funct1()
{
	typedef int(__fastcall * fc_funct)();
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A27A0);
	return fc_cc_funct();
}

int ccGameProperties::funct2(__int64 a1, __int64 a2)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1, __int64 a2);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A2164);
	return fc_cc_funct(a1, a2);
}

int ccGameProperties::funct3(__int64 a1)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A2A7C);
	return fc_cc_funct(a1);
}

int ccGameProperties::funct4(__int64 a1)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x6A2930);
	return fc_cc_funct(a1);
}

__int64 ccGameProperties::playanm(char* a1, char* a2)
{
	typedef int(__fastcall * fc_funct)(char* a1, char* a2);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x466D28);
	return fc_cc_funct(a1, a2);
}

__int64 ccGameProperties::playanm2(__int64 a1, char* a2, char* a3)
{
	typedef int(__fastcall * fc_funct)(__int64 a1, char* a2, char* a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x4CF7B8);
	return fc_cc_funct(a1, a2, a3);
}

__int64 ccGameProperties::playanm15(__int64 a1, __int64 a2, int a3, int a4, __int64 a45, int a5, int a6)
{
	typedef int(__fastcall * fc_funct)(__int64 a1, __int64 a2, int a3, int a4, __int64 a45, int a5, int a6);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x416710);
	return fc_cc_funct(a1, a2, a3, a4, a45, a5, a6);
}

__int64 * __fastcall ccGameProperties::forsceneloading(__int64 a1)
{
	typedef __int64*(__fastcall * fc_funct)(__int64 a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x21346C);
	return fc_cc_funct(a1);
}

__int64 __fastcall ccGameProperties::flashmalloc(__int64 a1)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x657B64);
	return fc_cc_funct(a1);
}

__int64 __fastcall ccGameProperties::msgbox(__int64 a1, char* a2)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1, char* a2);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x657EE0);
	return fc_cc_funct(a1, a2);
}

__int64 __fastcall ccGameProperties::msgbox2(__int64 a1, char* a2, __int64 a3)
{
	typedef __int64(__fastcall * fc_funct)(__int64 a1, char* a2, __int64 a3);
	fc_funct fc_cc_funct;
	fc_cc_funct = (fc_funct)(d3dcompiler_47_og::moduleBase + 0x658308);
	return fc_cc_funct(a1, a2, a3);
}