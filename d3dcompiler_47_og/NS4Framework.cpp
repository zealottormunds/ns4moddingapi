#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "NS4Framework.h"

#include "Common.h"
#include "PatternScan.h"
#include "FileParser.h"

#include "ModManager.h"
#include "MessageManager.h"
#include "PatchManager.h"
#include "PartnerManager.h"
#include "SpecialConditionManager.h"

#include "Console.h"
#include "HookFunctions.h"
#include "CpkLoader.h"

std::vector<Mod*> ModManager::modList;
std::vector<ExtensionManager::Extension*> ExtensionManager::extensionList;
std::vector<MessageManager::Message*> MessageManager::messageList;

bool EnableAPI = false;
int PluginState = -1;

using namespace std;

int __stdcall NS4Framework::Main()
{
	NS4Framework::ReadFrameworkFiles();

	// Read current version
	long long versionText = PatternScan::Scan("646c632f25640000312e30");
	if (versionText != 0)
	{
		char * version = (char*)(versionText + 8);
		cout << "NS4Framework :: Detected game version: " << version << endl;

		gameVersion = std::string(version);
	}
	else
	{
		cout << "NS4Framework :: Game version not detected" << endl;
	}

	// Initialize the function hooks
	HookFunctions::InitializeHooks();

	// Enable API
	EnableAPI = true;

	// Enable game and console threads
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)NS4Framework::LoopGame, (HMODULE)st_hModule, 0, nullptr);
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)NS4Framework::LoopConsole, (HMODULE)st_hModule, 0, nullptr);

	return 1;
}

void NS4Framework::ReadFrameworkFiles(bool isReloading)
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
		cout << "NS4Framework :: Config file not found, using default values." << endl;
		//return;
	}
	else
	{
		// When the API is initialized the first time
		if (isReloading == false)
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

				cout << "====== STORM FRAMEWORK MODDING CONSOLE ======" << endl;
			}

			if (GetPrivateProfileInt("General", "EnableModList", 1, ConfigPath) == 1 && false)
			{
				DWORD dwOld = 0;

				__int64 eula = PatternScan::Scan("48xxxx48xxxxxx33xx48xxxx74xx48xxxx8DxxxxFFxx48xxxxxx80xxxxxxxxxxxx75xxC7xxxxxxxxxxxxxxxxxxC7xxxxxxxxxxxxC7xxxxxxxxxxxxEBxx48xxxxxxxxxxxx41xxxxxxxxxxB9xxxxxxxxE8xxxxxxxx48xxxx");
				if (eula > 0)
				{
					VirtualProtect((void*)(eula + 0x20), 1, PAGE_EXECUTE_READWRITE, &dwOld);
					BYTE a = 2;
					memcpy((void*)(eula + 0x20), &a, 1);
					VirtualProtect((void*)(eula + 0x20), 1, dwOld, &dwOld);
				}
				else
				{
					cout << "NS4Framework :: Eula window unavailable in current version. Mod list will not be shown." << endl;
				}
			}

			cout << "NS4Framework :: Config finished" << endl;
		}

		PartnerManager::InitialScan();

		// Start reading mods
		strcat(ApiPath, "mods\\");

		std::vector<std::string> modFolders;

		// Read plugins first
		for (const auto & entry : filesystem::directory_iterator(ApiPath))
		{
			std::string s = entry.path().string();

			char FolderName[100];
			int StartIndex = strlen(ApiPath);
			int Count = s.length() - StartIndex;

			strncpy(FolderName, &s[StartIndex], 100);

			std::string ModPath = (std::string)(ApiPath) + (std::string)(FolderName);
			std::string InfoPath = ModPath + "\\info.txt";

			string modName = "";
			string modDesc = "";
			string modAuth = "";
			string modState = "";

			if (ModPath.find(".") == string::npos)
			{
				if (filesystem::exists(InfoPath) == true)
				{
					modFolders.push_back(ModPath);
					std::vector<std::string> fileLines = FileParser::ReadAllLines(InfoPath);

					int lineCount = fileLines.size();

					if (lineCount == 0) modName = "[name_error]";
					if (lineCount >= 1) modName = fileLines[0];
					if (lineCount >= 2) modDesc = fileLines[1];
					if (lineCount >= 3) modAuth = fileLines[2];
					if (lineCount >= 4) modState = fileLines[3];

					if (modName != "" && modState != "disable")
					{
						Mod * actualMod = new Mod(modName, modAuth, modDesc, FolderName);
						ModManager::AddMod(actualMod);

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
									cout << "NS4Framework :: Error loading plugin " << _file.c_str() << ": ERROR CODE " << std::dec << GetLastError() << endl;
								}
								else
								{
									Plugin* actualPlugin = new Plugin();
									string name = string(FolderName) + "/" + filesystem::path(_file).filename().string();
									actualPlugin->pluginPath = std::string(a);
									actualPlugin->pluginName = name;

									actualMod->pluginList.push_back(actualPlugin);
									actualPlugin->hInstance = (__int64)(hGetProcIDDLL);
									cout << "NS4Framework :: Loading plugin " << name << endl;

									// InitializePlugin
									typedef void(__stdcall *funct)(__int64 moduleBase, std::vector<__int64> deprecated);
									funct InitializePlugin = (funct)GetProcAddress(hGetProcIDDLL, "InitializePlugin");
									std::vector<__int64> a;
									if (InitializePlugin) InitializePlugin(moduleBase, a);
									else cout << "NS4Framework :: InitializePlugin() function not found" << endl;

									// Get GameLoop
									funct functloop = (funct)GetProcAddress(hGetProcIDDLL, "GameLoop");
									if (functloop) actualPlugin->gameLoop = (__int64)functloop;

									// Get AfterBoot
									funct functafterboot = (funct)GetProcAddress(hGetProcIDDLL, "AfterBoot");
									if (functafterboot) actualPlugin->afterBoot = (__int64)functafterboot;

									// Get Unload
									funct functunload = (funct)GetProcAddress(hGetProcIDDLL, "Unload");
									if (functunload) actualPlugin->unload = (__int64)functunload;

									// Get ParseFile
									funct functparsefile = (funct)GetProcAddress(hGetProcIDDLL, "ParseFile");
									if (functparsefile) actualPlugin->fileParser = (__int64)functparsefile;

									// Get Extensions
									typedef std::vector<std::string>*(__stdcall * extfunct)();
									extfunct GetExtensions = (extfunct)GetProcAddress(hGetProcIDDLL, "ExtensionList");

									if (GetExtensions)
									{
										std::vector<std::string> extList = *(std::vector<std::string>*)(GetExtensions());

										int extCount = extList.size();
										for (int actualExt = 0; actualExt < extCount; actualExt++)
										{
											std::string ext = extList[actualExt];
											bool hasExt = ExtensionManager::HasExtension(ext);

											if (hasExt == false)
											{
												ExtensionManager::AddExtension(ext, actualPlugin);
												std::cout << "NS4Framework :: Adding parser for extension \"." << ext << "\"" << std::endl;
											}
										}
									}

									// Get PreRender
									funct functprerender = (funct)GetProcAddress(hGetProcIDDLL, "PreRender");
									if (functprerender) actualPlugin->prerender = (__int64)functprerender;

									// Get OnGUI
									funct functpostrender = (funct)GetProcAddress(hGetProcIDDLL, "PostRender");
									if (functpostrender) actualPlugin->postrender = (__int64)functpostrender;

									// Get PostRender
									funct functongui = (funct)GetProcAddress(hGetProcIDDLL, "OnGUI");
									if (functongui) actualPlugin->ongui = (__int64)functongui;
								}
							}
						}
					}
				}
			}
		}

		// Read files (ns4p, ns4s, other extensions managed by plugins)
		int folders = modFolders.size();
		for (int actualFolder = 0; actualFolder < folders; actualFolder++)
		{
			std::string ModPath = modFolders[actualFolder];

			for (const auto & f : filesystem::directory_iterator(ModPath))
			{
				Mod * actualMod = ModManager::GetModList()[actualFolder];
				std::string modName = actualMod->path;

				string _file = f.path().string();
				if (_file.find("_noload_") == std::string::npos)
				{
					int extIndex = _file.find_last_of(".") + 1;
					int extLength = _file.size() - extIndex;
					string _ext = _file.substr(extIndex, extLength);
					Plugin * pluginToParse = ExtensionManager::GetExtensionParser(_ext);

					if (pluginToParse != nullptr)
					{
						typedef bool(__stdcall *filefunct)(std::string path, vector<BYTE> file);
						filefunct parseFileExtension = (filefunct)pluginToParse->fileParser;

						if (parseFileExtension) parseFileExtension(_file, FileParser::ReadAllBytes(_file));
					}
					else
					{
						if (_ext == "ns4s")
						{
							MessageManager::ParseMessageFile(_file);
						}
						else if (_ext == "ns4p")
						{
							PatchManager::ReadPatchFile(_file);
						}
						else if (_ext == "ns4e")
						{
							std::cout << "NS4Framework :: ns4e files are deprecated" << std::endl;
							//ReadScriptFile(_file);
						}
						else if (_ext == "cpk")
						{
							string cpkinfo = filesystem::path(_file).replace_extension("cpk.info").string();

							if (filesystem::exists(cpkinfo))
							{
								vector<BYTE> fileBytes1 = FileParser::ReadAllBytes(cpkinfo);
								int priority = fileBytes1[0] + (fileBytes1[1] * 0x100) + (fileBytes1[2] * 0x10000) + (fileBytes1[3] * 0x1000000);

								cout << "CpkLoader :: Priority set for cpk " << modName << "/" << filesystem::path(_file).filename() << " to " << std::dec << priority << "." << endl;
								string cpkpath = "moddingapi/mods/" + modName + "/" + filesystem::path(_file).filename().string();
								char* a = new char[cpkpath.length() + 1];
								strcpy(a, cpkpath.c_str());
								CpkLoader::CpkToLoad.push_back(a);
								CpkLoader::CpkPriority.push_back(priority);
							}
							else
							{
								cout << "CpkLoader :: Info file for cpk " << modName << "/" << filesystem::path(_file).filename() << " was not found. Setting priority to default (13)." << endl;
								string cpkpath = "moddingapi/mods/" + modName + "/" + filesystem::path(_file).filename().string();
								char* a = new char[cpkpath.length() + 1];
								strcpy(a, cpkpath.c_str());
								CpkLoader::CpkToLoad.push_back(a);
								CpkLoader::CpkPriority.push_back(13);
							}
						}
						else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "partnerSlotParam.xfbin")
						{
							PartnerManager::ReadPartnerSlotParam(_file);
						}
						else if (_file.length() > 0x16 && _file.substr(_file.length() - 0x16, 0x16) == "specialCondParam.xfbin")
						{
							SpecialConditionManager::ReadSpecialConditionParam(_file);
						}
						else
						{
							//std::cout << "Ignoring extension " << _ext << std::endl;
						}
					}
				}
			}
		}

		PluginState = 1;
		cout << "NS4Framework :: Finished reading mods" << endl;
	}
}

int __stdcall NS4Framework::LoopGame()
{
	while (true)
	{
		Update();
		Sleep(1);
	}
	return 0;
}

int __stdcall NS4Framework::LoopConsole()
{
	while (EnableAPI == false)
	{
		Sleep(100);
	}

	Console::InitializeConsole();

	while (EnableAPI)
	{
		std::string cmd;
		cout << "> ";
		cin >> cmd;

		Console::DoConsoleCommand(cmd);

		Sleep(100);
	}

	return 0;
}

#include "DirectX.h"
bool doneDX = false;
void NS4Framework::Update()
{
	if (!EnableAPI) return;

	// Do d3d hook
	if (DirectX::isHookDone == false)
	{
		//std::cout << "DirectX :: Attempting hook..." << std::endl;
		__int64 swapChain = DirectX::GetSwapChain();
		if (swapChain) DirectX::HookVtable(swapChain);
	}

	std::vector<Mod*> modList = ModManager::GetModList();
	int modCount = modList.size();

	for (int x = 0; x < modCount; x++)
	{
		Mod* m = modList[x];
		if (m) m->Update();
	}
}

void NS4Framework::PreRender()
{
	if (!EnableAPI) return;

	std::vector<Mod*> modList = ModManager::GetModList();
	int modCount = modList.size();

	for (int x = 0; x < modCount; x++)
	{
		Mod* m = modList[x];
		if(m) m->PreRender();
	}
}

void NS4Framework::PostRender()
{
	if (!EnableAPI) return;

	std::vector<Mod*> modList = ModManager::GetModList();
	int modCount = modList.size();

	for (int x = 0; x < modCount; x++)
	{
		Mod* m = modList[x];
		if (m) m->PostRender();
	}
}

void NS4Framework::OnGUI(bool s, __int64 hwnd, __int64 imguiContext)
{
	if (!EnableAPI) return;

	std::vector<Mod*> modList = ModManager::GetModList();
	int modCount = modList.size();

	for (int x = 0; x < modCount; x++)
	{
		Mod* m = modList[x];
		if (m) m->OnGUI(s, hwnd, imguiContext);
	}
}

/*void NS4Framework::UnloadPlugins()
{
	cout << "PluginSystem :: Unloading plugins..." << endl;

	for (int x = 0; x < PluginList.size(); x++)
	{
		Sleep(10);
		FreeLibrary(PluginList[x]);
	}

	PluginList.clear();
	PluginLoop.clear();

	cout << "Pluginsystem :: Plugins unloaded correctly" << endl;
}*/