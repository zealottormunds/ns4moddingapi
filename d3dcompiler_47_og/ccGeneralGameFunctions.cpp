#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#pragma comment(lib, "XInput.lib")
#include <Xinput.h>

#include "ccGeneralGameFunctions.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "ccMain.h"

using namespace moddingApi;
using namespace std;

// GET VERSION NUMBER
int ccGeneralGameFunctions::GetVersionNumber()
{
	typedef DWORD(__stdcall * get_version_number)();
	get_version_number g_GetVersionNumber;
	g_GetVersionNumber = (get_version_number)(d3dcompiler_47_og::moduleBase + 0x85CC78);
	return g_GetVersionNumber();
}

// GAME MESSAGE TO STRING [FIXED]
char * ccGeneralGameFunctions::MessageToString(char * msg)
{
	typedef char *(__fastcall * message_to_string)(char *);
	message_to_string g_MessageToString;
	g_MessageToString = (message_to_string)(d3dcompiler_47_og::moduleBase + 0x4E89C4);
	return g_MessageToString(msg);
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
	g_MessageToString2 = (message_to_string2)(d3dcompiler_47_og::moduleBase + 0xAB87D0);

	if (ccGeneralGameFunctions::ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		HookFunctions::UndoMessageInfoHook2();
		char* result = g_MessageToString2((char*)MessageToDecode);
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

		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}

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