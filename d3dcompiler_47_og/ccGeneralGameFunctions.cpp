#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#pragma comment(lib, "XInput.lib")
#include <Xinput.h>

#include "ccGeneralGameFunctions.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "ccMain.h"

using namespace moddingApi;
using namespace std;

BYTE ccGeneralGameFunctions::MAX_GAME_VERSION = 9;

// GAME INFO HOOK
void * ccGeneralGameFunctions::PTR_GAMEINFO_00 = 0;
typedef uintptr_t (__fastcall * gameinfohook)(uintptr_t);
gameinfohook g_GameInfoHook;
BYTE originalGameInfoFunction[15];
void UndoGameInfoHook();
uintptr_t __fastcall ccGeneralGameFunctions::SetGameInfoPointer(uintptr_t a1)
{
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
	memcpy(originalGameInfoFunction, (void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), (void*)(ccGeneralGameFunctions::SetGameInfoPointer), 15);
}
void UndoGameInfoHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), originalGameInfoFunction, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0xA03E90), 15, dwOld, &dwOld);
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
typedef DWORD(__stdcall * get_version_number)();
get_version_number g_GetVersionNumber;
int ccGeneralGameFunctions::GetVersionNumber()
{
	g_GetVersionNumber = (get_version_number)(d3dcompiler_47_og::moduleBase + 0x85CC78);
	return g_GetVersionNumber();
}

// GET VERSION STRING
char* ccGeneralGameFunctions::GetVersionString()
{
	int v = GetVersionNumber();

	char * Version[10] = {
		"1.00",
		"1.01",
		"1.02",
		"1.03",
		"1.04",
		"1.05",
		"1.06",
		"1.07",
		"1.08",
		"1.09",
	};

	return Version[v];
}

// GET VERSION STRING API
char* ccGeneralGameFunctions::GetVersionStringAPI()
{
	int v = GetVersionNumber();

	char * Version[10] = {
		"1.00 (Modding API by Zealot Tormunds)",
		"1.01 (Modding API by Zealot Tormunds)",
		"1.02 (Modding API by Zealot Tormunds)",
		"1.03 (Modding API by Zealot Tormunds)",
		"1.04 (Modding API by Zealot Tormunds)",
		"1.05 (Modding API by Zealot Tormunds)",
		"1.06 (Modding API by Zealot Tormunds)",
		"1.07 (Modding API by Zealot Tormunds)",
		"1.08 (Modding API by Zealot Tormunds)",
		"1.09 (Modding API by Zealot Tormunds)",
	};

	return Version[v];
}

// GET RYO POINTER
typedef uintptr_t(__cdecl * get_ryo_pointer)();
get_ryo_pointer g_GetRyoPointer;
uintptr_t ccGeneralGameFunctions::GetRyoPointer()
{
g_GetRyoPointer = (get_ryo_pointer)(d3dcompiler_47_og::moduleBase + 0x51C11C);
return g_GetRyoPointer();
}

// GET GAME MONEY
typedef int(__cdecl * get_game_money)();
get_game_money g_GetGameMoney;
int ccGeneralGameFunctions::GetGameMoney()
{
	g_GetGameMoney = (get_game_money)(d3dcompiler_47_og::moduleBase + 0x4DEAB8);
	return g_GetGameMoney();
}

// GAME MESSAGE TO STRING
typedef char *(__fastcall * message_to_string)(char *);
message_to_string g_MessageToString;
char * ccGeneralGameFunctions::MessageToString(char * msg)
{
	g_MessageToString = (message_to_string)(d3dcompiler_47_og::moduleBase + 0x4E80A4);
	return g_MessageToString(msg);
}

// HOOK OPEN ADV MESSAGE
typedef int *(__fastcall * openmsg)(char *);
openmsg g_OpenMsg;
int ccGeneralGameFunctions::OpenAdvMessageById(char * a)
{
	g_OpenMsg = (openmsg)(d3dcompiler_47_og::moduleBase + 0x4DB9F4);
	g_OpenMsg(a);
	return 0;
}

// START LOAD
typedef int *(__stdcall * startload)();
startload g_StartLoad;
int ccGeneralGameFunctions::StartLoad()
{
	g_StartLoad = (startload)(d3dcompiler_47_og::moduleBase + 0x65A198);
	return (int)g_StartLoad();
}

// END LOAD
typedef int *(__stdcall * endload)();
endload g_EndLoad;
int ccGeneralGameFunctions::EndLoad()
{
	g_EndLoad = (endload)(d3dcompiler_47_og::moduleBase + 0x32CAE8);
	return (int)g_EndLoad();
}

// Load CPK
typedef uintptr_t(__fastcall * readcpk)(char *, void *, uint16_t);
readcpk g_ReadCpk;
int ccGeneralGameFunctions::cpkcount = 0;
uintptr_t ccGeneralGameFunctions::Cpk_LoadXfbin(void * path)
{
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
	string st = "<color red>Naruto Storm 4</color> Modding API by Zealot Tormunds\n\n";
	if (ccMain::ModList.size() > 0)
	{
		st = st + "<color yellow>Mod List:</color>\n";
		for (int x = 0; x < ccMain::ModCount; x++)
		{
			st = st + "> " + ccMain::ModList[x];
			if (ccMain::ModAuth[x] != "") st = st + " <color yellow>(" + ccMain::ModAuth[x] + ")</color>\n";
			else st = st + "\n";
		}

		st = st + "\n";
		st = st + "<color yellow>" + to_string(ccMain::ModList.size()) + " mods installed</color>";
	}
	else
	{
		st = st + "<color yellow>No mods installed</color>\n";
	}
	return st;
}

// All custom messageinfo functions
vector<std::string> ccGeneralGameFunctions::MessageID;
vector<std::string> ccGeneralGameFunctions::MessageStr;
BYTE ccGeneralGameFunctions::ViewMessageConversions = 0;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString(uintptr_t MessageToDecode)
{
	if (ccGeneralGameFunctions::ViewMessageConversions == 0)
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

			if (finished == false)
			{
				std::string msg = (std::string)(char*)MessageToDecode;

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
		return MessageToDecode;
	}
}

typedef char *(__fastcall * message_to_string2)(char *);
message_to_string2 g_MessageToString2;

uintptr_t ccGeneralGameFunctions::Hook_MsgToString_Alt(uintptr_t MessageToDecode)
{
	g_MessageToString2 = (message_to_string2)(d3dcompiler_47_og::moduleBase + 0xAB4770);

	if (ccGeneralGameFunctions::ViewMessageConversions == 0)
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
				std::string msg = (std::string)(char*)MessageToDecode;

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
		return MessageToDecode;
	}
}

// GAMEPAD FUNCTIONS
bool ccGeneralGameFunctions::TestButton(WORD button)
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