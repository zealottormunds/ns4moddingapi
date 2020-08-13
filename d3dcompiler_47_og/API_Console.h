#ifndef API_CONSOLE_H 
#define API_CONSOLE_H
#pragma once

#include <vector>

namespace moddingApi
{
	class API_Console
	{
	public:
		static void InitializeConsole();
		static void DoConsoleCommand(std::string cmd);
	};
}

#endif