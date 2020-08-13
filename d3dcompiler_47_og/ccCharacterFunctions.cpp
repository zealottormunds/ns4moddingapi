#include <Winsock2.h>
#include <windows.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ccCharacterFunctions.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"

#include <WinSock2.h>
#include <time.h>

using namespace moddingApi;
using namespace std;

int ccCharacterFunctions::test()
{
	return 0;
}

// Character select param

int CharacterSelectParamAPI(uintptr_t a1, uintptr_t charsel);
BYTE OriginalCharacterSelectParam[19];
uintptr_t charsel_1 = -1;
uintptr_t charsel_2 = -1;

typedef int(__fastcall * characterselectparamread)(uintptr_t, uintptr_t);
characterselectparamread CharacterSelectParamRead;
uintptr_t CharacterSelectParamRead_Address = 0x4B3D20;

void ccCharacterFunctions::DoCharacterSelectParamHook()
{
	memcpy(OriginalCharacterSelectParam, (void*)(d3dcompiler_47_og::moduleBase + CharacterSelectParamRead_Address), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + CharacterSelectParamRead_Address), (void*)CharacterSelectParamAPI, 15);
}

void UndoCharacterSelectParamHook()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + CharacterSelectParamRead_Address), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + CharacterSelectParamRead_Address), OriginalCharacterSelectParam, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + CharacterSelectParamRead_Address), 15, dwOld, &dwOld);
}

int CharacterSelectParamAPI(uintptr_t a1, uintptr_t charsel)
{
	charsel_1 = a1;
	charsel_2 = charsel;

	cout << std::hex << charsel_1 << endl;
	cout << std::hex << charsel_2 << endl;

	UndoCharacterSelectParamHook();
	CharacterSelectParamRead = (characterselectparamread)(d3dcompiler_47_og::moduleBase + CharacterSelectParamRead_Address);
	int a = CharacterSelectParamRead(a1, charsel);
	ccCharacterFunctions::DoCharacterSelectParamHook();

	return a;
}

void ccCharacterFunctions::ReloadCharsel()
{
	if (charsel_1 != -1 && charsel_2 != -1)
	{
		CharacterSelectParamRead = (characterselectparamread)(d3dcompiler_47_og::moduleBase + CharacterSelectParamRead_Address);
		CharacterSelectParamRead(charsel_1, charsel_2);
		cout << "Charsel reloaded successfully" << endl;
	}
	else
	{
		cout << "Cannot reload charsel" << endl;
	}
}

// PARTNER FUNCTIONS
uintptr_t partnerAlloc = 0;
vector<uintptr_t> ccCharacterFunctions::c_partnerFunctions;
vector<int> ccCharacterFunctions::c_partnerCodes;
void ccCharacterFunctions::PartnerFunctions()
{
	vector<uintptr_t> partnerFunctions = ccCharacterFunctions::c_partnerFunctions;
	vector<int> partnerCodes = ccCharacterFunctions::c_partnerCodes;
	int PartnerCount = partnerFunctions.size();

	BYTE function[] = { 0x33, 0xC9, 0x48, 0x8D, 0x05, 0x9B, 0x2B, 0x8C, 0x00, 0x3B, 0x10,
						0x74, 0x15, 0x4C, 0x8D, 0x05, 0x00, 0x2C, 0x8C, 0x00, 0x48, 0x83,
						0xC0, 0x10, 0xFF, 0xC1, 0x49, 0x3B, 0xC0, 0x7C, 0xEA, 0x33, 0xC0,
						0xC3, 0x48, 0x63, 0xC1, 0x48, 0x8D, 0x0D, 0x70, 0x2B, 0x8C, 0x00,
						0x48, 0x03, 0xC0, 0x48, 0xFF, 0x24, 0xC1,
						0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // 51, jmp qword ptr [$+6]
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // 57

	uintptr_t main_malloc = (uintptr_t)VirtualAlloc(0, 65 + (PartnerCount * 0x10), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	uintptr_t char_functions = main_malloc + 65;
	uintptr_t char_codes = main_malloc + 65 + 8;
	uintptr_t char_funct_end = main_malloc + 65 + (PartnerCount * 0x10);

	int char_codes_rip = char_codes - (main_malloc + 2 + 7);
	int char_funct_end_rip = char_funct_end - (main_malloc + 20);
	int char_functions_rip = char_functions - (main_malloc + 44);

	uintptr_t jump_to = d3dcompiler_47_og::moduleBase + 0x7EEBEB;

	void * writeAddress = &function[0];

	memcpy((void*)(&function[0] + 5), (void*)&char_codes_rip, sizeof(int));
	memcpy((void*)(&function[0] + 16), (void*)&char_funct_end_rip, 4);
	memcpy((void*)(&function[0] + 40), (void*)&char_functions_rip, 4);
	memcpy((void*)(&function[0] + 57), (void*)&jump_to, 8);

	memcpy((void*)main_malloc, (void*)&function, 65);

	DWORD dwOld = 0;
	VirtualProtect((void*)main_malloc, 65, PAGE_EXECUTE_READWRITE, &dwOld);

	for (int x = 0; x < PartnerCount; x++)
	{
		memcpy((void*)(char_functions + (x * 0x10)), (void*)(&partnerFunctions[x]), 8);
		memcpy((void*)(char_functions + (x * 0x10) + 0x8), (void*)(&partnerCodes[x]), 4);
	}

	// Hook original function to jump to our function
	if(partnerAlloc == 0) HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7EEBB8), (void*)main_malloc, 14);
	else
	{
		// Fix address for reload
		uintptr_t placeJump = d3dcompiler_47_og::moduleBase + 0x7EEBB8;

		DWORD dwOld = 0;
		VirtualProtect((void*)placeJump, 14, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(placeJump + 6), (void*)&main_malloc, 8);
		VirtualProtect((void*)placeJump, 14, dwOld, &dwOld);
	}

	// Free old piece of code (if there was one)
	//if (partnerAlloc != 0) free((void*)partnerAlloc);
	partnerAlloc = main_malloc;
}

// SPECIAL CONDITIONS
uintptr_t condAlloc = 0;
vector<uintptr_t> ccCharacterFunctions::c_specialCondFunct;
vector<int> ccCharacterFunctions::c_specialCondCodes;
void ccCharacterFunctions::SpecialCondFunctions()
{
	//CustomConditionCreate();

	BYTE function[] = { 0x48, 0x8D, 0x05, 0x48 + 14, 0x00, 0x00, 0x00,

						0x3B, 0x38,
						0x0F, 0x84, 0x1D, 0x00, 0x00, 0x00,
						0x48, 0x8D, 0x0D, 0xFF, 0xFF, 0xFF, 0x00, // add 14
						0x48, 0x83, 0xC0, 0x10,
						0xFF, 0xC3,
						0x48, 0x3B, 0xC1,
						0x7C, 0xE6,
						0xFF, 0x15, 0x20 + 14, 0x00, 0x00, 0x00,
						0xE9, 0x10, 0x00, 0x00, 0x00,

						0x48, 0x63, 0xC3,
						0x48, 0x8D, 0x0D, 0x11 + 14, 0x00, 0x00, 0x00,
						0x48, 0x03, 0xC0,
						0xFF, 0x14, 0xC1,

						0x48, 0x8B, 0x5C, 0x24, 0x30,
						0x48, 0x83, 0xC4, 0x20,
						0x5F,
						0xC3,
	
						0xCC, 0xCC, 0x90, 0x90, 0x90, 0x90, // jmp qword ptr [$+6]
						0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	int funcsize = 0x55;

	vector<uintptr_t> condFunct = ccCharacterFunctions::c_specialCondFunct;
	vector<int> condCodes = ccCharacterFunctions::c_specialCondCodes;

	int conditionCount = condFunct.size();
	int totalSize = (funcsize) + (conditionCount * 0x10) + (0x8);

	uintptr_t main_malloc = (uintptr_t)VirtualAlloc(0, totalSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	uintptr_t specialCondFunct = main_malloc + funcsize;
	uintptr_t specialCondCodes = main_malloc + funcsize + 0x8;
	uintptr_t end = main_malloc + totalSize;

	void * writeAddress = &function[0];

	int lea_rip_address = 0x31 + (conditionCount * 0x10) + 0x8 + 14;
	memcpy((void*)(&function[0] + 0x12), &lea_rip_address, 0x4); // fix the lea with rip + address (points to the end of the condition list)

	// create jump back
	uintptr_t jback = d3dcompiler_47_og::moduleBase + 0x7C4651;
	memcpy((void*)(&function[0] + 0x4E), &jback, 8);

	// Copy function to memory, and make executable
	memcpy((void*)main_malloc, (void*)&function, funcsize);
	DWORD dwOld = 0;
	VirtualProtect((void*)main_malloc, funcsize, PAGE_EXECUTE_READWRITE, &dwOld);

	//cout << "Executable: " << std::hex << main_malloc << " to " << std::hex << (main_malloc + funcsize);

	for (int x = 0; x < conditionCount; x++)
	{
		memcpy((void*)(specialCondFunct + (x * 0x10)), (void*)(&condFunct[x]), 8);
		memcpy((void*)(specialCondCodes + (x * 0x10)), (void*)(&condCodes[x]), 4);
	}

	// Hook original function
	if(condAlloc == 0) HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7C3891), (void*)main_malloc, 15);
	else
	{
		// Fix address for reload
		uintptr_t placeJump = d3dcompiler_47_og::moduleBase + 0x7C3891;

		DWORD dwOld = 0;
		VirtualProtect((void*)placeJump, 14, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(placeJump + 6), (void*)&main_malloc, 8);
		VirtualProtect((void*)placeJump, 14, dwOld, &dwOld);
	}

	//cout << "Function: " << std::hex << (uintptr_t)(d3dcompiler_47_og::moduleBase + 0x7C3891) << endl;
	//cout << "main_malloc = " << std::hex << main_malloc << endl;

	// Free old piece of code (if there was one)
	//if (condAlloc != 0) free((void*)condAlloc);
	condAlloc = main_malloc;
}

// COND_BKKX FOR COOP
vector<uintptr_t> ccCharacterFunctions::charPointer;
vector<long long> ccCharacterFunctions::charAllocTime;
void Unhook_COND_BKKX();
uintptr_t asd = 0x6B0E4C;
typedef signed __int64(__fastcall * test)(uintptr_t a1, uintptr_t a2);
test Test1;
BYTE originalasd[20];

signed __int64 COND_BKKX(uintptr_t cptr, uintptr_t a2)
{
	if (ccCharacterFunctions::charAllocTime.size() > 0)
	{
		time_t timeInSec_;
		time(&timeInSec_);
		if ((long long)timeInSec_ - ccCharacterFunctions::charAllocTime[0] > 5)
		{
			ccCharacterFunctions::charPointer.clear();
			ccCharacterFunctions::charAllocTime.clear();
		}
	}
	else
	{
		//cout << "no elements in alloc time" << endl;
	}

	ccCharacterFunctions::charPointer.push_back(cptr);
	time_t timeInSec;
	time(&timeInSec);
	ccCharacterFunctions::charAllocTime.push_back((long long)timeInSec);

	Test1 = (test)(d3dcompiler_47_og::moduleBase + asd);
	cout << "CHR #" << ccCharacterFunctions::charPointer.size() << ": " << std::hex << cptr << endl;
	Unhook_COND_BKKX();
	signed __int64 result = Test1(cptr, a2);
	ccCharacterFunctions::Hook_COND_BKKX();

	return result;
	//cout << std::hex << cptr << endl;
}

void ccCharacterFunctions::Hook_COND_BKKX()
{
	memcpy(originalasd, (void*)(d3dcompiler_47_og::moduleBase + 0x6B0E4C), 15);
	HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x6B0E4C), (void*)COND_BKKX, 15);
}

void Unhook_COND_BKKX()
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6B0E4C), 15, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy((void*)(d3dcompiler_47_og::moduleBase + 0x6B0E4C), originalasd, 15);
	VirtualProtect((void*)(d3dcompiler_47_og::moduleBase + 0x6B0E4C), 15, dwOld, &dwOld);
}

void ccCharacterFunctions::EnableControl(int character, int pad)
{
	DWORD dwOld = 0;
	VirtualProtect((void*)(ccCharacterFunctions::charPointer[character] + 0xB40), 8, PAGE_EXECUTE_READWRITE, &dwOld);

	BYTE oldBytes[8] = {
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character]),
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character] + 0xB40 + 1),
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character] + 0xB40 + 2),
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character] + 0xB40 + 3),
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character] + 0xB40 + 4),
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character] + 0xB40 + 5),
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character] + 0xB40 + 6),
		(BYTE)(BYTE*)(ccCharacterFunctions::charPointer[character] + 0xB40 + 7),
	};

	bool replace = false;
	for (int x = 0; x < 8; x++) if (oldBytes[x] != 0) replace = true;

	BYTE newBytes[8] = { 0,0,0,0,0,0,0,0 };
	memcpy((void*)(ccCharacterFunctions::charPointer[character] + 0xB40), newBytes, 8);

	if(replace == false)
	{
		cout << "Char " << character << " is already a player." << endl;
	}

	VirtualProtect((void*)(ccCharacterFunctions::charPointer[character] + 0xB40), 8, dwOld, &dwOld);

	if (replace)
	{
		VirtualProtect((void*)(ccCharacterFunctions::charPointer[character] + 0x840), 1, PAGE_EXECUTE_READWRITE, &dwOld);
		BYTE newbyte[1] = { 0 };
		
		switch (pad)
		{
		case 0:
			newbyte[0] = 0;
			break;
		case 1:
			newbyte[0] = 1;
			break;
		case 2:
			newbyte[0] = 2;
			break;
		case 3:
			newbyte[0] = 3;
			break;
		}

		memcpy((void*)(ccCharacterFunctions::charPointer[character] + 0x840), newbyte, 1);
		VirtualProtect((void*)(ccCharacterFunctions::charPointer[character] + 0x840), 1, dwOld, &dwOld);

		cout << "Char " << character << " is now being controlled by pad " << pad << endl;
	}
}