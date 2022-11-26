#include "PatternScan.h"
#include <vector>
#include <iostream>

#include "Common.h"

// I got this specific char2int function from somewhere, but I can't remember rn. Credits will be added when I find who made it lol
char char2int(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	throw std::invalid_argument("Invalid input string");
}

__int64 PatternScan::Scan(std::string pattern, __int64 startIndex, bool backwards)
{
	int totalBytes = (pattern.length() + 1) / 2;

	std::vector<char> bytes;
	std::vector<bool> isbyte;

	for (int x = 0; x < totalBytes; x++)
	{
		int index = x * 2;
		if (pattern.at(index) != 'x')
		{
			bytes.push_back(char2int(pattern.at(index)) * 0x10 + char2int(pattern.at(index + 1)));
			isbyte.push_back(true);
		}
		else
		{
			bytes.push_back(0);
			isbyte.push_back(false);
		}
	}

	//std::cout << "Searching for: ";
	//for (int x = 0; x < totalBytes; x++) std::cout << std::hex << bytes.at(x);
	//std::cout << std::endl;

	__int64 address = 0;
	bool found = false;

	__int64 base = moduleBase - 0xC00;
	if (startIndex != 0) base = startIndex;

	__int64 total = moduleBase + moduleLength - 0xC00 - totalBytes;

	if (backwards == false)
	{
		for (__int64 x = base; x < total; x++)
		{
			bool isCorrect = true;
			for (int y = 0; y < totalBytes; y++)
			{
				isCorrect &= isbyte[y] == false || bytes[y] == *(char*)(x + y);
				if (isCorrect == false) y = totalBytes;
			}

			if (isCorrect)
			{
				address = x;
				found = true;
				x = total;
			}
		}
	}
	else
	{
		for (__int64 x = startIndex; x >= moduleBase; x--)
		{
			bool isCorrect = true;
			for (int y = 0; y < totalBytes; y++)
			{
				isCorrect = (isbyte[y] == false || bytes[y] == *(char*)(x + y));
				if (isCorrect == false) y = totalBytes;
			}

			if (isCorrect)
			{
				address = x;
				found = true;
				x = moduleBase;
			}
		}
	}

	/*if (found)
		std::cout << "Pattern was found at " << std::hex << address << std::endl;
	else
		std::cout << "Pattern was not found" << std::endl;*/

	return address;
}
