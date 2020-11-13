#pragma once

#include <stdio.h>
#include <windows.h>
#include "Vector3.h"

namespace moddingApi
{
	class ccPlayerStruct
	{
	public:
		// THIS CODE IS PRETTY USELESS AT THE MOMENT!

		ccPlayerStruct(uintptr_t p, uintptr_t s)
		{
			posx = (float*)(p + 0x70);
			posz = (float*)(p + 0x74);
			posy = (float*)(p + 0x78);

			chakra = (float*)(p + 0x08);
		}

		float *posx;
		float *posz;
		float *posy;
		float *chakra;
	};
}