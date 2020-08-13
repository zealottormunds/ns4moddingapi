#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Vector3.h"
#include "PlayerScript.h"
#include "Savefile.h"
#include "FileParser.h"

#include <WinSock2.h>
#include <Windows.h>

using namespace std;
using namespace moddingApi;

bool Savefile::isRpgMode = false;
string Savefile::username = "Zealot";
int Savefile::health = 100;
int Savefile::chakra = 100;
int Savefile::ryo = 0;

int Savefile::torsocount = 2;
int Savefile::bottomcount = 2;
int Savefile::actualtorso = 0;
int Savefile::actualbottom = 0;

vector<std::byte> AddInt(vector<std::byte> f, int value);
vector<std::byte> AddFloat(vector<std::byte> f, float value);
vector<std::byte> AddString(vector<std::byte> f, std::string value);

int ReadInt(char* f, int index);
char* ReadString(char* f, int index);
float ReadFloat(char* f, int index);

string Savefile::GetRootPath()
{
	char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);

	return string((char*)ApiPath[0]);
}

bool Savefile::FileExists(std::string file)
{
	ifstream f(file.c_str());
	return f.good();
}

void Savefile::Save()
{
	/*vector<std::byte> fileBytes;

	// Save status
	fileBytes = AddInt(fileBytes, Savefile::health);
	fileBytes = AddInt(fileBytes, Savefile::ryo);
	fileBytes = AddString(fileBytes, Savefile::username);

	// Save position
	fileBytes = AddFloat(fileBytes, PlayerScript::pl.playerObject.transform.position.x);
	fileBytes = AddFloat(fileBytes, PlayerScript::pl.playerObject.transform.position.y);
	fileBytes = AddFloat(fileBytes, PlayerScript::pl.playerObject.transform.position.z);*/

	int usernameLen = Savefile::username.length();

	PlayerScript* pl = (PlayerScript*)(PlayerScript::pl);

	void* fileBytes = malloc(24 + Savefile::username.length());
	memcpy((void*)((uintptr_t)fileBytes + 0x0), &Savefile::health, 4);
	memcpy((void*)((uintptr_t)fileBytes + 0x4), &Savefile::ryo, 4);
	memcpy((void*)((uintptr_t)fileBytes + 0x8), &usernameLen, 4);
	memcpy((void*)((uintptr_t)fileBytes + 0xC), (void*)(Savefile::username.c_str()), usernameLen);
	memcpy((void*)((uintptr_t)fileBytes + 0xC + usernameLen), &(pl->playerObject->transform->position->x), 4);
	memcpy((void*)((uintptr_t)fileBytes + 0x10 + usernameLen), &(pl->playerObject->transform->position->y), 4);
	memcpy((void*)((uintptr_t)fileBytes + 0x14 + usernameLen), &(pl->playerObject->transform->position->z), 4);

	char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);
	int ActualLength = strlen(ApiPath);

	strcat(ApiPath, "\\uns_stories\\savefile_000.zts");
	remove(ApiPath);

	ofstream file;
	file.open(ApiPath);
	file.clear();

	file.write((char*)fileBytes, 24 + Savefile::username.length());
	file.close();
}

void Savefile::Load()
{
	/*char ApiPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, ApiPath);
	int ActualLength = strlen(ApiPath);

	strcat(ApiPath, "\\shinobistory\\savefile_000.zts");
	//remove(ApiPath);
	char* fileBytes = ReadAllBytes(ApiPath);
	Savefile::health = ReadInt(fileBytes, 0);
	Savefile::ryo = ReadInt(fileBytes, 4);
	Savefile::username = ReadString(fileBytes, 8);*/
}

vector<std::byte> AddInt(vector<std::byte> f, int value)
{
	vector<std::byte> file = f;

	unsigned char bytes[4];

	bytes[0] = (unsigned char)value & 0xFF;
	bytes[1] = (unsigned char)((value >> 8) & 0xFF);
	bytes[2] = (unsigned char)((value >> 16) & 0xFF);
	bytes[3] = (unsigned char)((value >> 24) & 0xFF);

	for (int x = 0; x < 4; x++)
	{
		file.push_back((std::byte)bytes[x]);
	}

	return file;
}

vector<std::byte> AddFloat(vector<std::byte> f, float value)
{
	vector<std::byte> file = f;

	unsigned char bytes[4];

	/*bytes[0] = (unsigned char)value & 0xFF;
	bytes[1] = (unsigned char)((value >> 8) & 0xFF);
	bytes[2] = (unsigned char)((value >> 16) & 0xFF);
	bytes[3] = (unsigned char)((value >> 24) & 0xFF);*/

	memcpy(&bytes[0], &value, 4);

	for (int x = 0; x < 4; x++)
	{
		file.push_back((std::byte)bytes[x]);
	}

	return file;
}

vector<std::byte> AddString(vector<std::byte> f, std::string value)
{
	vector<std::byte> file = f;

	int len = value.length();
	file = AddInt(file, len);

	for (int x = 0; x < len; x++)
	{
		file.push_back(f[len]);
	}

	return file;
}

int ReadInt(char* f, int index)
{
	int x = 0;

	x = (f[index] * 0x1) + (f[index + 1] * 0x100) + (f[index + 2] * 0x10000) + (f[index + 3] * 0x1000000);

	return x;
}

char* ReadString(char* f, int index)
{
	int len = ReadInt(f, index);
	char* st = (char*)(malloc(len));
	memcpy(st, &f[index + 4], len);
	return st;
}

float ReadFloat(char* f, int index)
{
	float floatnum = 0;
	memcpy(&floatnum, &f[index], 4);
	return floatnum;
}