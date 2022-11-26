#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <WinSock2.h>
#include <Windows.h>

#include "Common.h"

class PatchManager
{
public:
	static void ReadPatchFile(std::string _file)
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

		std::string Hex = _file.substr(StartAddress, ExtensionAddress - StartAddress);


		uintptr_t Address = 0;
		try { Address = strtol(Hex.c_str(), NULL, 16); }
		catch(const char* msg){ Address = 0; }

		//if (Address > 0x13B4DAC) Address = Address + 0x400;
		//else if (Address > 0xEAAFAC) Address = Address + 0x400;

		std::ifstream f;
		f.open(_file);

		std::vector<char> replace;
		int count = 0;
		while (!f.eof())
		{
			replace.push_back(f.get());
			count++;
		}

		if (Address != 0x0)
		{
			DoPatch(replace, Address);
		}

		f.close();
	}

	static void DoPatch(std::vector<char> replace, __int64 address)
	{
		int count = replace.size();

		DWORD dwOld = 0;
		VirtualProtect((void*)(moduleBase + address), replace.size(), PAGE_EXECUTE_READWRITE, &dwOld);
		BYTE v[0x1000];
		for (int x = 0; x < count; x++) v[x] = replace[x];

		std::cout << "Patch Manager :: Patched .exe at " << std::hex << address << " (" << std::hex << moduleBase + address << ")" << std::endl;
		memcpy((void*)(moduleBase + address), &v, count - 1);
		VirtualProtect((void*)(moduleBase + address), replace.size(), dwOld, &dwOld);
	}
};