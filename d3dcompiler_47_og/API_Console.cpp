#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iostream>
#include <mmsystem.h>
#include "API_Console.h"
#include "ccMain.h"
#include "d3dcompiler_47_og.h"
#include "ccGeneralGameFunctions.h"
#include "ccCharacterFunctions.h"
#include "ccBossIAFunctions.h"
#include "HookFunctions.h"
#pragma comment(lib, "winmm.lib")
using namespace std;
using namespace moddingApi;
#include "irrKlang.h"
using namespace irrklang;
// Console Functions
vector<string> consoleCommands;
vector<uintptr_t> consoleFunctions;
vector<int> consoleParams;
void AddCommand(string, uintptr_t, int);
int GetCommandIndex(string);

// Command Functions
void c_ConvertMessage();
void c_GetVersionNumber();
void c_GetVersionString();
void c_GetVersionStringAPI();
void c_GetRyo();
void c_StartLoad();
void c_EndLoad();
void c_ViewMessageConversions();
void c_Help();
void c_ViewAwakeningDebug();
void c_ReloadCharsel();
void c_ReloadProperties();
void c_ReloadInit();
void c_LoadScene();
void c_ReloadParamFiles();
void c_EnableAllPad();
void c_ControlNpc();
void c_ccGroupBattleEventCameraBegin();
void c_ccGroupBattleEventCameraMovePosBegin();
void c_ccGroupBattleEventCameraMoveLookBegin();
void c_ccGetGpPtr();
void c_ccMultiMatchShowPlayerStatus();
void c_ccGetCastPointer();
void c_SoundTest();

void API_Console::InitializeConsole()
{
	AddCommand("ConvertMessage", (uintptr_t)c_ConvertMessage, 1);
	//AddCommand("GetVersionNumber", (uintptr_t)c_GetVersionNumber, 0);
	//AddCommand("GetVersionString", (uintptr_t)c_GetVersionString, 0);
	//AddCommand("GetVersionStringAPI", (uintptr_t)c_GetVersionStringAPI, 0);
	/*AddCommand("GetRyo", (uintptr_t)c_GetRyo, 0);
	AddCommand("StartLoad", (uintptr_t)c_StartLoad, 0);
	AddCommand("EndLoad", (uintptr_t)c_EndLoad, 0);*/
	AddCommand("ViewMessageConversions", (uintptr_t)c_ViewMessageConversions, 0);
	AddCommand("Help", (uintptr_t)c_Help, 0);
	/*AddCommand("ReloadParamFiles", (uintptr_t)c_ReloadParamFiles, 0);
	AddCommand("EnableAllPad", (uintptr_t)c_EnableAllPad, 0);
	AddCommand("ControlNpc", (uintptr_t)c_ControlNpc, 2);
	AddCommand("ccGroupBattleEventCameraBegin", (uintptr_t)c_ccGroupBattleEventCameraBegin, 0);
	AddCommand("ccGroupBattleEventCameraMovePosBegin", (uintptr_t)c_ccGroupBattleEventCameraMovePosBegin, 4);
	AddCommand("ccGroupBattleEventCameraMoveLookBegin", (uintptr_t)c_ccGroupBattleEventCameraMoveLookBegin, 4);
	AddCommand("ccGetGpPtr", (uintptr_t)c_ccGetGpPtr, 0);
	AddCommand("ccMultiMatchShowPlayerStatus", (uintptr_t)c_ccMultiMatchShowPlayerStatus, 0);*/
	AddCommand("GetCastPointer", (uintptr_t)c_ccGetCastPointer, 1);
	AddCommand("SoundTest", (uintptr_t)c_SoundTest, 0);

	//cout << std::hex << (d3dcompiler_47_og::moduleBase + 0x1653688) << endl;
}

typedef void(__stdcall * f)();
f Function;

void API_Console::DoConsoleCommand(string Input)
{
	string Command = Input;

	int ind = GetCommandIndex(Command);
	if (ind != -1)
	{
		Function = (f)consoleFunctions[ind];
		Function();

		cout << endl;
	}
	else
	{
		cout << "Command not found" << endl;
	}
}

void c_ConvertMessage()
{
	std::string param1;

	cout << "MSG >> ";
	cin >> param1;
	char * param1_c = strcpy(new char[param1.length() + 1], param1.c_str());

	cout << ccGeneralGameFunctions::MessageToString(param1_c);
}

void c_SoundTest()
{
			// start the sound engine with default parameters
		ISoundEngine* engine = createIrrKlangDevice();

		if (!engine)
		{
			cout << 0;
		}
		  // play some sound stream, looped
		engine->play2D("mywavsound.wav", true);

		char i = 0;
		std::cin >> i; // wait for user to press some key

		engine->drop(); // delete engine
}

void c_GetVersionNumber()
{
	cout << ccGeneralGameFunctions::GetVersionNumber();
}

void c_GetVersionString()
{
	cout << ccGeneralGameFunctions::GetVersionString();
}

void c_GetVersionStringAPI()
{
	cout << ccGeneralGameFunctions::GetVersionStringAPI();
}

void c_GetRyo()
{
	cout << ccGeneralGameFunctions::GetGameMoney();
}

void c_StartLoad()
{
	ccGeneralGameFunctions::StartLoad();
}

void c_EndLoad()
{
	ccGeneralGameFunctions::EndLoad();
}

void c_ViewMessageConversions()
{
	if (ccGeneralGameFunctions::ViewMessageConversions == 0)
	{
		cout << "Enabling view of message conversions..." << endl;
		ccGeneralGameFunctions::ViewMessageConversions = 1;
	}
	else
	{
		cout << "Disabling view of message conversions..." << endl;
		ccGeneralGameFunctions::ViewMessageConversions = 0;
	}
}

void c_Help()
{
	cout << endl;
	cout << "Available commands:" << endl;
	for (int x = 0; x < consoleCommands.size(); x++)
	{
		cout << consoleCommands[x] << endl;
	}
}

#include "ccPlayer.h"
void c_ViewAwakeningDebug()
{
	//ccPlayer::AwakeDebugEnabled = !ccPlayer::AwakeDebugEnabled;
}

#include "ccCharacterFunctions.h"
void c_ReloadCharsel()
{
	ccCharacterFunctions::ReloadCharsel();
}

#include "ccGameProperties.h"
void c_ReloadProperties()
{
	ccGameProperties::ReloadProperties();
}

void c_ReloadInit()
{
	ccGameProperties::ReloadInit();
}

void c_LoadScene()
{
	std::string param1;

	cout << "SCENE >> ";
	cin >> param1;
	char * param1_c = strcpy(new char[param1.length() + 1], param1.c_str());

	ccGameProperties::ccLoadScene(param1_c);
}

void c_ReloadParamFiles()
{
	cout << "Reloading API's parameter files (specialCondParam, partnerSlotParam)..." << endl;
	ccMain::ReloadParamFiles();
	cout << "Files reloaded correctly" << endl;
}

void c_EnableAllPad()
{
	ccGeneralGameFunctions::enablePads();
}

void c_ControlNpc()
{
	std::string param1;
	cout << "CHAR >> ";
	cin >> param1;
	char * param1_c = strcpy(new char[param1.length() + 1], param1.c_str());

	std::string param2;
	cout << "PAD >> ";
	cin >> param2;
	char * param2_c = strcpy(new char[param2.length() + 1], param2.c_str());

	//cout << ccGeneralGameFunctions::MessageToString(param1_c);
	ccCharacterFunctions::EnableControl(stoi(param1), stoi(param2));
}

#include "LuaHook.h"
void c_ccGroupBattleEventCameraBegin()
{
	LuaHook::ccGroupBattleEventCameraBegin();
}

void c_ccGroupBattleEventCameraMovePosBegin()
{
	std::string param1;
	cout << "X >> ";
	cin >> param1;
	float param1_c = stof(param1);

	std::string param2;
	cout << "Z >> ";
	cin >> param2;
	float param2_c = stof(param2);

	std::string param3;
	cout << "Y >> ";
	cin >> param3;
	float param3_c = stof(param3);

	std::string param4;
	cout << "A >> ";
	cin >> param4;
	float param4_c = stof(param4);

	LuaHook::ccGroupBattleEventCameraMovePosBegin(param1_c, param2_c, param3_c, param4_c);
}

void c_ccGroupBattleEventCameraMoveLookBegin()
{
	std::string param1;
	cout << "X >> ";
	cin >> param1;
	float param1_c = stof(param1);

	std::string param2;
	cout << "Z >> ";
	cin >> param2;
	float param2_c = stof(param2);

	std::string param3;
	cout << "Y >> ";
	cin >> param3;
	float param3_c = stof(param3);

	std::string param4;
	cout << "A >> ";
	cin >> param4;
	float param4_c = stof(param4);

	LuaHook::ccGroupBattleEventCameraMovePosBegin(param1_c, param2_c, param3_c, param4_c);
}

#include "MultiMatch.h"
void c_ccGetGpPtr()
{
	cout << std::hex << (uintptr_t)MultiMatch::fc_GetGpPtr() << endl;
}

#include "LuaHook_Commands.h"
void c_ccMultiMatchShowPlayerStatus()
{
	LuaHook_Commands::ccEntryNameTelop("P4 > HP: 100 / CHK: 100", "", 570, 500, 0, 0, 120);
}

void c_ccGetCastPointer()
{
	std::string param1;

	cout << "CAST >> ";
	cin >> param1;
	char* param1_c = strcpy(new char[param1.length() + 1], param1.c_str());

	cout << "CHAR: " << hex << LuaHook::fc_ccGetCastPointer(param1_c) << endl;
}

void AddCommand(string command, uintptr_t function, int paramCount)
{
	consoleCommands.push_back(command);
	consoleFunctions.push_back(function);
	consoleParams.push_back(paramCount);
}

int GetCommandIndex(string command)
{
	int cmd = -1;

	for (int x = 0; x < consoleCommands.size(); x++)
	{
		//cout << command << " " << consoleCommands[x] << endl;
		if (command == consoleCommands[x])
		{
			cmd = x;
			x = consoleCommands.size();
		}
	}

	return cmd;
}