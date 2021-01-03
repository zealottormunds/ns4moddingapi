#pragma once

#include <vector>

namespace moddingApi
{
	class Input
	{
	public:
		static void UpdateKeys();
		static bool GetKeyDown(char k);
		static bool GetKey(char k);
		static bool GetKeyUp(char k);
		static bool pressedKeys[0xFF];
		static bool pressedKeysPrev[0xFF];
	};
}