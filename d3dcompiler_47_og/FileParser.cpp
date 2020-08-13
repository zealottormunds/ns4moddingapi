#include "FileParser.h"
#include <sstream>
#include <streambuf>
#include <fstream>
#include <stdint.h>
#include <iostream>
#include <filesystem>

using namespace std;
using namespace moddingApi;

vector<BYTE> FileParser::b_ReadByteArray(vector<BYTE> actual, int index, int count)
{
	vector<BYTE> a = vector<BYTE>();

	for (int x = 0; x < count; x++)
	{
		a.push_back(actual[index + x]);
	}

	return a;
}

int FileParser::b_byteArrayToInt(vector<BYTE> actual)
{
	int a = 0;
	return actual[0] + actual[1] * 256 + actual[2] * 65536 + actual[3] * 16777216;
}

int FileParser::b_byteArrayToIntRev(vector<BYTE> actual)
{
	int a = 0;
	return actual[3] + actual[2] * 256 + actual[1] * 65536 + actual[0] * 16777216;
}

int FileParser::b_ReadInt(vector<BYTE> fileBytes, int index)
{
	return b_byteArrayToInt(b_ReadByteArray(fileBytes, index, 4));
}

int FileParser::b_ReadIntRev(vector<BYTE> fileBytes, int index)
{
	return b_byteArrayToIntRev(b_ReadByteArray(fileBytes, index, 4));
}

float FileParser::b_ReadFloat(vector<BYTE> actual, int index)
{
	BYTE floatBytes[4] = { 0, 0, 0, 0 };

	for (int x = 0; x < 4; x++)
	{
		floatBytes[x] = actual[index + x];
	}

	float * a = (float*)&floatBytes[0];
	return *a;
}

std::string FileParser::b_ReadString(vector<BYTE> actual, int index, int count)
{
	string a = "";
	if (count == -1)
	{
		for (int x2 = index; x2 < actual.size(); x2++)
		{
			if (actual[x2] != 0)
			{
				string str = a;
				char c = (char)actual[x2];
				a = str + c;
			}
			else
			{
				x2 = actual.size();
			}
		}
	}
	else
	{
		for (int x = index; x < count; x++)
		{
			string str2 = a;
			char c = (char)actual[x];
			a = str2 + c;
		}
	}
	return a;
}

vector<BYTE> FileParser::b_ReplaceBytes(vector<BYTE> actual, vector<BYTE> bytesToReplace, int Index, int Invert)
{
	if (Invert == 0)
	{
		for (int x2 = 0; x2 < bytesToReplace.size(); x2++)
		{
			actual[Index + x2] = bytesToReplace[x2];
		}
	}
	else
	{
		for (int x = 0; x < bytesToReplace.size(); x++)
		{
			actual[Index + x] = bytesToReplace[bytesToReplace.size() - 1 - x];
		}
	}
	return actual;
}

vector<BYTE> FileParser::b_ReplaceString(vector<BYTE> actual, string str, int Index, int Count)
{
	if (Count == -1)
	{
		for (int x2 = 0; x2 < str.size(); x2++)
		{
			actual[Index + x2] = (BYTE)str.at(x2);
		}
	}
	else
	{
		for (int x = 0; x < Count; x++)
		{
			if (str.size() > x)
			{
				actual[Index + x] = (BYTE)str.at(x);
			}
			else
			{
				actual[Index + x] = 0;
			}
		}
	}
	return actual;
}

vector<BYTE> FileParser::b_AddBytes(vector<BYTE> actual, vector<BYTE> bytesToAdd, int Reverse, int index, int count)
{
	vector<BYTE> a = actual;

	if (Reverse == 0)
	{
		if (count == -1) count = bytesToAdd.size();
		for (int x = index; x < index + count; x++)
		{
			a.push_back(bytesToAdd[x]);
		}
	}
	else
	{
		if (count == -1) count = bytesToAdd.size();
		for (int x = index; x < index + count; x++)
		{
			a.push_back(bytesToAdd[bytesToAdd.size() - 1 - x]);
		}
	}
	return a;
}

vector<BYTE> FileParser::b_AddInt(vector<BYTE> actual, int _num)
{
	vector<BYTE> a = actual;

	BYTE numb[4] = { 0,0,0,0 };
	memcpy(&numb, &_num, 4);

	for (int x = 0; x < 4; x++)
	{
		a.push_back(numb[x]);
	}
	return a;
}

vector<BYTE> FileParser::b_AddString(vector<BYTE> actual, string _str, int count)
{
	vector<BYTE> a = actual;

	for (int x2 = 0; x2 < _str.length(); x2++)
	{
		a.push_back((BYTE)_str.at(x2));
	}
	for (int x = _str.length(); x < count; x++)
	{
		a.push_back(0);
	}
	return a;
}

vector<BYTE> FileParser::b_AddFloat(vector<BYTE> actual, float f)
{
	vector<BYTE> a = actual;

	BYTE numb[4] = { 0,0,0,0 };
	memcpy(&numb, &f, 4);

	for (int x = 0; x < 4; x++)
	{
		a.push_back(numb[x]);
	}
	return a;
}

int FileParser::b_FindBytes(vector<BYTE> actual, vector<BYTE> bytes, int index)
{
	int actualIndex = index;

	vector<BYTE> actualBytes = vector<BYTE>();
	for (int x = 0; x < bytes.size(); x++) actualBytes.push_back(0);

	bool found = false;
	bool f = false;

	int foundIndex = -1;

	for (int a = actualIndex; a < (actual.size() - bytes.size()); a++)
	{
		f = true;

		for (int x = 0; x < bytes.size(); x++)
		{
			actualBytes[x] = actual[a + x];

			if (actualBytes[x] != bytes[x])
			{
				x = bytes.size();
				f = false;
			}
		}

		if (f)
		{
			found = true;
			foundIndex = a;
			a = actual.size();
		}
	}

	return foundIndex;
}

vector<int> FileParser::b_FindBytesList(vector<BYTE> actual, vector<BYTE> bytes, int index)
{
	int actualIndex = index;
	vector<int> indexes;

	int lastFound = 0;
	while (lastFound != -1)
	{
		lastFound = b_FindBytes(actual, bytes, actualIndex);
		if (lastFound != -1)
		{
			actualIndex = lastFound + 1;
			indexes.push_back(lastFound);
		}
	}

	return indexes;
}

#include <iterator>
vector<BYTE> FileParser::ReadAllBytes(string _file)
{
	ifstream f;
	f.open(_file, ios::binary);

	std::vector<BYTE> result;

	int FileSize = 0;
	while (!f.eof())
	{
		BYTE a = f.get();
		result.push_back(a);
		FileSize++;
	}

	f.close();
	return result;

	/*ifstream f;
	f.open(_file);

	int FileSize = 0;
	while (!f.eof())
	{
		f.get();
		FileSize++;
	}

	f.close();
	f.open(_file, ios::binary);

	std::vector<BYTE> result(FileSize);

	f.seekg(0, ios::beg);

	for (int x = 0; x < FileSize; x++)
	{
		BYTE a = f.get();
		memcpy((void*)&result[0 + x], &a, 1);
	}

	f.close();

	return result;*/
}

vector<string> FileParser::ReadAllLines(string _file)
{
	ifstream f;
	f.open(_file);

	std::vector<string> result;

	while (!f.eof())
	{
		string str;
		std::getline(f, str);
		result.push_back(str);
	}

	f.close();
	return result;
}

void FileParser::WriteAllBytes(char* path, std::vector<BYTE> actual)
{
	ofstream fout;
	fout.open(path, ios::binary | ios::out);
	for (int x = 0; x < actual.size(); x++)
	{
		fout.write((char*)&actual[x], 1);
	}
	fout.close();
}