#pragma once
#include <stdio.h>

namespace moddingApi
{
	class ccMemoryFunctions
	{
	public:
		static uintptr_t TempMalloc(int);
		static void memcpy(void* Dst, void* Source, size_t count);
	};
}