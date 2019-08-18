#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "API_Console.h"

#include "ccMain.h"
#include "d3dcompiler_47_og.h"
#include "ccGeneralGameFunctions.h"
#include "ccCharacterFunctions.h"
#include "ccBossIAFunctions.h"
#include "HookFunctions.h"

using namespace std;
using namespace moddingApi;

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

void API_Console::InitializeConsole()
{
	AddCommand("ConvertMessage", (uintptr_t)c_ConvertMessage, 1);
	AddCommand("GetVersionNumber", (uintptr_t)c_GetVersionNumber, 0);
	AddCommand("GetVersionString", (uintptr_t)c_GetVersionString, 0);
	AddCommand("GetVersionStringAPI", (uintptr_t)c_GetVersionStringAPI, 0);
	AddCommand("GetRyo", (uintptr_t)c_GetRyo, 0);
	AddCommand("StartLoad", (uintptr_t)c_StartLoad, 0);
	AddCommand("EndLoad", (uintptr_t)c_EndLoad, 0);
	AddCommand("ViewMessageConversions", (uintptr_t)c_ViewMessageConversions, 0);
	AddCommand("Help", (uintptr_t)c_Help, 0);
	//AddCommand("ViewAwakeningDebug", (uintptr_t)c_ViewAwakeningDebug, 0);
	//AddCommand("ReloadCharsel", (uintptr_t)c_ReloadCharsel, 0);
	//AddCommand("ReloadProperties", (uintptr_t)c_ReloadProperties, 0);
	//AddCommand("ReloadInit", (uintptr_t)c_ReloadInit, 0);
	//AddCommand("LoadScene", (uintptr_t)c_LoadScene, 1);
	AddCommand("ReloadParamFiles", (uintptr_t)c_ReloadParamFiles, 0);

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
	ccPlayer::AwakeDebugEnabled = !ccPlayer::AwakeDebugEnabled;
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
