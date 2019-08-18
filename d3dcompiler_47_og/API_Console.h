#pragma once

#include <vector>

using namespace std;

namespace moddingApi
{
	class API_Console
	{
	public:
		static void InitializeConsole();
		static void DoConsoleCommand(string cmd);
	};
}