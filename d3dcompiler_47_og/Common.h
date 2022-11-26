#pragma once
extern __int64 moduleBase;
extern __int64 moduleLength;
extern __int64 st_hModule;
extern __int64 datasection;

extern std::string gameVersion;
extern bool isDebug;
extern bool EnableAPI;
extern int PluginState;

class Common
{
public:
	static constexpr unsigned int str2int(const char* str, int h)
	{
		return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
	}

	static __int64 GetQword(__int64 qw)
	{
		__int64 qwr = qw - 0x140000C00;
		return *(__int64*)(moduleBase + qwr);
	}

	// Get a DWORD pointer from the game
	static int GetDword(__int64 dw)
	{
		__int64 dwr = dw - 0x140000C00;
		return *(int*)(moduleBase + dwr);
	}

	// Get an OFFSET pointer from the game
	static __int64 GetOffset(__int64 of)
	{
		__int64 ofr = of - 0xC00 + 0x1000;
		return (moduleBase + ofr);
	}
};