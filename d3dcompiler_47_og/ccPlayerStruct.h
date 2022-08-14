#ifndef PLAYERSTRUCT_H 
#define PLAYERSTRUCT_H
#pragma once

class ccPlayerStruct
{
public:
	// THIS CODE IS PRETTY USELESS AT THE MOMENT!

	ccPlayerStruct(__int64 p, __int64 s)
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

#endif