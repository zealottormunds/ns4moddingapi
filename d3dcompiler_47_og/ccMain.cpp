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
#include "ccCharacterFunctions.h"
#include "ccBossIAFunctions.h"
#include "HookFunctions.h"
#include "ccPlayer.h"
#include "Memory.h"
using namespace moddingApi;
using namespace std;
using namespace std::experimental;

int Console_GetInt(char*);
char * Console_GetString(char*);
bool EnableAPI = false;

void ReadCpk();

DWORD WINAPI ccMain::Main()
{
	// Read all the mods and configs
	ccMain::ReadApiFiles();
	//Establishes Memory
	External::Memory memory = External::Memory("NSUNS4.exe");
	cout << "Memory Established";
	// Initialize the function hooks
	HookFunctions::InitializeHooks();

	// Enable API
	EnableAPI = true;

	// Read CPK
	ReadCpk();

	// Enable the game thread (this is for player modification in game)
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ccMain::LoopGame, (HMODULE)d3dcompiler_47_og::st_hModule, 0, nullptr);

	// Loop console
	ccMain::LoopConsole();

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
DWORD WINAPI ccMain::LoopGame()
{
	while (true)
	{
		ccPlayer::Loop();
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
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6E3C0A), 1, PAGE_EXECUTE_READWRITE, &dwOld);
			BYTE a = 0;
			memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x6E3C0A), &a, 1);
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6E3C0A), 1, dwOld, &dwOld);
		}

		cout << "Config finished..." << endl;

		// Start reading mods
		strcat(ApiPath, "mods\\");

		for (const auto & entry : std::filesystem::directory_iterator(ApiPath))
		{
			std::string s = entry.path().string();

			char ModName[100];
			int StartIndex = strlen(ApiPath);
			int Count = s.length() - StartIndex;

			strncpy(ModName, &s[StartIndex], 100);

			std::string ModPath = (std::string)(ApiPath) + (std::string)(ModName);
			std::string InfoPath = ModPath + "\\info.txt";

			//cout << InfoPath << endl;

			if (std::filesystem::exists(InfoPath) == true)
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
					// Start reading mod files
					vector<string> files;
					for (const auto & f : std::filesystem::directory_iterator(ModPath))
					{
						string _file = f.path().string();
						string _ext = _file.substr(_file.length() - 4, 4);

						if (_ext == "ns4s")
						{
							//cout << "Message file" << endl;
							vector<string> msg = ReadMessageFile(_file);

							for (int x = 0; x + 1 < msg.size(); x = x + 2)
							{
								//cout << "Added Message ID: " << msg[x] << endl;
								ccGeneralGameFunctions::MessageID.push_back(msg[x]);
								ccGeneralGameFunctions::MessageStr.push_back(msg[x + 1]);
							}
						}
						else if (_ext == "ns4p")
						{
							//cout << "Patch file" << endl;
							ReadPatchFile(_file);
						}
						else if (_ext == "ns4e")
						{
							ReadScriptFile(_file);
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

	for (const auto & entry : std::filesystem::directory_iterator(ApiPath))
	{
		std::string s = entry.path().string();

		char ModName[100];
		int StartIndex = strlen(ApiPath);
		int Count = s.length() - StartIndex;

		strncpy(ModName, &s[StartIndex], 100);

		std::string ModPath = (std::string)(ApiPath) + (std::string)(ModName);
		std::string InfoPath = ModPath + "\\info.txt";

		//cout << InfoPath << endl;

		if (std::filesystem::exists(InfoPath) == true)
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
				for (const auto & f : std::filesystem::directory_iterator(ModPath))
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

vector<BYTE> ReadAllBytes(string);

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

		if (slotType == "PARTNER_TYPE_2PAR") slotFunct = 0x7EE7C8;
		else if (slotType == "PARTNER_TYPE_2KKG") slotFunct = 0x7EE820;
		else if (slotType == "PARTNER_TYPE_2AKM") slotFunct = 0x7EE878;
		else if (slotType == "PARTNER_TYPE_2KRS") slotFunct = 0x7EE8D0;
		else if (slotType == "PARTNER_TYPE_1AKM") slotFunct = 0x7EE928;
		else if (slotType == "PARTNER_TYPE_1KRS") slotFunct = 0x7EE980;
		else if (slotType == "PARTNER_TYPE_2SCX") slotFunct = 0x7EE9D8;
		else if (slotType == "PARTNER_TYPE_8AEM") slotFunct = 0x7EEA30;

		ccCharacterFunctions::c_partnerFunctions.push_back(d3dcompiler_47_og::RecalculateAddress(slotFunct));
		ccCharacterFunctions::c_partnerCodes.push_back(slotCharacter);

		//cout << "CharacterType = " << slotType.c_str() << ", Chara = " << std::hex << slotCharacter << endl;
	}
}

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

		//cout << "stuff: " << std::hex << (uintptr_t)fileBytes[actual] << " " << (uintptr_t)fileBytes[actual + 1] << endl;
		condCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);

		uintptr_t condFunct = 0x0;

		if (slotType == "COND_1CMN") condFunct = 0x7C2C58;
		else if (slotType == "COND_2SIK") condFunct = 0x7C2CC0;
		else if (slotType == "COND_2HDN") condFunct = 0x7C2D28;
		else if (slotType == "COND_2KKS") condFunct = 0x7C2D90;
		else if (slotType == "COND_2CYB") condFunct = 0x7C2DF8;
		else if (slotType == "COND_2SCO") condFunct = 0x7C2E60;
		else if (slotType == "COND_2DDR") condFunct = 0x7C2EC8;
		else if (slotType == "COND_3HNZ") condFunct = 0x7C2F30;
		else if (slotType == "COND_3TOB") condFunct = 0x7C2F98;
		else if (slotType == "COND_3TYO") condFunct = 0x7C3000;
		else if (slotType == "COND_3MDR_2") condFunct = 0x7C3068;
		else if (slotType == "COND_3KBT") condFunct = 0x7C30D0;
		else if (slotType == "COND_2KNK") condFunct = 0x7C3138;
		else if (slotType == "COND_2JRY") condFunct = 0x7C31A0;
		else if (slotType == "COND_3GAR") condFunct = 0x7C3208;
		else if (slotType == "COND_2GAV") condFunct = 0x7C3208;
		else if (slotType == "COND_2ORC") condFunct = 0x7C3270;
		else if (slotType == "COND_5KGY") condFunct = 0x7C32D8;
		else if (slotType == "COND_2FOU") condFunct = 0x7C3340;
		else if (slotType == "COND_2DNZ") condFunct = 0x7C33A8;
		else if (slotType == "COND_3GUY") condFunct = 0x7C3410;
		else if (slotType == "COND_2KBT") condFunct = 0x7C3478;
		else if (slotType == "COND_2MDR") condFunct = 0x7C34E0;
		else if (slotType == "COND_JKKS") condFunct = 0x7C3548;
		else if (slotType == "COND_2KIB") condFunct = 0x7C35B0;
		else if (slotType == "COND_2KNN") condFunct = 0x7C1460;
		else if (slotType == "COND_2SGT") condFunct = 0x7C14C8;
		else if (slotType == "COND_4MKG") condFunct = 0x7C1530;
		else if (slotType == "COND_2NRT") condFunct = 0x7C1598;
		else if (slotType == "COND_2NRG") condFunct = 0x7C1598;
		else if (slotType == "COND_3NRT") condFunct = 0x7C1598;
		else if (slotType == "COND_2NRX") condFunct = 0x7C1600;
		else if (slotType == "COND_3SSK") condFunct = 0x7C1668;
		else if (slotType == "COND_5TYY") condFunct = 0x7C16D0;
		else if (slotType == "COND_5MDR") condFunct = 0x7C1738;
		else if (slotType == "COND_5KDM") condFunct = 0x7C17A0;
		else if (slotType == "COND_BMDR") condFunct = 0x7C1808;
		else if (slotType == "COND_1KNK") condFunct = 0x7C1870;
		else if (slotType == "COND_2YMT") condFunct = 0x7C18D8;
		else if (slotType == "COND_3MDR") condFunct = 0x7C1940;
		else if (slotType == "COND_5SKN") condFunct = 0x7C19A8;
		else if (slotType == "COND_5JRB") condFunct = 0x7C1A10;
		else if (slotType == "COND_7BRX") condFunct = 0x7C1A78;
		else if (slotType == "COND_7SKD") condFunct = 0x7C1AE0;
		else if (slotType == "COND_7YRI") condFunct = 0x7C1B48;
		else if (slotType == "COND_7NRN") condFunct = 0x7C1BB0;
		else if (slotType == "COND_7SSX") condFunct = 0x7C1C18;
		else if (slotType == "COND_7MMS") condFunct = 0x7C1C80;
		else if (slotType == "COND_7KIN") condFunct = 0x7C1CE8;
		else if (slotType == "COND_7GAR") condFunct = 0x7C3208;
		else if (slotType == "COND_7MTK") condFunct = 0x7C1D50;
		else if (slotType == "COND_8MMS") condFunct = 0x7C1DB8;
		else if (slotType == "COND_8KIN") condFunct = 0x7C1E20;
		else if (slotType == "COND_8KNK") condFunct = 0x7C1E88;
		else if (slotType == "COND_8SIK") condFunct = 0x7C1EF0;
		else if (slotType == "COND_8TYO") condFunct = 0x7C3000;
		else if (slotType == "COND_BKRL") condFunct = 0x7C1F58;
		else if (slotType == "COND_BSSN") condFunct = 0x7C1FC0;
		else if (slotType == "COND_BOBT") condFunct = 0x7C2028;
		else if (slotType == "COND_BKRS") condFunct = 0x7C2090;
		else if (slotType == "COND_B3HS") condFunct = 0x7C20F8;
		else if (slotType == "COND_BGKT") condFunct = 0x7C2160;
		else if (slotType == "COND_BAOD") condFunct = 0x7C21C8;
		else if (slotType == "COND_BKTY") condFunct = 0x7C2230;
		else if (slotType == "COND_1JBR") condFunct = 0x7C2298;
		else if (slotType == "COND_2JBR") condFunct = 0x7C2300;
		else if (slotType == "COND_3JBR") condFunct = 0x7C2368;
		else if (slotType == "COND_4JBR") condFunct = 0x7C23D0;
		else if (slotType == "COND_5JBR") condFunct = 0x7C2438;
		else if (slotType == "COND_6JBR") condFunct = 0x7C24A0;
		else if (slotType == "COND_BJYD") condFunct = 0x7C2508;
		else if (slotType == "COND_GFSA") condFunct = 0x7C2570;
		else if (slotType == "COND_BKKX") condFunct = 0x7C25D8;
		else if (slotType == "COND_B5OB") condFunct = 0x7C2640;
		else if (slotType == "COND_B4NR") condFunct = 0x7C26A8;
		else if (slotType == "COND_B2NR") condFunct = 0x7C2710;
		else if (slotType == "COND_BJB1") condFunct = 0x7C2778;
		else if (slotType == "COND_BJB2") condFunct = 0x7C2778;
		else if (slotType == "COND_BJB3") condFunct = 0x7C2778;
		else if (slotType == "COND_BJB4") condFunct = 0x7C2778;
		else if (slotType == "COND_GFSA") condFunct = 0x7C2778;
		else if (slotType == "COND_BGRG") condFunct = 0x7C27E0;
		else if (slotType == "COND_GZTU") condFunct = 0x7C2848;
		else if (slotType == "COND_BRSK") condFunct = 0x7C28B0;
		else if (slotType == "COND_BKMS") condFunct = 0x7C2918;
		else if (slotType == "COND_BKSR") condFunct = 0x7C2980;
		else if (slotType == "COND_BOBK") condFunct = 0x7C29E8;
		else if (slotType == "COND_BNRX") condFunct = 0x7C2A50;
		else if (slotType == "COND_BSSX") condFunct = 0x7C2AB8;
		else if (slotType == "COND_BISS") condFunct = 0x7C2B20;
		else if (slotType == "COND_BMNK") condFunct = 0x7C2B88;
		else if (slotType == "COND_7MMV") condFunct = 0x7C2BF0;

		ccCharacterFunctions::c_specialCondFunct.push_back(d3dcompiler_47_og::RecalculateAddress(condFunct));
		ccCharacterFunctions::c_specialCondCodes.push_back(condCharacter);

		//cout << "CharacterType = " << slotType.c_str() << ", Chara = " << std::hex << condCharacter << endl;
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

	//cout << _file.c_str() << endl;
	std::vector<BYTE> result(FileSize);

	f.seekg(0, ios::beg);

	for (int x = 0; x < FileSize; x++)
	{
		BYTE a = f.get();
		memcpy((void*)&result[0 + x], &a, 1);
	}

	//f.read(&result[0], FileSize);

	f.close();

	return result;
}

#include "ccGameProperties.h"
#include "ccMemoryFunctions.h"
void ReadCpk()
{
	BYTE cpkCount = 6;

	char* cpkList[] =
	{
		"sim:data/launch/data1.cpk",
		"sim:data/launch/stage1.cpk",
		"disc:data/launch/dataRegion.cpk",
		"sim:data/launch/sound.cpk",
		"disc:data/launch/adx2.cpk",
		"disc:data/launch/movie1.cpk",
		"sim:data/launch/test.cpk"
	};

	void* cpkMode1v = malloc(8);
	BYTE cpkMode1[] =
	{
		0x01, 0x00, 0x00, 0x00, 0xF6, 0x7F, 0x00, 0x00
	};
	memcpy(cpkMode1v, &cpkMode1[0], 8);

	void* cpkMode2v = malloc(8);
	BYTE cpkMode2[] =
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	memcpy(cpkMode2v, &cpkMode2[0], 8);

	void* cpkMode3v = malloc(8);
	BYTE cpkMode3[] =
	{
		0x00, 0x00, 0x00, 0x00, 0xF6, 0x7F, 0x00, 0x00
	};
	memcpy(cpkMode3v, &cpkMode3[0], 8);

	void* cpkMode4v = malloc(8);
	BYTE cpkMode4[] =
	{
		0x00, 0x00, 0x00, 0x00, 0x53, 0x00, 0x00, 0x00
	};
	memcpy(cpkMode4v, &cpkMode4[0], 8);

	void* arrayMalloc = malloc(0x10 * cpkCount);
	
	for (int x = 0; x < cpkCount; x++)
	{
		void* actual = (void*)((__int64)arrayMalloc + (x * 0x10));
		memcpy(actual, &cpkList[x], 0x8);
	}

	cout << "Address: " << std::hex << arrayMalloc << endl;

	// This will be placed in the game exe, 0x853D6B
	BYTE jmp_[]
	{
		0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // 0x0
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x90 // 0x6
	};

	void* jmp = VirtualAlloc(0, 14, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(jmp, &jmp_[0], 14);

	// This is the function that will get executed
	BYTE function_[]{
		0x48, 0x8D, 0x1D, 0x13, 0x00, 0x00, 0x00, // 0x0, mov rbx, [rip+0x13]
		0xBF, cpkCount, 0x00, 0x00, 0x00, // 0x7, mov edi, 6
		0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // 0xC, jmp
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x12, back to 0x853DC8
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x1A
	};

	void *function = VirtualAlloc(0, 34 + (cpkCount * 0x10) - 0x10, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(function, &function_[0], 34);

	// Paste function address in jmp
	memcpy((void*)((_int64)jmp + 0x6), &function, 8);

	// Calculate jmp back
	__int64 back = d3dcompiler_47_og::moduleBase + 0x853DC8;

	// Paste jmp back in function + 0x12
	memcpy((void*)((__int64)function + 0x12), &back, 8);

	// Paste address of strings in function + 0x1A
	for (int x = 0; x < cpkCount; x++)
	{
		memcpy((void*)((__int64)function + 0x1A + (x * 0x10)), (void*)((__int64)arrayMalloc + (x * 0x10)), 8);

		switch (x)
		{
		case 0:
		case 1:
		case 2:
			memcpy((void*)((__int64)function + 0x1A + (x * 0x10) + 0x8), cpkMode1v, 8);
			break;
		case 3:
			memcpy((void*)((__int64)function + 0x1A + (x * 0x10) + 0x8), cpkMode2v, 8);
			break;
		case 4:
			memcpy((void*)((__int64)function + 0x1A + (x * 0x10) + 0x8), cpkMode3v, 8);
			break;
		case 5:
			memcpy((void*)((__int64)function + 0x1A + (x * 0x10) + 0x8), cpkMode4v, 8);
			break;
		case 6:
		case 7:
		case 8:
			memcpy((void*)((__int64)function + 0x1A + (x * 0x10) + 0x8), cpkMode4v, 8);
			break;
		}
	}

	// Make executable memory
	DWORD dwOld = 0;
	VirtualProtect(function, 34, PAGE_EXECUTE_READWRITE, &dwOld);

	// Paste jmp in original function
	void* test = malloc(1);
	BYTE test1 = 0x48;
	memcpy(test, &test1, 1);

	void * oriFunct = (void*)(d3dcompiler_47_og::moduleBase + 0x853D6B);

	DWORD dwOld1 = 0;
	VirtualProtect(oriFunct, 15, PAGE_EXECUTE_READWRITE, &dwOld1);
	//memcpy(oriFunct, jmp, 15); // DISABLE CPK READ
	VirtualProtect(oriFunct, 15, dwOld1, &dwOld1);
	//ccMemoryFunctions::memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x853D6B), test, 1);

	cout << "stuff" << endl;
	cout << std::hex << (__int64)(jmp) << endl;
	cout << std::hex << (__int64)(function) << endl;
}