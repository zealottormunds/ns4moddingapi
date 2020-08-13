#ifndef FILEPARSER_H 
#define FILEPARSER_H
#pragma once

#include <vector>

typedef unsigned char BYTE;

namespace moddingApi
{
	class FileParser
	{
	public:
		static std::vector<BYTE> b_ReadByteArray(std::vector<BYTE> actual, int index, int count);
		static int b_byteArrayToInt(std::vector<BYTE> actual);
		static int b_byteArrayToIntRev(std::vector<BYTE> actual);
		static int b_ReadInt(std::vector<BYTE> fileBytes, int index);
		static int b_ReadIntRev(std::vector<BYTE> fileBytes, int index);
		static float b_ReadFloat(std::vector<BYTE> actual, int index);
		static std::string b_ReadString(std::vector<BYTE> actual, int index, int count = -1);
		static std::vector<BYTE> b_ReplaceBytes(std::vector<BYTE> actual, std::vector<BYTE> bytesToReplace, int Index, int Invert = 0);
		static std::vector<BYTE> b_ReplaceString(std::vector<BYTE> actual, std::string str, int Index, int Count = -1);
		static std::vector<BYTE> b_AddBytes(std::vector<BYTE> actual, std::vector<BYTE> bytesToAdd, int Reverse = 0, int index = 0, int count = -1);
		static std::vector<BYTE> b_AddInt(std::vector<BYTE> actual, int _num);
		static std::vector<BYTE> b_AddString(std::vector<BYTE> actual, std::string _str, int count = -1);
		static std::vector<BYTE> b_AddFloat(std::vector<BYTE> actual, float f);
		static int b_FindBytes(std::vector<BYTE> actual, std::vector<BYTE> bytes, int index = 0);
		static std::vector<int> b_FindBytesList(std::vector<BYTE> actual, std::vector<BYTE> bytes, int index = 0);
		static std::vector<BYTE> ReadAllBytes(std::string _file);
		static std::vector<std::string> ReadAllLines(std::string _file);
		static void WriteAllBytes(char* path, std::vector<BYTE> actual);
	};
}

#endif