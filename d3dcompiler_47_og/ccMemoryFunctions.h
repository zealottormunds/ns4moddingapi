#ifndef MEMFUNCTIONS_H 
#define MEMFUNCTIONS_H
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

#endif