#pragma once

#include <stdio.h>
using namespace std;

namespace moddingApi
{
	class ccGameProperties
	{
	public:
		static void DoGamePropertiesHook();
		static uintptr_t GlobalPointer;
		static void ReloadProperties();

		static void DoInitHook();
		static uintptr_t InitMemory;
		static void ReloadInit();

		static void DoAutoSaveHook();
		static void ccLoadScene(std::string);
	};
}