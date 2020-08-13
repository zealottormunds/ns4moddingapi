#include <stdint.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "XfbinParser.h"
#include "FileParser.h"

using namespace std;
using namespace moddingApi;

int XfbinParser::HeaderSize = 0x44;

std::vector<BYTE> XfbinParser::GetHeader(std::vector<BYTE> fileBytes)
{
	return FileParser::b_ReadByteArray(fileBytes, 0, HeaderSize);
}

int XfbinParser::GetNuccSectionIndex()
{
	return HeaderSize;
}

int XfbinParser::GetNuccSectionSize(std::vector<BYTE> fileBytes)
{
	return FileParser::b_byteArrayToIntRev(FileParser::b_ReadByteArray(fileBytes, 0x20, 4));
}

int XfbinParser::GetPathSectionIndex(std::vector<BYTE> fileBytes)
{
	return GetNuccSectionIndex() + GetNuccSectionSize(fileBytes);
}

int XfbinParser::GetPathSectionSize(std::vector<BYTE> fileBytes)
{
	return FileParser::b_byteArrayToIntRev(FileParser::b_ReadByteArray(fileBytes, 0x28, 4));
}

int XfbinParser::GetPathCount(std::vector<BYTE> fileBytes)
{
	return FileParser::b_byteArrayToIntRev(FileParser::b_ReadByteArray(fileBytes, 0x24, 4)) - 1;
}

std::vector<std::string> XfbinParser::GetPathList(std::vector<BYTE> fileBytes)
{
	vector<string> pathList;

	int pathCount = GetPathCount(fileBytes);
	int index = GetPathSectionIndex(fileBytes) + 1;

	for (int x = 0; x < pathCount; x++)
	{
		string actualPath = FileParser::b_ReadString(fileBytes, index);
		pathList.push_back(actualPath);
		index = index + actualPath.size() + 1;
	}

	return pathList;
}

int XfbinParser::GetNameSectionIndex(std::vector<BYTE> fileBytes)
{
	return GetPathSectionIndex(fileBytes) + GetPathSectionSize(fileBytes);
}

int XfbinParser::GetNameSectionSize(std::vector<BYTE> fileBytes)
{
	return FileParser::b_byteArrayToIntRev(FileParser::b_ReadByteArray(fileBytes, 0x30, 4));
}

std::vector<std::string> XfbinParser::GetNameList(std::vector<BYTE> fileBytes)
{
	vector<string> nameList;

	int nameCount = GetPathCount(fileBytes);
	int index = GetNameSectionIndex(fileBytes) + 1;

	for (int x = 0; x < nameCount; x++)
	{
		string actualName = FileParser::b_ReadString(fileBytes, index);
		nameList.push_back(actualName);
		index = index + actualName.size() + 1;
	}

	return nameList;
}

int XfbinParser::GetBin1SectionIndex(std::vector<BYTE> fileBytes)
{
	int ind = GetNameSectionIndex(fileBytes) + GetNameSectionSize(fileBytes);
	while (ind % 4 != 0) ind++;
	return ind;
}

int XfbinParser::GetBin1SectionSize(std::vector<BYTE> fileBytes)
{
	return FileParser::b_byteArrayToIntRev(FileParser::b_ReadByteArray(fileBytes, 0x38, 0x4));
}

int XfbinParser::GetBin2SectionIndex(std::vector<BYTE> fileBytes)
{
	int ind = GetBin1SectionIndex(fileBytes) + GetBin1SectionSize(fileBytes);
	return ind;
}

int XfbinParser::GetBin2SectionSize(std::vector<BYTE> fileBytes)
{
	return GetPathCount(fileBytes) * 0x10;
}

int XfbinParser::GetFileSectionIndex(std::vector<BYTE> fileBytes)
{
	return GetBin2SectionIndex(fileBytes) + GetBin2SectionSize(fileBytes);
}

std::vector<BYTE> XfbinParser::WriteStringSection(std::vector<std::string> strings)
{
	vector<BYTE> actual;

	vector<BYTE> zero = { 0 };
	for (int x = 0; x < strings.size(); x++)
	{
		actual = FileParser::b_AddBytes(actual, zero);
		actual = FileParser::b_AddString(actual, strings[x]);
		actual = FileParser::b_AddBytes(actual, zero);
	}

	return actual;
}