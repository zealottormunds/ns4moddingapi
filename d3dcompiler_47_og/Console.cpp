#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include <WinSock2.h>
#include <Windows.h>

#include "Common.h"
#include "Console.h"
#include "ccGeneralGameFunctions.h"
#include "HookFunctions.h"

#include "ModManager.h"

using namespace std;
using namespace moddingApi;

// Console Functions
vector<string> consoleCommands;
vector<uintptr_t> consoleFunctions;
vector<int> consoleParams;
void AddCommand(string, uintptr_t, int);
int GetCommandIndex(string);

// Command Functions
void cmdUnloadPlugins();
void cmdReloadPlugins();
void cmdConvertMessage();
void cmdViewMessageConversions();
void cmdHelp();

void Console::InitializeConsole()
{
	AddCommand("UnloadPlugins", (uintptr_t)cmdUnloadPlugins, 0);
	AddCommand("ReloadPlugins", (uintptr_t)cmdReloadPlugins, 0);
	AddCommand("ConvertMessage", (uintptr_t)cmdConvertMessage, 1);
	AddCommand("ViewMessageConversions", (uintptr_t)cmdViewMessageConversions, 0);
	AddCommand("Help", (uintptr_t)cmdHelp, 0);

	// Load plugin commands
	std::vector<Mod*> modList = ModManager::GetModList();
	int modCount = modList.size();
	for (int mod = 0; mod < modCount; mod++)
	{
		Mod * m = modList[mod];

		std::vector<Plugin*> pluginList = m->pluginList;
		int pluginCount = pluginList.size();
		for (int plugin = 0; plugin < pluginCount; plugin++)
		{
			Plugin * p = pluginList[plugin];
			HINSTANCE hGetProcIDDLL = (HINSTANCE)(p->hInstance);

			typedef void(__stdcall *cmdfunct)(__int64 a, __int64 cmdFunction);
			cmdfunct funct = (cmdfunct)GetProcAddress(hGetProcIDDLL, "InitializeCommands");

			if (funct) funct(0, (__int64)AddCommand);
		}
	}

	cout << "Console :: Commands have been initialized" << endl;
}

typedef void(__stdcall * f)();
f Function;

void Console::DoConsoleCommand(string Input)
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
		cout << "Console :: Command not found" << endl;
	}
}

void cmdUnloadPlugins()
{
	//NS4Framework::PluginState = -1;
}

void cmdReloadPlugins()
{
	/*Console::RestartConsole();
	NS4Framework::ReadApiFiles(true);
	Console::InitializeConsole();
	HookFunctions::InitializePluginHooks();*/
}

void cmdConvertMessage()
{
	std::string param1;

	cout << "MSG >> ";
	cin >> param1;
	char * param1_c = strcpy(new char[param1.length() + 1], param1.c_str());

	cout << ccGeneralGameFunctions::MessageToString(param1_c);
}

void cmdViewMessageConversions()
{
	if (ccGeneralGameFunctions::ViewMessageConversions == 0)
	{
		cout << "Console :: Enabling view of message conversions..." << endl;
		ccGeneralGameFunctions::ViewMessageConversions = 1;
	}
	else
	{
		cout << "Console :: Disabling view of message conversions..." << endl;
		ccGeneralGameFunctions::ViewMessageConversions = 0;
	}
}

void cmdHelp()
{
	cout << endl;
	cout << "Available commands:" << endl;
	for (int x = 0; x < consoleCommands.size(); x++)
	{
		cout << consoleCommands[x] << endl;
	}
}

void AddCommand(string command, uintptr_t function, int paramCount)
{
	consoleCommands.push_back(command);
	consoleFunctions.push_back(function);
	consoleParams.push_back(paramCount);
}

void Console::RestartConsole()
{
	consoleCommands.clear();
	consoleFunctions.clear();
	consoleParams.clear();
}

int GetCommandIndex(string command)
{
	int cmd = -1;

	for (int x = 0; x < consoleCommands.size(); x++)
	{
		if (command == consoleCommands[x])
		{
			cmd = x;
			x = consoleCommands.size();
		}
	}

	return cmd;
}