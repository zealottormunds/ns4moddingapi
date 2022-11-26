#pragma once
#include "Common.h"

class GraphicSettings
{
public:
	int resx;
	int resy;
	int windowed;

	static GraphicSettings * GetResolutionPointer()
	{
		typedef GraphicSettings*(__fastcall * funct)();
		funct fc = (funct)(moduleBase + 0xA43FF0);
		return fc();
	}
};