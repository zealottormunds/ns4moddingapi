#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#pragma comment(lib, "XInput.lib")
#include <Xinput.h>
#include "ccGeneralGameFunctions.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "ccMain.h"
#include "SDL.h"
#include "soloud/include/soloud.h"
#include "soloud/include/soloud_wav.h"
using namespace moddingApi;
using namespace std;

//Patch Notes
char ccGeneralGameFunctions::MAX_GAME_VERSION = 9;

// GAME INFO HOOK
void * ccGeneralGameFunctions::PTR_GAMEINFO_00 = 0;
BYTE originalGameInfoFunction[15];
void UndoGameInfoHook();
uintptr_t __fastcall ccGeneralGameFunctions::SetGameInfoPointer(uintptr_t a1)
{
	typedef uintptr_t(__fastcall * gameinfohook)(uintptr_t);
	gameinfohook g_GameInfoHook;
	UndoGameInfoHook();

	g_GameInfoHook = (gameinfohook)(d3dcompiler_47_og::moduleBase + 0xA03E90);
	uintptr_t result = g_GameInfoHook(a1);
	ccGeneralGameFunctions::PTR_GAMEINFO_00 = (void*)result;
	cout << "Game Info: " << std::hex << ccGeneralGameFunctions::PTR_GAMEINFO_00 << endl;

	ccGeneralGameFunctions::DoGameInfoHook();
	
	return result;
}

uintptr_t GameInfoHookAddress = 0xA03E90;
void ccGeneralGameFunctions::DoGameInfoHook()
{
	memcpy(originalGameInfoFunction, (void*)(d3dcompiler_47_og::moduleBase + GameInfoHookAddress), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + GameInfoHookAddress), (void*)(ccGeneralGameFunctions::SetGameInfoPointer), 15);
}
void UndoGameInfoHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + GameInfoHookAddress), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + GameInfoHookAddress), originalGameInfoFunction, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + GameInfoHookAddress), 15, dwOld, &dwOld);
}

// CPK LOADING
void ccGeneralGameFunctions::CpkLoadList()
{
	BYTE function[] = { 0x48, 0x8D, 0x05, 0x2A, 0x7A, 0x88, 0x00,
						0x89, 0x74, 0x24, 0x38, 0x89, 0x74, 0x24, 0x48,
						0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ptr
	};

	int StringLength = 0x20;
	vector<string> CpkList;

	CpkList.push_back("sim:data/launch/data1.cpk");
	CpkList.push_back("sim:data/launch/stage1.cpk");
	CpkList.push_back("disc:data/launch/dataRegion.cpk");
	CpkList.push_back("sim:data/launch/sound.cpk");
	CpkList.push_back("disc:data/launch/adx2.cpk");
	CpkList.push_back("disc:data/launch/movie1.cpk");
	CpkList.push_back("sim:data/launch/data12.cpk");
	CpkList.push_back("sim:data/launch/data13.cpk");

	// Alloc function
	void * main_malloc = VirtualAlloc(0, sizeof(function) + (CpkList.size() * StringLength), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	cout << "CPK LOAD: " << std::hex << (uintptr_t)main_malloc << endl;

	//memcpy(main_malloc, (void*)&function, sizeof(function));

	// Set up jump to go back to function
	uintptr_t addressToJump = d3dcompiler_47_og::RecalculateAddress(0x8501B7);
	memcpy((void*)((uintptr_t)&function[0] + 21), (void*)&addressToJump, 8);

	// Write cpk list in memory
	void * cpk_list = (void*)((uintptr_t)&function[0] + sizeof(function));
	int distance1 = (uintptr_t)cpk_list - ((uintptr_t)&function[0] + 7);
	memcpy((void*)((uintptr_t)&function[0] + 3), (void*)&distance1, 4);

	for (int x = 0; x < CpkList.size(); x++)
	{
		cout << "Address: " << std::hex << (uintptr_t)((uintptr_t)main_malloc + (StringLength * x)) << endl;
		memcpy((void*)((uintptr_t)main_malloc + sizeof(function) + (StringLength * x)), (void*)(CpkList[x].c_str()), CpkList[x].length());
	}

	memcpy(main_malloc, (void*)&function[0], sizeof(function));

	DWORD dwOld = 0;
	VirtualProtect(main_malloc, sizeof(function), PAGE_EXECUTE_READWRITE, &dwOld);

	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x8501A7), main_malloc, 15);
}

// SET MAX VERSION NUMBER
int ccGeneralGameFunctions::SetMaxVersion()
{
	uintptr_t mem_maxVer = d3dcompiler_47_og::moduleBase + 0x85c5b4;

	DWORD dwOld = 0;
	VirtualProtect((void*)mem_maxVer, 1, PAGE_EXECUTE_READWRITE, &dwOld);

	*(BYTE*)((DWORD_PTR)mem_maxVer) = ccGeneralGameFunctions::MAX_GAME_VERSION;

	VirtualProtect((void*)mem_maxVer, 1, dwOld, &dwOld);

	return 0;
}

// GET VERSION NUMBER
int ccGeneralGameFunctions::GetVersionNumber()
{
	typedef DWORD(__stdcall * get_version_number)();
	get_version_number g_GetVersionNumber;
	g_GetVersionNumber = (get_version_number)(d3dcompiler_47_og::moduleBase + 0x85CC78);
	return g_GetVersionNumber();
}

// GET RYO POINTER
uintptr_t ccGeneralGameFunctions::GetRyoPointer()
{
	typedef uintptr_t(__cdecl * get_ryo_pointer)();
	get_ryo_pointer g_GetRyoPointer;
	g_GetRyoPointer = (get_ryo_pointer)(d3dcompiler_47_og::moduleBase + 0x51C11C);
	return g_GetRyoPointer();
}

// GET GAME MONEY
int ccGeneralGameFunctions::GetGameMoney()
{
	typedef int(__cdecl * get_game_money)();
	get_game_money g_GetGameMoney;
	g_GetGameMoney = (get_game_money)(d3dcompiler_47_og::moduleBase + 0x4DEAB8);
	return g_GetGameMoney();
}

// GAME MESSAGE TO STRING [FIXED]
char * ccGeneralGameFunctions::MessageToString(char * msg)
{
	typedef char *(__fastcall * message_to_string)(char *);
	message_to_string g_MessageToString;
	g_MessageToString = (message_to_string)(d3dcompiler_47_og::moduleBase + 0x4E89C4);
	return g_MessageToString(msg);
}

// HOOK OPEN ADV MESSAGE
int ccGeneralGameFunctions::OpenAdvMessageById(char * a)
{
	typedef int *(__fastcall * openmsg)(char *);
	openmsg g_OpenMsg;
	g_OpenMsg = (openmsg)(d3dcompiler_47_og::moduleBase + 0x4DB9F4);
	g_OpenMsg(a);
	return 0;
}

// START LOAD
int ccGeneralGameFunctions::StartLoad()
{
	typedef int *(__stdcall * startload)();
	startload g_StartLoad;
	g_StartLoad = (startload)(d3dcompiler_47_og::moduleBase + 0x65A198);
	return (int)g_StartLoad();
}

// END LOAD
int ccGeneralGameFunctions::EndLoad()
{
	typedef int *(__stdcall * endload)();
	endload g_EndLoad;
	g_EndLoad = (endload)(d3dcompiler_47_og::moduleBase + 0x32CAE8);
	return (int)g_EndLoad();
}

// Load CPK
int ccGeneralGameFunctions::cpkcount = 0;
uintptr_t ccGeneralGameFunctions::Cpk_LoadXfbin(void * path)
{
	typedef uintptr_t(__fastcall * readcpk)(char *, void *, uint16_t);
	readcpk g_ReadCpk;

	g_ReadCpk = (readcpk)(d3dcompiler_47_og::moduleBase + 0x56AA4C);

	if (true)
	{
		char a[100];
		//cout << "Loading cpk: " << std::hex << path << endl;

		ccGeneralGameFunctions::cpkcount++;
		return g_ReadCpk((char*)path, a, 0);
	}
}

// Get mod list string
std::string GetModMessage()
{
	// Color codes
	string blue = "<color blue>";
	string red = "<color red>";
	string yellow = "<color yellow>";
	string reset = "</color>";

	//Credits
	string st = "lol";
	if (ccMain::ModList.size() > 0)
	{
		st = yellow + "Perfect Storm Version 1.0" +
			reset + "\n\n" + red + "Mod Pack Credits:" + 
			reset + "\nLead Developer - Exavadeathwitch \nLead Designer - PlaycoArmboy \nTesters - Raghbir, Poisoned, Malice \nCostume Modders - Hydrabladez, Chakrawarrior2012, akiaki, Haikal \nMoveset Modders - Eliteace, TobiisTenten, Valant96 \nEngine Modders - Nighlin \nSound Modder - TheOneOfAll \nSpecial thanks to Zealot and R.A.G. for the modding API. \nSuper special thanks to TheWalkingAmongTheDead, Theovanua, Typhonua, Crownclown, Portable Productions, and UltimateOmbuStorm for providing code and models.";
	}
	else
	{
		st = st + "<color yellow>No mods installed</color>\n";
	}
	return st;
}

// This function doesn't work in 1.09 yet.
void RandomizeBackground()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::RecalculateAddress(0xEE52B0)), 0x20, PAGE_EXECUTE_READWRITE, &dwOld);
	char * randomBg = "data/ui/max/bg/bg_freebtl1.xfbin";
	switch (rand() % 7)
	{
	case 0:
		randomBg = "data/ui/max/bg/bg_freebtl1.xfbin";
		break;
	case 1:
		randomBg = "data/ui/max/bg/bg_freebtl2.xfbin";
		break;
	case 2:
		randomBg = "data/ui/max/bg/bg_freebtl3.xfbin";
		break;
	case 3:
		randomBg = "data/ui/max/bg/bg_freebtl4.xfbin";
		break;
	case 4:
		randomBg = "data/ui/max/bg/bg_freebtl5.xfbin";
		break;
	case 5:
		randomBg = "data/ui/max/bg/bg_freebtl6.xfbin";
		break;
	case 6:
		randomBg = "data/ui/max/bg/bg_freebtl7.xfbin";
		break;
	case 7:
		randomBg = "data/ui/max/bg/bg_freebtl7.xfbin";
		break;
	}
	memcpy((void*)(d3dcompiler_47_og::RecalculateAddress(0xEE52B0)), (void*)(randomBg), 0x20);
	VirtualProtect((void*)(d3dcompiler_47_og::RecalculateAddress(0xEE52B0)), 0x20, dwOld, &dwOld);
}

// All custom messageinfo functions
vector<std::string> ccGeneralGameFunctions::MessageID;
vector<std::string> ccGeneralGameFunctions::MessageStr;
char ccGeneralGameFunctions::ViewMessageConversions = 0;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString(uintptr_t MessageToDecode)
{
	//bool showDecode = true;
	//if ((string((char*)MessageToDecode).length() >= 4 && string((char*)MessageToDecode).substr(0, 4) == "####")) showDecode = false;

	//RandomizeBackground();

	if (ccGeneralGameFunctions::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		HookFunctions::UndoMessageInfoHook();
		char* result = ccGeneralGameFunctions::MessageToString((char*)MessageToDecode);
		HookFunctions::DoMessageInfoHook();

		if (MessageToDecode != 0)
		{
			bool finished = false;

			string message((char*)MessageToDecode);

			if (message == "network_agreement_EU_s-A" || message == "network_agreement_s-A")
			{
				result = (char*)GetModMessage().c_str();
				finished = true;
			}
			else if (message == "network_agreementp2_EU_s-A" || message == "network_agreementp2_s-A")
			{
				result = "";
				finished = true;
			}
			// Patch Notes Stuff/After Credits Screen
			if (finished == false)
			{
				string msg((char*)MessageToDecode);
				if (msg == "network_agreement_select") result = "Thanks for Playing!";
				else if (msg == "network_agreement_ok") result = "Patch Notes";
				else if (msg == "network_agreement_ng") result = "Continue to Game!";
				else if (msg == "network_privacy_s-A") result = "patchnotes";
				else
				{
					for (int x = 0; x < MessageID.size(); x++)
					{
						if (msg == MessageID[x])
						{
							result = (char*)MessageStr[x].c_str();
						}
					}
				}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}
		return (uintptr_t)result;
	}
	else
	{
		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}

typedef char *(__fastcall * message_to_string2)(char *);
message_to_string2 g_MessageToString2;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString_Alt(uintptr_t MessageToDecode)
{
	g_MessageToString2 = (message_to_string2)(d3dcompiler_47_og::moduleBase + 0xAB7CA0);

	//bool showDecode = true;
	//if ((string((char*)MessageToDecode).length() >= 4 && string((char*)MessageToDecode).substr(0, 4) == "####")) showDecode = false;

	if (ccGeneralGameFunctions::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		HookFunctions::UndoMessageInfoHook2();
		char * result = g_MessageToString2((char*)MessageToDecode);
		HookFunctions::DoMessageInfoHook2();

		if (MessageToDecode != 0)
		{
			bool finished = false;

			string message((char*)MessageToDecode);

			if (message == "network_agreement_EU_s-A" || message == "network_agreement_s-A")
			{
				result = (char*)GetModMessage().c_str();
				finished = true;
			}
			else if (message == "network_agreementp2_EU_s-A" || message == "network_agreementp2_s-A")
			{
				result = "";
				finished = true;
			}

			if (finished == false)
			{
				string msg((char*)MessageToDecode);

				if (msg == "network_agreement_select") result = "Press any button to continue";
				else if (msg == "network_agreement_ok") result = "";
				else if (msg == "network_agreement_ng") result = "<icon btn_2 />";
				else
				{
					for (int x = 0; x < MessageID.size(); x++)
					{
						if (msg == MessageID[x])
						{
							result = (char*)MessageStr[x].c_str();
						}
					}
				}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}
		return (uintptr_t)result;
	}
	else
	{
		/*if (string((char*)MessageToDecode).length() >= 4 && string((char*)MessageToDecode).substr(0, 4) == "####")
		{
			cout << "Message: " << (char*)MessageToDecode << endl;
			string realstr = string((char*)MessageToDecode);
			char* res = (char*)realstr.substr(4, realstr.length()).c_str();

			return (uintptr_t)res;
		}*/

		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}

/*BYTE f_LoadXfbin[15];

void ccGeneralGameFunctions::HookLoadXfbin()
{
	__int64 __fastcall fc_Xfbin_LoadFile(__int64 FilePath);
	memcpy(f_LoadXfbin, (void*)(d3dcompiler_47_og::moduleBase + 0x5341CC), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x5341CC), (void*)(fc_Xfbin_LoadFile), 15);
}

void UnhookLoadXfbin()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x5341CC), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x5341CC), f_LoadXfbin, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x5341CC), 15, dwOld, &dwOld);
}

__int64 __fastcall fc_Xfbin_LoadFile(__int64 FilePath)
{
	typedef __int64(__fastcall * Xfbin_LoadFile)(__int64);
	Xfbin_LoadFile g_Xfbin_LoadFile;

	g_Xfbin_LoadFile = (Xfbin_LoadFile)(d3dcompiler_47_og::moduleBase + 0x5341CC);

	string ActualFilePath = string((char*)FilePath);
	string newFilePath = "disc:data_win32/" + ActualFilePath.substr(5, ActualFilePath.length() - 5);
	cout << newFilePath << endl;

	__int64 result = 0;

	char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);

	string TestPath = string(ApiPath) + "\\data_win32\\" + ActualFilePath.substr(5, ActualFilePath.length() - 5);
	cout << "Testing for " << TestPath << endl;

	if (filesystem::exists(TestPath) == true)
	{
		UnhookLoadXfbin();
		result = g_Xfbin_LoadFile((__int64)newFilePath.c_str());
		//result = g_Xfbin_LoadFile(FilePath);
		ccGeneralGameFunctions::HookLoadXfbin();
		cout << "Loaded " << newFilePath << endl;
	}
	else
	{
		UnhookLoadXfbin();
		result = g_Xfbin_LoadFile(FilePath);
		ccGeneralGameFunctions::HookLoadXfbin();
		cout << "Loaded " << FilePath << endl;
	}

	return result;
}

////////////////////////////////////////////////////////////////////////

__int64 __fastcall fc_Menu_LoadXfbin(__int64 a1, __int64 FilePath);
BYTE f_Menu_LoadXfbin[16];

void ccGeneralGameFunctions::HookLoadXfbin2()
{
	memcpy(f_Menu_LoadXfbin, (void*)(d3dcompiler_47_og::moduleBase + 0x9FEE00), 16);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x9FEE00), (void*)(fc_Menu_LoadXfbin), 16);
}

void UnhookLoadXfbin2()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x9FEE00), 16, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x9FEE00), f_Menu_LoadXfbin, 16);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x9FEE00), 16, dwOld, &dwOld);
}

__int64 __fastcall fc_Menu_LoadXfbin(__int64 a1, __int64 FilePath)
{
	typedef __int64(__fastcall * Menu_LoadXfbin)(__int64, __int64);
	Menu_LoadXfbin g_Menu_LoadXfbin;
	g_Menu_LoadXfbin = (Menu_LoadXfbin)(d3dcompiler_47_og::moduleBase + 0x9FEE00);

	string ActualFilePath = string((char*)FilePath);
	string newFilePath = "disc:data/" + ActualFilePath.substr(5, ActualFilePath.length() - 5);
	//cout << newFilePath << endl;

	__int64 result = 0;

	char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);

	string TestPath = string(ApiPath) + "\\data\\" + ActualFilePath.substr(5, ActualFilePath.length() - 5);
	//cout << "Testing for " << TestPath << endl;

	if (filesystem::exists(TestPath) == true)
	{
		UnhookLoadXfbin2();
		//result = g_Menu_LoadXfbin(a1, (__int64)newFilePath.c_str());
		result = g_Menu_LoadXfbin(a1, FilePath);
		ccGeneralGameFunctions::HookLoadXfbin2();
		//cout << "Loaded " << newFilePath << endl;
	}
	else
	{
		UnhookLoadXfbin2();
		result = g_Menu_LoadXfbin(a1, FilePath);
		ccGeneralGameFunctions::HookLoadXfbin2();
		//cout << "Loaded " << (char*)FilePath << endl;
	}

	return result;
}

////////////////////////////////////////////////////////////////////////

BYTE loadCpkFunc1[16];
void ccGeneralGameFunctions::HookCpkLoad()
{
	__int64 __fastcall loadCpkFunc(__int64 a1, __int64 a2, int a3);
	memcpy(loadCpkFunc1, (void*)(d3dcompiler_47_og::moduleBase + 0x56AA4C), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x56AA4C), (void*)(loadCpkFunc), 15);
}

void UnhookCpkLoad()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x56AA4C), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x56AA4C), loadCpkFunc1, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x56AA4C), 15, dwOld, &dwOld);
}

__int64 __fastcall loadCpkFunc(__int64 a1, __int64 a2, int a3)
{
	typedef __int64(__fastcall * fc_loadCpkFunc)(__int64, __int64, int);
	fc_loadCpkFunc g_loadCpkFunc;
	g_loadCpkFunc = (fc_loadCpkFunc)(d3dcompiler_47_og::moduleBase + 0x56AA4C);

	cout << std::hex << (uintptr_t)a1 << endl;
	cout << std::hex << (uintptr_t)a2 << endl;
	cout << a3 << endl;

	UnhookCpkLoad();
	__int64 result = g_loadCpkFunc(a1, a2, a3);
	ccGeneralGameFunctions::HookCpkLoad();

	return result;
}*/

// GAMEPAD FUNCTIONS
bool ccGeneralGameFunctions::TestButton(unsigned short button)
{
	XINPUT_STATE actualState;
	XInputGetState(0, &actualState);

	bool toReturn = false;

	if (button != 0x5000 && button != 0x6000)
	{
		if ((actualState.Gamepad.wButtons & button) != 0) toReturn = true;
	}
	else
	{
		switch (button)
		{
		case 0x5000:
			if (actualState.Gamepad.bLeftTrigger > 20) toReturn = true;
			break;
		case 0x6000:
			if (actualState.Gamepad.bRightTrigger > 20) toReturn = true;
			break;
		}
	}

	return (actualState.Gamepad.wButtons & button) != 0;
}

signed __int64 ccGeneralGameFunctions::enablePads()
{
	typedef signed __int64(__fastcall * fc_enableAllPad_00)();
	fc_enableAllPad_00 enableAllPad_00;
	enableAllPad_00 = (fc_enableAllPad_00)(d3dcompiler_47_og::moduleBase + 0x6582B4);
	return enableAllPad_00();
}

// Get the current frame of the game
int ccGeneralGameFunctions::GetCurrentFrame()
{
	int frame = 0;
	memcpy(&frame, (void*)(d3dcompiler_47_og::moduleBase + 0x15AE70C - 0xC00), 4);
	return frame;
}

// Get 30 or 60 depending on the settings
int ccGeneralGameFunctions::GetFPS()
{
	int fps = 0;
	memcpy(&fps, (void*)(d3dcompiler_47_og::moduleBase + 0x155F498), 4);
	return fps;
}

// Is focus
bool ccGeneralGameFunctions::IsFocus()
{
	// 08D30960

	uintptr_t *p1 = 0;
	uintptr_t *p2 = 0;
	uintptr_t *p3 = 0;
	uintptr_t *p4 = 0;
	int *p5 = 0;

	p1 = (uintptr_t*)(d3dcompiler_47_og::moduleBase - 0xC00 + 0x08D30960);
	if (*p1 == 0) return 0;
	p2 = (uintptr_t*)(*p1 + 0x8);
	if (*p2 == 0) return 0;
	p3 = (uintptr_t*)(*p2 + 0xB0);
	if (*p3 == 0) return 0;
	p4 = (uintptr_t*)(*p3 + 0x48);
	if (*p4 == 0) return 0;
	p4 = (uintptr_t*)(*p3 + 0x48);
	if (*p4 == 0) return 0;
	p5 = (int*)(*p4 + 0x994);

	return *p5;
}