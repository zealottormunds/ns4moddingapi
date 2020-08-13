#ifndef XFBINPARSER_H 
#define XFBINPARSER_H
#pragma once

#include <vector>

typedef unsigned char BYTE;

namespace moddingApi
{
	class XfbinParser
	{
	public:
		static int HeaderSize;
		static std::vector<BYTE> GetHeader(std::vector<BYTE> fileBytes);
		static int GetNuccSectionIndex();
		static int GetNuccSectionSize(std::vector<BYTE> fileBytes);
		static int GetPathSectionIndex(std::vector<BYTE> fileBytes);
		static int GetPathSectionSize(std::vector<BYTE> fileBytes);
		static int GetPathCount(std::vector<BYTE> fileBytes);
		static std::vector<std::string> GetPathList(std::vector<BYTE> fileBytes);
		static int GetNameSectionIndex(std::vector<BYTE> fileBytes);
		static int GetNameSectionSize(std::vector<BYTE> fileBytes);
		static std::vector<std::string> GetNameList(std::vector<BYTE> fileBytes);
		static int GetBin1SectionIndex(std::vector<BYTE> fileBytes);
		static int GetBin1SectionSize(std::vector<BYTE> fileBytes);
		static int GetBin2SectionIndex(std::vector<BYTE> fileBytes);
		static int GetBin2SectionSize(std::vector<BYTE> fileBytes);
		static int GetFileSectionIndex(std::vector<BYTE> fileBytes);
		static std::vector<BYTE> WriteStringSection(std::vector<std::string> strings);
	};
}

#endif