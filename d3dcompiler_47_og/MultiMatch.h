#pragma once

#include <vector>

namespace moddingApi
{
	class MultiMatch
	{
	public:
		static int p_BaseStock[4];
		static int p_UsedStock[4];
		static char* p_Chars[4];

		static int ccInitializeMultiMatch(__int64 a1);
		static int ccMultiMatchCameraLoop();
		static int ccMultiMatchShowPlayerStatus(__int64 a1);

		static __int64 fc_GetGpPtr();
	};
}