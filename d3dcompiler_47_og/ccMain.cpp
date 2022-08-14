#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <Xinput.h>

#include "ccMain.h"
#include "API_Console.h"
#include "d3dcompiler_47_og.h"
#include "ccGeneralGameFunctions.h"
#include "ccGameProperties.h"
#include "ccCharacterFunctions.h"
#include "HookFunctions.h"

#include "FileParser.h"

using namespace moddingApi;
using namespace std;

int Console_GetInt(char*);
char * Console_GetString(char*);
bool EnableAPI = false;
vector<BYTE> ReadAllBytes(string);

// When the API boots...
DWORD WINAPI ccMain::Main()
{
	// Read all the mods and configs
	ccMain::ReadApiFiles();

	// Initialize the function hooks
	HookFunctions::InitializeHooks();

	// Enable API
	EnableAPI = true;

	// Read CPK
	//ReadCpk();

	// Enable the game thread (this is for player modification in game)
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ccMain::LoopGame, (HMODULE)d3dcompiler_47_og::st_hModule, 0, nullptr);

	// Loop console
	//ccMain::LoopConsole();
	CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ccMain::LoopConsole, (HMODULE)d3dcompiler_47_og::st_hModule, 0, nullptr));

	return 0;
}

// Process the console
DWORD WINAPI ccMain::LoopConsole()
{
	while (EnableAPI == false)
	{
		Sleep(100);
	}

	API_Console::InitializeConsole();

	while (EnableAPI)
	{
		std::string cmd;
		cout << "> ";
		cin >> cmd;

		API_Console::DoConsoleCommand(cmd);

		Sleep(100);
	}

	return 0;
}

// Process the player
#include "Input.h"
DWORD WINAPI ccMain::LoopGame()
{
	while (true)
	{
		//Input::UpdateKeys();

		// Load plugin commands
		for (int actualPlugin = 0; actualPlugin < ccMain::PluginList.size(); actualPlugin++)
		{
			HINSTANCE hGetProcIDDLL = ccMain::PluginList.at(actualPlugin);

			if (PluginLoop.at(actualPlugin) != 0)
			{
				typedef void(__stdcall *loopfunct)(__int64 moduleBase);
				loopfunct funct = (loopfunct)(PluginLoop.at(actualPlugin));
				if (funct) funct(d3dcompiler_47_og::moduleBase);
			}
		}

		Sleep(10);
	}
	return 0;
}

// Console base commands
int Console_GetInt(char * CommandPrompt)
{
	if (CommandPrompt != "") cout << CommandPrompt << endl;
	int a;
	cin >> a;
	cout << endl;
	return a;
}

char * Console_GetString(char * CommandPrompt)
{
	if (CommandPrompt != "") cout << CommandPrompt << endl;
	char * a;
	cin >> a;
	cout << endl;
	return a;
}

// Mod list

int ccMain::ModCount = 0;
vector<std::string> ccMain::ModList;
vector<std::string> ccMain::ModDesc;
vector<std::string> ccMain::ModAuth;
vector<BYTE> ccMain::ModState;
std::vector<HINSTANCE> ccMain::PluginList;
std::vector<__int64> ccMain::PluginLoop;

// Initialize game functions
typedef uintptr_t(__fastcall * initializegame)(uintptr_t);
initializegame g_InitializeGame;
typedef uintptr_t(__fastcall * initializegame2)(float);
initializegame2 g_InitializeGame2;

// Read all mods
vector<string> ReadMessageFile(string);
void ReadPatchFile(string);
void ReadScriptFile(string);
void DoInstruction(string instruction, vector<string> params, string _file);
void ReadPartnerSlotParam(string _file);
void ReadSpecialConditionParam(string _file);

#include "GameSettings.h"
void ccMain::ReadApiFiles()
{
	char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);
	int ActualLength = strlen(ApiPath);

	strcat(ApiPath, "\\moddingapi\\");

	char ConfigPath[_MAX_PATH];
	strcpy(ConfigPath, ApiPath);
	ActualLength = strlen(ConfigPath);
	strcat(ConfigPath, "config.ini");

	// Check if config ini exists
	if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(ConfigPath) && GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		cout << "Config file not found, using default values." << endl;
		//return;
	}
	else
	{
		if (GetPrivateProfileInt("General", "EnableConsole", 1, ConfigPath) == 0)
		{
			FreeConsole();
		}
		else
		{
			// Console allocation
			AllocConsole();
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);

			cout << "====== Welcome to STORM 4 MODDING CONSOLE ======" << endl;
		}

		if (GetPrivateProfileInt("General", "EnableModList", 1, ConfigPath) == 1)
		{
			cout << "Enable mod list" << endl;
			DWORD dwOld = 0;
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6E56CE), 1, PAGE_EXECUTE_READWRITE, &dwOld);
			BYTE a = 0;
			memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x6E56CE), &a, 1);
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6E56CE), 1, dwOld, &dwOld);
		}

		cout << "Config finished..." << endl;

		// Start reading mods
		strcat(ApiPath, "mods\\");

		for (const auto & entry : filesystem::directory_iterator(ApiPath))
		{
			std::string s = entry.path().string();

			char ModName[100];
			int StartIndex = strlen(ApiPath);
			int Count = s.length() - StartIndex;

			strncpy(ModName, &s[StartIndex], 100);

			std::string ModPath = (std::string)(ApiPath) + (std::string)(ModName);
			std::string InfoPath = ModPath + "\\info.txt";

			//cout << InfoPath << endl;

			if (filesystem::exists(InfoPath) == true)
			{
				BYTE actual = 0;
				string modName;
				string modDesc;
				string modAuth;

				ifstream file;
				file.open(InfoPath);

				while (file.eof() == false && actual < 3)
				{
					char a;
					switch (actual)
					{
					case 0:
						a = file.get();
						if (a == '|') actual = 1;
						else modName = modName + a;
						break;
					case 1:
						a = file.get();
						if (a == '|') actual = 2;
						else modDesc = modDesc + a;
						break;
					case 2:
						a = file.get();
						if (a == '|') actual = 3;
						else modAuth = modAuth + a;
						break;
					}
				}
				file.close();

				if (modName != "")
				{
					// Read plugins first
					for (const auto & f : filesystem::directory_iterator(ModPath))
					{
						string _file = f.path().string();
						string _ext = _file.substr(_file.length() - 4, 4);

						if (_ext == ".dll")
						{
							char* a = new char[_file.length() + 1];
							strcpy(a, _file.c_str());
							HINSTANCE hGetProcIDDLL = LoadLibrary(a);

							if (!hGetProcIDDLL)
							{
								cout << "PluginSystem :: Error loading plugin " << _file.c_str() << ": ERROR CODE " << std::dec << GetLastError() << endl;
							}
							else
							{
								string pluginname = string(ModName) + "/" + filesystem::path(_file).filename().string();
								PluginList.push_back(hGetProcIDDLL);
								cout << "PluginSystem :: Loaded plugin " << pluginname << endl;

								vector<__int64> functionExport;
								functionExport.push_back((__int64)Input::UpdateKeys);
								functionExport.push_back((__int64)Input::GetKey);
								functionExport.push_back((__int64)Input::GetKeyDown);
								functionExport.push_back((__int64)Input::GetKeyUp);

								// Get InitializePlugin
								typedef void(__stdcall *initfunct)(__int64 moduleBase, vector<__int64> functs);
								initfunct funct = (initfunct)GetProcAddress(hGetProcIDDLL, "InitializePlugin");

								if (funct) funct(d3dcompiler_47_og::moduleBase, functionExport);
								else cout << "PluginSystem :: Init not found in plugin" << endl;

								// Get GameLoop
								typedef void(__stdcall *initfunctloop)(__int64 moduleBase);
								initfunctloop functloop = (initfunctloop)GetProcAddress(hGetProcIDDLL, "GameLoop");

								if (functloop) PluginLoop.push_back((__int64)functloop);
								else
								{
									cout << "PluginSystem :: Loop not found in plugin" << endl;
									PluginLoop.push_back(0);
								}
							}
						}
					}

					// Read API files
					for (const auto & f : filesystem::directory_iterator(ModPath))
					{
						string _file = f.path().string();
						string _ext = _file.substr(_file.length() - 4, 4);
						bool fileManagedByPlugin = false;

						// Send file to plugin
						for (int actualPlugin = 0; actualPlugin < ccMain::PluginList.size(); actualPlugin++)
						{
							HINSTANCE hGetProcIDDLL = ccMain::PluginList.at(actualPlugin);

							typedef bool(__stdcall *filefunct)(__int64 moduleBase, std::string path, vector<BYTE> file);
							filefunct funct = (filefunct)GetProcAddress(hGetProcIDDLL, "ParseApiFiles");
							if (funct)
							{
								fileManagedByPlugin = funct(d3dcompiler_47_og::moduleBase, _file, ReadAllBytes(_file));
							}

							if (fileManagedByPlugin) actualPlugin = ccMain::PluginList.size();
						}

						if (fileManagedByPlugin == false)
						{
							if (_ext == "ns4s")
							{
								vector<string> msg = ReadMessageFile(_file);

								for (int x = 0; x + 1 < msg.size(); x = x + 2)
								{
									ccGeneralGameFunctions::MessageID.push_back(msg[x]);
									ccGeneralGameFunctions::MessageStr.push_back(msg[x + 1]);
								}
							}
							else if (_ext == "ns4p")
							{
								ReadPatchFile(_file);
							}
							else if (_ext == "ns4e")
							{
								ReadScriptFile(_file);
							}
							else if (_ext == ".cpk")
							{
								string cpkinfo = filesystem::path(_file).replace_extension("cpk.info").string();
								if (filesystem::exists(cpkinfo))
								{
									vector<BYTE> fileBytes1 = ReadAllBytes(cpkinfo);
									int priority = fileBytes1[0] + (fileBytes1[1] * 0x100) + (fileBytes1[2] * 0x10000) + (fileBytes1[3] * 0x1000000);

									cout << "CpkLoader :: Priority set for cpk " << string(ModName) << "/" << filesystem::path(_file).filename() << " to " << std::dec << priority << "." << endl;
									string cpkpath = "moddingapi/mods/" + string(ModName) + "/" + filesystem::path(_file).filename().string();
									char* a = new char[cpkpath.length() + 1];
									strcpy(a, cpkpath.c_str());
									GameSettings::CpkToLoad.push_back(a);
									GameSettings::CpkPriority.push_back(priority);
								}
								else
								{
									cout << "CpkLoader :: Info file for cpk " << string(ModName) << "/" << filesystem::path(_file).filename() << " was not found. Setting priority to default (13)." << endl;
									string cpkpath = "moddingapi/mods/" + string(ModName) + "/" + filesystem::path(_file).filename().string();
									char* a = new char[cpkpath.length() + 1];
									strcpy(a, cpkpath.c_str());
									GameSettings::CpkToLoad.push_back(a);
									GameSettings::CpkPriority.push_back(13);
								}
							}
							else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "partnerSlotParam.xfbin")
							{
								ReadPartnerSlotParam(_file);
							}
							else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "specialCondParam.xfbin")
							{
								ReadSpecialConditionParam(_file);
							}
						}
					}
					ccMain::ModCount++;
					ccMain::ModList.push_back(modName);
					ccMain::ModDesc.push_back(modDesc);
					ccMain::ModAuth.push_back(modAuth.substr(0, modAuth.length() - 1));
					ccMain::ModState.push_back(1);

					cout << "Enabling mod \"" << ModName << "\"" << endl;
				}
				else
				{
					cout << "Disabling mod \"" << ModName << "\" - Invalid info file." << endl;
				}
			}
			else
			{
				cout << "Disabling mod \"" << ModName << "\" - No info.txt file found." << endl;
			}
		}

		cout << "Finished reading mods" << endl;
	}
}

void ccMain::ReloadParamFiles()
{
	// Start reading mods
	char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);
	int ActualLength = strlen(ApiPath);

	strcat(ApiPath, "\\moddingapi\\");

	char ConfigPath[_MAX_PATH];
	strcpy(ConfigPath, ApiPath);
	ActualLength = strlen(ConfigPath);
	strcat(ConfigPath, "config.ini");

	strcat(ApiPath, "mods\\");

	ccCharacterFunctions::c_partnerCodes.clear();
	ccCharacterFunctions::c_partnerFunctions.clear();
	ccCharacterFunctions::c_specialCondCodes.clear();
	ccCharacterFunctions::c_specialCondFunct.clear();

	for (const auto & entry : filesystem::directory_iterator(ApiPath))
	{
		std::string s = entry.path().string();

		char ModName[100];
		int StartIndex = strlen(ApiPath);
		int Count = s.length() - StartIndex;

		strncpy(ModName, &s[StartIndex], 100);

		std::string ModPath = (std::string)(ApiPath) + (std::string)(ModName);
		std::string InfoPath = ModPath + "\\info.txt";

		//cout << InfoPath << endl;

		if (filesystem::exists(InfoPath) == true)
		{
			BYTE actual = 0;
			string modName;
			string modDesc;
			string modAuth;

			ifstream file;
			file.open(InfoPath);

			while (file.eof() == false && actual < 3)
			{
				char a;
				switch (actual)
				{
				case 0:
					a = file.get();
					if (a == '|') actual = 1;
					else modName = modName + a;
					break;
				case 1:
					a = file.get();
					if (a == '|') actual = 2;
					else modDesc = modDesc + a;
					break;
				case 2:
					a = file.get();
					if (a == '|') actual = 3;
					else modAuth = modAuth + a;
					break;
				}
			}
			file.close();

			//cout << "heehee" << endl;

			if (modName != "")
			{
				// Start reading mod files
				vector<string> files;
				for (const auto & f : filesystem::directory_iterator(ModPath))
				{
					string _file = f.path().string();
					string _ext = _file.substr(_file.length() - 4, 4);

					if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "partnerSlotParam.xfbin")
					{
						ReadPartnerSlotParam(_file);
						cout << "Reloading partnerSlotParam.xfbin in " << modName << endl;
					}
					else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "specialCondParam.xfbin")
					{
						ReadSpecialConditionParam(_file);
						cout << "Reloading specialCondParam.xfbin in " << modName << endl;
					}
				}
			}
		}
	}

	ccCharacterFunctions::PartnerFunctions();
	ccCharacterFunctions::SpecialCondFunctions();
}

vector<string> ReadMessageFile(string _file)
{
	ifstream f;
	f.open(_file);

	vector<string> Messages;
	string actual = "";
	while (!f.eof())
	{
		char a = f.get();

		if (a != 0x00)
		{
			actual = actual + a;
		}
		else
		{
			//cout << "Push back " << actual << endl;
			Messages.push_back(actual);
			actual = "";
		}
	}

	f.close();

	return Messages;
}

void ReadPatchFile(string _file)
{
	int SlashCount = 0;
	int ExtensionAddress = 0;
	for (int x = 0; x < _file.length(); x++)
	{
		if (_file[x] == '\\') SlashCount++;
		if (_file[x] == '.') ExtensionAddress = x;
	}

	int StartAddress = 0;
	int SlashesPassed = 0;
	for (int x = 0; x < _file.length(); x++)
	{
		if (_file[x] == '\\') SlashesPassed++;

		if (SlashesPassed == SlashCount)
		{
			StartAddress = x + 1;
			x = _file.length();
		}
	}

	string Hex = _file.substr(StartAddress, ExtensionAddress - StartAddress);

	//cout << Hex << endl;

	uintptr_t Address = 0;

	try
	{
		Address = strtol(Hex.c_str(), NULL, 16);
	}
	catch(exception e)
	{
		Address = 0;
	}

	if (Address > 0x13B4DAC) Address = Address + 0x400;
	else if (Address > 0xEAAFAC) Address = Address + 0x400;

	//cout << std::hex << Address << endl;

	ifstream f;
	f.open(_file);

	vector<BYTE> replace;
	int count = 0;
	while (!f.eof())
	{
		replace.push_back(f.get());
		count++;
	}

	if (Address != 0x0)
	{
		DWORD dwOld = 0;
		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + Address), replace.size(), PAGE_EXECUTE_READWRITE, &dwOld);
		BYTE v[0x1000];
		for (int x = 0; x < count; x++)
		{
			v[x] = replace[x];
		}

		//cout << "Patch";
		cout << "Patched .exe at " << hex << Address << " (" << std::hex << d3dcompiler_47_og::moduleBase + Address << ")" << endl;
		memcpy((void*)(d3dcompiler_47_og::moduleBase + Address), &v, count - 1);
		VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + Address), replace.size(), dwOld, &dwOld);
	}

	f.close();
}

vector<BYTE> var;
void ReadScriptFile(string _file)
{
	ifstream f;
	f.open(_file);

	BYTE mode = 0;
	string instruction;
	BYTE parameterCount;

	vector<string> params;
	uintptr_t address;

	bool ready = false;

	while (!f.eof())
	{
		char a = f.get();

		if (a != '\n')
		{
			if (mode == 0)
			{
				if (a != '(')
				{
					instruction = instruction + a;
				}
				else
				{
					mode = 1;
					if (instruction == "Get")
					{
						//cout << "Get" << endl;
						parameterCount = 2;
						params.push_back("");
					}
					else if (instruction == "Write")
					{
						//cout << "Write" << endl;
						parameterCount = 2;
						params.push_back("");
					}
					else if (instruction == "WriteBytes")
					{
						parameterCount = 3;
						params.push_back("");
					}
				}
			}
			else if (mode == 1)
			{
				if (a != ',' && a != ')')
				{
					params[params.size() - 1] += a;
				}
				else
				{
					if (a == ',')
					{
						//cout << "Read param " << params[params.size() - 1] << endl;
						//cout << "Adding param" << endl;
						params.push_back("");
					}
					else if (a == ')')
					{
						//cout << "Read param " << params[params.size() - 1] << endl;
						//cout << "Mode 2" << endl;
						DoInstruction(instruction, params, _file);
						mode = 0;
					}
				}
			}
		}
		else
		{
			mode = 0;
			instruction = "";
			params.clear();
			parameterCount = 0;
			address = -1;
		}
	}

	f.close();
}

void ReadGameScriptFile(string _file)
{
	ifstream f;
	f.open(_file);

	BYTE mode = 0;
	string instruction;
	BYTE parameterCount;

	vector<string> params;
	uintptr_t address;

	bool ready = false;

	while (!f.eof())
	{
		char a = f.get();

		if (a != '\n')
		{
			if (mode == 0)
			{
				if (a != '(')
				{
					instruction = instruction + a;
				}
				else
				{
					mode = 1;
					if (instruction == "Get")
					{
						//cout << "Get" << endl;
						parameterCount = 2;
						params.push_back("");
					}
					else if (instruction == "Write")
					{
						//cout << "Write" << endl;
						parameterCount = 2;
						params.push_back("");
					}
					else if (instruction == "WriteBytes")
					{
						parameterCount = 3;
						params.push_back("");
					}
				}
			}
			else if (mode == 1)
			{
				if (a != ',' && a != ')')
				{
					params[params.size() - 1] += a;
				}
				else
				{
					if (a == ',')
					{
						//cout << "Read param " << params[params.size() - 1] << endl;
						//cout << "Adding param" << endl;
						params.push_back("");
					}
					else if (a == ')')
					{
						//cout << "Read param " << params[params.size() - 1] << endl;
						//cout << "Mode 2" << endl;
						DoInstruction(instruction, params, _file);
						mode = 0;
					}
				}
			}
		}
		else
		{
			mode = 0;
			instruction = "";
			params.clear();
			parameterCount = 0;
			address = -1;
		}
	}

	f.close();
}

void DoInstruction(string instruction, vector<string> params, string _file)
{
	if (instruction == "Get")
	{
		var.clear();
		uintptr_t v1 = strtol(params[0].c_str(), NULL, 16);

		if (v1 > 0x13A38AD) v1 = v1 + 0x1A00;
		else if (v1 > 0xEA7420) v1 = v1 + 0xE00;

		int v2 = atoi(params[1].c_str());

		//cout << "Get (" << std::hex << v1 << "," << v2 << ")" << endl;

		for (int x = 0; x < v2; x++)
		{
			var.push_back(*(BYTE*)(d3dcompiler_47_og::moduleBase + v1 + x));
		}
	}
	else if (instruction == "Write")
	{
		if (var.size() > 0)
		{
			int count = atoi(params[1].c_str());
			if (var.size() >= count)
			{
				uintptr_t v1 = strtol(params[0].c_str(), NULL, 16);
				
				if (v1 > 0x13B4DAC) v1 = v1 + 0x400;
				else if (v1 > 0xEAAFAC) v1 = v1 + 0x400;

				int v2 = atoi(params[1].c_str());

				//cout << "Write (" << std::hex << v1 << "," << v2 << ")" << endl;
				//cout << std::hex << d3dcompiler_47_og::moduleBase + v1 << endl;
				DWORD dwOld = 0;
				VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + v1), count, PAGE_EXECUTE_READWRITE, &dwOld);
				for (int x = 0; x < count; x++)
				{
					memcpy((void*)(d3dcompiler_47_og::moduleBase + v1 + x), (void*)&var[x], 1);
				}
				VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + v1), count, dwOld, &dwOld);
			}
			else
			{
				cout << "Error in script " << _file.c_str() << " : Tried to Write() more bytes than the ones saved with Get()" << endl;
			}
		}
		else
		{
			cout << "Error in script " << _file.c_str() << " : Tried to Write() without anything saved with Get()" << endl;
		}
		var.clear();
	}
	else if (instruction == "WriteBytes")
	{
		cout << "Error in script " << _file.c_str() << " : Function WriteBytes() doesn't exist" << endl;
	}
}

void ReadPartnerSlotParam(string _file)
{
	vector<BYTE> fileBytes = ReadAllBytes(_file);

	int slotCount = fileBytes.size() / 0x20;

	for (int x = 0; x < slotCount; x++)
	{
		string slotType = "";
		int slotCharacter = 0;
		int actual = (0x20 * x);

		while (actual < (0x20 * x) + 0x17)
		{
			if (fileBytes[actual] != 0x0)
			{
				slotType = slotType + (char)fileBytes[actual];
				actual++;
			}
			else
			{
				actual = (0x20 * x) + 0x17;
			}
		}

		//cout << "stuff: " << std::hex << (uintptr_t)fileBytes[actual] << " " << (uintptr_t)fileBytes[actual + 1] << endl;
		slotCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);

		uintptr_t slotFunct = 0x0;

		if (slotType == "PARTNER_TYPE_2PAR") slotFunct = 0x7F0064; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2KKG") slotFunct = 0x7F00BC; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2AKM") slotFunct = 0x7F0114; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2KRS") slotFunct = 0x7F016C; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_1AKM") slotFunct = 0x7F01C4; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_1KRS") slotFunct = 0x7F021C; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2SCX") slotFunct = 0x7F0274; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_8AEM") slotFunct = 0x7F02CC; // UPDATED TO 12

		ccCharacterFunctions::c_partnerFunctions.push_back(d3dcompiler_47_og::RecalculateAddress(slotFunct));
		ccCharacterFunctions::c_partnerCodes.push_back(slotCharacter);

		//cout << "CharacterType = " << slotType.c_str() << ", Chara = " << std::hex << slotCharacter << endl;
	}
}

bool finishedReadingSpecialCondition = false;
uintptr_t addressArea = 0;
vector<uintptr_t> addressList;
vector<string> condName;

void ReadSpecialConditionParam(string _file)
{
	vector<BYTE> fileBytes = ReadAllBytes(_file);

	int slotCount = fileBytes.size() / 0x20;

	for (int x = 0; x < slotCount; x++)
	{
		string slotType = "";
		int condCharacter = 0;
		int actual = (0x20 * x);

		while (actual < (0x20 * x) + 0x17)
		{
			if (fileBytes[actual] != 0x0)
			{
				slotType = slotType + (char)fileBytes[actual];
				actual++;
			}
			else
			{
				actual = (0x20 * x) + 0x17;
			}
		}

		condCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);

		uintptr_t condFunct = 0x0;
		int actualConditionIndex = -1;
		bool found = false;
		
		for (int x = 0; x < condName.size(); x++)
		{
			if (slotType == condName[x])
			{
				found = true;
				x = 0x5C;
				condFunct = addressList[x];
			}
		}

		int basecond = 0x7C4B7C;

		if (slotType == "COND_1CMN") condFunct = 0x7C4B7C;
		else if (slotType == "COND_2SIK") condFunct = 0x7C4BE4;
		else if (slotType == "COND_2HDN") condFunct = 0x7C4C4C;
		else if (slotType == "COND_2KKS") condFunct = 0x7C4CB4;
		else if (slotType == "COND_2CYB") condFunct = 0x7C4D1C;
		else if (slotType == "COND_2SCO") condFunct = 0x7C4D84;
		else if (slotType == "COND_2DDR") condFunct = 0x7C4DEC;
		else if (slotType == "COND_3HNZ") condFunct = 0x7C4E54;
		else if (slotType == "COND_3TOB") condFunct = 0x7C4EBC;
		else if (slotType == "COND_3TYO") condFunct = 0x7C3E14;
		else if (slotType == "COND_3MDR_2") condFunct = 0x7C4F24;
		else if (slotType == "COND_3KBT") condFunct = 0x7C4F8C;
		else if (slotType == "COND_2KNK") condFunct = 0x7C4FF4;
		else if (slotType == "COND_2JRY") condFunct = 0x7C505C;
		else if (slotType == "COND_3GAR") condFunct = 0x7C50C4; // same as below
		else if (slotType == "COND_2GAV") condFunct = 0x7C50C4; // same as above
		else if (slotType == "COND_2ORC") condFunct = 0x7C512C;
		else if (slotType == "COND_5KGY") condFunct = 0x7C5194;
		else if (slotType == "COND_2FOU") condFunct = 0x7C51FC;
		else if (slotType == "COND_2DNZ") condFunct = 0x7C5264;
		else if (slotType == "COND_3GUY") condFunct = 0x7C52CC;
		else if (slotType == "COND_2KBT") condFunct = 0x7C317C;
		else if (slotType == "COND_2MDR") condFunct = 0x7C31E4;
		else if (slotType == "COND_JKKS") condFunct = 0x7C324C;
		else if (slotType == "COND_2KIB") condFunct = 0x7C32B4;
		else if (slotType == "COND_2KNN") condFunct = 0x7C331C;
		else if (slotType == "COND_2SGT") condFunct = 0x7C3384;
		else if (slotType == "COND_4MKG") condFunct = 0x7C33EC;
		else if (slotType == "COND_2NRT") condFunct = 0x7C3454; // same as below
		else if (slotType == "COND_2NRG") condFunct = 0x7C3454; // same as below
		else if (slotType == "COND_3NRT") condFunct = 0x7C3454; // same as above
		else if (slotType == "COND_2NRX") condFunct = 0x7C34BC;
		else if (slotType == "COND_3SSK") condFunct = 0x7C3524;
		else if (slotType == "COND_5TYY") condFunct = 0x7C358C;
		else if (slotType == "COND_5MDR") condFunct = 0x7C35F4;
		else if (slotType == "COND_5KDM") condFunct = 0x7C365C;
		else if (slotType == "COND_BMDR") condFunct = 0x7C36C4;
		else if (slotType == "COND_1KNK") condFunct = 0x7C372C;
		else if (slotType == "COND_2YMT") condFunct = 0x7C3794;
		else if (slotType == "COND_3MDR") condFunct = 0x7C37FC;
		else if (slotType == "COND_5SKN") condFunct = 0x7C3864;
		else if (slotType == "COND_5JRB") condFunct = 0x7C38CC;
		else if (slotType == "COND_7BRX") condFunct = 0x7C3934;
		else if (slotType == "COND_7SKD") condFunct = 0x7C399C;
		else if (slotType == "COND_7YRI") condFunct = 0x7C3A04;
		else if (slotType == "COND_7NRN") condFunct = 0x7C3A6C;
		else if (slotType == "COND_7SSX") condFunct = 0x7C3AD4;
		else if (slotType == "COND_7MMS") condFunct = 0x7C3B3C;
		else if (slotType == "COND_7KIN") condFunct = 0x7C3BA4;
		else if (slotType == "COND_7GAR") condFunct = 0x7C50C4;
		else if (slotType == "COND_7MTK") condFunct = 0x7C3C0C;
		else if (slotType == "COND_8MMS") condFunct = 0x7C3C74;
		else if (slotType == "COND_8KIN") condFunct = 0x7C3CDC;
		else if (slotType == "COND_8KNK") condFunct = 0x7C3D44;
		else if (slotType == "COND_8SIK") condFunct = 0x7C3DAC;
		else if (slotType == "COND_8TYO") condFunct = 0x7C3E14;
		else if (slotType == "COND_BKRL") condFunct = 0x7C3E7C;
		else if (slotType == "COND_BSSN") condFunct = 0x7C3EE4;
		else if (slotType == "COND_BOBT") condFunct = 0x7C3F4C;
		else if (slotType == "COND_BKRS") condFunct = 0x7C3FB4;
		else if (slotType == "COND_B3HS") condFunct = 0x7C401C;
		else if (slotType == "COND_BGKT") condFunct = 0x7C4084;
		else if (slotType == "COND_BAOD") condFunct = 0x7C40EC;
		else if (slotType == "COND_BKTY") condFunct = 0x7C4154;
		else if (slotType == "COND_1JBR") condFunct = 0x7C41BC;
		else if (slotType == "COND_2JBR") condFunct = 0x7C4224;
		else if (slotType == "COND_3JBR") condFunct = 0x7C428C;
		else if (slotType == "COND_4JBR") condFunct = 0x7C42F4;
		else if (slotType == "COND_5JBR") condFunct = 0x7C435C;
		else if (slotType == "COND_6JBR") condFunct = 0x7C43C4;
		else if (slotType == "COND_BJYD") condFunct = 0x7C442C;
		else if (slotType == "COND_GFSA") condFunct = 0x7C4494;
		else if (slotType == "COND_BKKX") condFunct = 0x7C44FC;
		else if (slotType == "COND_B5OB") condFunct = 0x7C4564;
		else if (slotType == "COND_B4NR") condFunct = 0x7C45CC;
		else if (slotType == "COND_B2NR") condFunct = 0x7C4634;
		else if (slotType == "COND_BJB1") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_BJB2") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_BJB3") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_BJB4") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_GFSA") condFunct = 0x7C469C; // same as above
		else if (slotType == "COND_BGRG") condFunct = 0x7C4704;
		else if (slotType == "COND_GZTU") condFunct = 0x7C476C;
		else if (slotType == "COND_BRSK") condFunct = 0x7C47D4;
		else if (slotType == "COND_BKMS") condFunct = 0x7C483C;
		else if (slotType == "COND_BKSR") condFunct = 0x7C48A4;
		else if (slotType == "COND_BOBK") condFunct = 0x7C490C;
		else if (slotType == "COND_BNRX") condFunct = 0x7C4974;
		else if (slotType == "COND_BSSX") condFunct = 0x7C49DC;
		else if (slotType == "COND_BISS") condFunct = 0x7C4A44;
		else if (slotType == "COND_BMNK") condFunct = 0x7C4AAC;
		else if (slotType == "COND_7MMV") condFunct = 0x7C4B14;

		ccCharacterFunctions::c_specialCondFunct.push_back(d3dcompiler_47_og::RecalculateAddress(condFunct));
		ccCharacterFunctions::c_specialCondCodes.push_back(condCharacter);

	}
}

vector<BYTE> ReadAllBytes(string _file)
{
	ifstream f;
	f.open(_file);

	int FileSize = 0;
	while (!f.eof())
	{
		f.get();
		FileSize++;
	}

	f.close();
	f.open(_file, ios::binary);

	std::vector<BYTE> result(FileSize);

	f.seekg(0, ios::beg);

	for (int x = 0; x < FileSize; x++)
	{
		BYTE a = f.get();
		memcpy((void*)&result[0 + x], &a, 1);
	}

	f.close();

	return result;
}

#include "ccGameProperties.h"
#include "ccMemoryFunctions.h"