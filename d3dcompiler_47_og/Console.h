#ifndef CONSOLE_H 
#define CONSOLE_H
#pragma once

#include <vector>

class Console
{
public:
	static void InitializeConsole();
	static void DoConsoleCommand(std::string cmd);
	static void RestartConsole();
};

#endif