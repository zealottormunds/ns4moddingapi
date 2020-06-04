#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ccMemoryFunctions.h"
#include "d3dcompiler_47_og.h"

using namespace moddingApi;
using namespace std;

typedef uintptr_t(__fastcall * tempmalloc)(int);
tempmalloc g_TempMalloc;

uintptr_t ccMemoryFunctions::TempMalloc(int Size)
{
	g_TempMalloc = (tempmalloc)(d3dcompiler_47_og::moduleBase + 0x9FC880);
	return g_TempMalloc(Size);
}

void ccMemoryFunctions::memcpy(void* Dst, void* Source, size_t count)
{
	DWORD dwOld = 0;
	VirtualProtect(Dst, count, PAGE_EXECUTE_READWRITE, &dwOld);
	//memcpy(Dst, Source, count);
	VirtualProtect(Dst, count, dwOld, &dwOld);
}