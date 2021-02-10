#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "API_Console.h"

#include "ccMain.h"
#include "d3dcompiler_47_og.h"
#include "ccGeneralGameFunctions.h"

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
void c_ViewMessageConversions();
void c_Help();

void API_Console::InitializeConsole()
{
	AddCommand("ConvertMessage", (uintptr_t)c_ConvertMessage, 1);
	AddCommand("ViewMessageConversions", (uintptr_t)c_ViewMessageConversions, 0);
	AddCommand("Help", (uintptr_t)c_Help, 0);

	// Load plugin commands
	for (int actualPlugin = 0; actualPlugin < ccMain::PluginList.size(); actualPlugin++)
	{
		HINSTANCE hGetProcIDDLL = ccMain::PluginList.at(actualPlugin);

		typedef void(__stdcall *cmdfunct)(__int64 moduleBase, __int64 cmdFunction);
		cmdfunct funct = (cmdfunct)GetProcAddress(hGetProcIDDLL, "InitializeCommands");

		if (funct) funct(d3dcompiler_47_og::moduleBase, (__int64)AddCommand);
	}
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
		if (command == consoleCommands[x])
		{
			cmd = x;
			x = consoleCommands.size();
		}
	}

	return cmd;
}