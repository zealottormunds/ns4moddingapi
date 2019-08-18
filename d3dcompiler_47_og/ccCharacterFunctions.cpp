#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ccCharacterFunctions.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"

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

	uintptr_t jump_to = d3dcompiler_47_og::moduleBase + 0x7EB257;

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
	if(partnerAlloc == 0) HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7EB224), (void*)main_malloc, 14);
	else
	{
		// Fix address for reload
		uintptr_t placeJump = d3dcompiler_47_og::moduleBase + 0x7EB224;

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
	uintptr_t jback = d3dcompiler_47_og::moduleBase + 0x7C106D;
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
	if(condAlloc == 0) HookFunctions::Hook((void*)(d3dcompiler_47_og::moduleBase + 0x7C02AD), (void*)main_malloc, 15);
	else
	{
		// Fix address for reload
		uintptr_t placeJump = d3dcompiler_47_og::moduleBase + 0x7C02AD;

		DWORD dwOld = 0;
		VirtualProtect((void*)placeJump, 14, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(placeJump + 6), (void*)&main_malloc, 8);
		VirtualProtect((void*)placeJump, 14, dwOld, &dwOld);
	}

	//cout << "Function: " << std::hex << (uintptr_t)(d3dcompiler_47_og::moduleBase + 0x7C02AD) << endl;
	//cout << "main_malloc = " << std::hex << main_malloc << endl;

	// Free old piece of code (if there was one)
	//if (condAlloc != 0) free((void*)condAlloc);
	condAlloc = main_malloc;
}