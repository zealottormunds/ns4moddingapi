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

using namespace moddingApi;
using namespace std;

int Console_GetInt(char*);
char * Console_GetString(char*);
bool EnableAPI = false;

// Main function of the API
DWORD WINAPI ccMain::Main()
{
	//HookFunctions::InitializeHooks();
	ccMain::ReadApiFiles();
	HookFunctions::InitializeHooks();
	//ccGeneralGameFunctions::CpkLoadList();
	return 0;
}

DWORD WINAPI ccMain::Loop()
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

int ccMain::ModCount = 0;
vector<std::string> ccMain::ModList;
vector<std::string> ccMain::ModDesc;
vector<std::string> ccMain::ModAuth;
vector<BYTE> ccMain::ModState;

// INITIALIZE GAME
typedef uintptr_t(__fastcall * initializegame)(uintptr_t);
initializegame g_InitializeGame;
typedef uintptr_t(__fastcall * initializegame2)(float);
initializegame2 g_InitializeGame2;

// READ MOD FILES
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
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6E1C4A), 1, PAGE_EXECUTE_READWRITE, &dwOld);
			BYTE a = 0;
			memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x6E1C4A), &a, 1);
			VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6E1C4A), 1, dwOld, &dwOld);
		}
		else
		{
			
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

				//cout << "heehee" << endl;

				if (modName != "")
				{
					// Start reading mod files
					vector<string> files;
					for (const auto & f : filesystem::directory_iterator(ModPath))
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

			//cout << ModName << endl;
		}

		cout << "Finished reading mods" << endl;
	}

	//HookFunctions::UndoInitializeHook2();
	//g_InitializeGame = (initializegame)(d3dcompiler_47_og::moduleBase + 0x85175C);
	//g_InitializeGame2 = (initializegame2)(d3dcompiler_47_og::moduleBase + 0x85AE80);

	EnableAPI = true;
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ccMain::Loop, (HMODULE)d3dcompiler_47_og::st_hModule, 0, nullptr);
}

void ccMain::ReloadParamFiles()
{
	/*char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);
	int ActualLength = strlen(ApiPath);

	strcat(ApiPath, "\\moddingapi\\");

	char ConfigPath[_MAX_PATH];
	strcpy(ConfigPath, ApiPath);
	ActualLength = strlen(ConfigPath);
	strcat(ConfigPath, "config.ini");

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
				vector<string> files;

				ccCharacterFunctions::c_partnerCodes.clear();
				ccCharacterFunctions::c_partnerFunctions.clear();
				ccCharacterFunctions::c_specialCondCodes.clear();
				ccCharacterFunctions::c_specialCondFunct.clear();

				for (const auto & f : filesystem::directory_iterator(ModPath))
				{
					string _file = f.path().string();
					string _ext = _file.substr(_file.length() - 4, 4);

					if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "partnerSlotParam.xfbin")
					{
						ReadPartnerSlotParam(_file);
						cout << "Read partner slot..." << endl;
					}
					else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "specialCondParam.xfbin")
					{
						ReadSpecialConditionParam(_file);
						cout << "Read special cond..." << endl;
					}
				}
			}
		}
	}*/

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

	if (Address > 0x13A38AD) Address = Address + 0x1A00;
	else if (Address > 0xEA7420) Address = Address + 0xE00;

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
		//cout << std::hex << d3dcompiler_47_og::moduleBase + Address << endl;
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
				
				if (v1 > 0x13A38AD) v1 = v1 + 0x1A00;
				else if (v1 > 0xEA7420) v1 = v1 + 0xE00;

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

		if (slotType == "PARTNER_TYPE_2PAR") slotFunct = 0x7EAE8C;
		else if (slotType == "PARTNER_TYPE_2KKG") slotFunct = 0x7EAEE4;
		else if (slotType == "PARTNER_TYPE_2AKM") slotFunct = 0x7EAF3C;
		else if (slotType == "PARTNER_TYPE_2KRS") slotFunct = 0x7EAF94;
		else if (slotType == "PARTNER_TYPE_1AKM") slotFunct = 0x7EAFEC;
		else if (slotType == "PARTNER_TYPE_1KRS") slotFunct = 0x7EB044;
		else if (slotType == "PARTNER_TYPE_2SCX") slotFunct = 0x7EB09C;

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

		if (slotType == "COND_2NRT") condFunct = 0x7BE01C;
		else if (slotType == "COND_2SIK") condFunct = 0x7BE084;
		else if (slotType == "COND_2HDN") condFunct = 0x7BE0EC;
		else if (slotType == "COND_2KKS") condFunct = 0x7BE154;
		else if (slotType == "COND_2CYB") condFunct = 0x7BE1BC;
		else if (slotType == "COND_2SCO") condFunct = 0x7BE224;
		else if (slotType == "COND_2DDR") condFunct = 0x7BE28C;
		else if (slotType == "COND_3HNZ") condFunct = 0x7BE2F4;
		else if (slotType == "COND_3TOB") condFunct = 0x7BE35C;
		else if (slotType == "COND_3TYO") condFunct = 0x7BE3C4;
		else if (slotType == "COND_3MDR_2") condFunct = 0x7BE42C;
		else if (slotType == "COND_3KBT") condFunct = 0x7BE494;
		else if (slotType == "COND_2KNK") condFunct = 0x7BE4FC;
		else if (slotType == "COND_2JRY") condFunct = 0x7BE564;
		else if (slotType == "COND_ALL_GAARA") condFunct = 0x7BE5CC;
		else if (slotType == "COND_2ORC") condFunct = 0x7BE634;
		else if (slotType == "COND_5KGY") condFunct = 0x7BE69C;
		else if (slotType == "COND_2FOU") condFunct = 0x7BE704;
		else if (slotType == "COND_2DNZ") condFunct = 0x7BE76C;
		else if (slotType == "COND_3GUY") condFunct = 0x7BE7D4;
		else if (slotType == "COND_2KBT") condFunct = 0x7BE83C;
		else if (slotType == "COND_2MDR") condFunct = 0x7BE8A4;
		else if (slotType == "COND_JKKS") condFunct = 0x7BE90C;
		else if (slotType == "COND_2KIB") condFunct = 0x7BE974;
		else if (slotType == "COND_2KNN") condFunct = 0x7BE9DC;
		else if (slotType == "COND_2SGT") condFunct = 0x7BEA44;
		else if (slotType == "COND_4MKG") condFunct = 0x7BEAAC;
		else if (slotType == "COND_ALL_NARUTO") condFunct = 0x7BEB14;
		else if (slotType == "COND_2NRX") condFunct = 0x7BEB7C;
		else if (slotType == "COND_3SSK") condFunct = 0x7BEBE4;
		else if (slotType == "COND_5TYY") condFunct = 0x7BEC4C;
		else if (slotType == "COND_5MDR") condFunct = 0x7BECB4;
		else if (slotType == "COND_5KDM") condFunct = 0x7BED1C;
		else if (slotType == "COND_BMDR") condFunct = 0x7BED84;
		else if (slotType == "COND_1KNK") condFunct = 0x7BEDEC;
		else if (slotType == "COND_2YMT") condFunct = 0x7BEE54;
		else if (slotType == "COND_3MDR") condFunct = 0x7BEEBC;
		else if (slotType == "COND_5SKN") condFunct = 0x7BEF24;
		else if (slotType == "COND_5JRB") condFunct = 0x7BEF8C;
		else if (slotType == "COND_7BRX") condFunct = 0x7BEFF4;
		else if (slotType == "COND_7SKD") condFunct = 0x7BF05C;
		else if (slotType == "COND_7YRI") condFunct = 0x7BF0C4;
		else if (slotType == "COND_7NRN") condFunct = 0x7BF12C;
		else if (slotType == "COND_7SSX") condFunct = 0x7BF194;
		else if (slotType == "COND_7MMS") condFunct = 0x7BF1FC;
		else if (slotType == "COND_7KIN") condFunct = 0x7BF264;
		else if (slotType == "COND_7MTK") condFunct = 0x7BF2CC;
		else if (slotType == "COND_BKRL") condFunct = 0x7BF334;
		else if (slotType == "COND_BSSN") condFunct = 0x7BF39C;
		else if (slotType == "COND_BOBT") condFunct = 0x7BF404;
		else if (slotType == "COND_BKRS") condFunct = 0x7BF46C;
		else if (slotType == "COND_B3HS") condFunct = 0x7BF4D4;
		else if (slotType == "COND_BGKT") condFunct = 0x7BF53C;
		else if (slotType == "COND_BAOD") condFunct = 0x7BF5A4;
		else if (slotType == "COND_BKTY") condFunct = 0x7BF60C;
		else if (slotType == "COND_1JBR") condFunct = 0x7BF674;
		else if (slotType == "COND_2JBR") condFunct = 0x7BF6DC;
		else if (slotType == "COND_3JBR") condFunct = 0x7BF744;
		else if (slotType == "COND_4JBR") condFunct = 0x7BF7AC;
		else if (slotType == "COND_5JBR") condFunct = 0x7BF814;
		else if (slotType == "COND_6JBR") condFunct = 0x7BF87C;
		else if (slotType == "COND_BJYD") condFunct = 0x7BF8E4;
		else if (slotType == "COND_GFSA") condFunct = 0x7BF94C;
		else if (slotType == "COND_BKKX") condFunct = 0x7BF9B4;
		else if (slotType == "COND_B5OB") condFunct = 0x7BFA1C;
		else if (slotType == "COND_B4NR") condFunct = 0x7BFA84;
		else if (slotType == "COND_B2NR") condFunct = 0x7BFAEC;
		else if (slotType == "COND_ALL_GROUP") condFunct = 0x7BFB54;
		else if (slotType == "COND_BGRG") condFunct = 0x7BFBBC;
		else if (slotType == "COND_GZTU") condFunct = 0x7BFC24;
		else if (slotType == "COND_BRSK") condFunct = 0x7BFC8C;
		else if (slotType == "COND_BKMS") condFunct = 0x7BFCF4;
		else if (slotType == "COND_BKSR") condFunct = 0x7BFD5C;
		else if (slotType == "COND_BOBK") condFunct = 0x7BFDC4;
		else if (slotType == "COND_BNRX") condFunct = 0x7BFE2C;
		else if (slotType == "COND_BSSX") condFunct = 0x7BFE94;
		else if (slotType == "COND_BISS") condFunct = 0x7BFEFC;
		else if (slotType == "COND_BMNK") condFunct = 0x7BFF64;
		else if (slotType == "COND_7MNV") condFunct = 0x7BFFCC;

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