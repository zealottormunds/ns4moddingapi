#ifndef CCGAMEPROPERTIES_H 
#define CCGAMEPROPERTIES_H
#pragma once

#include <stdio.h>
#include <string>

namespace moddingApi
{
	class ccGameProperties
	{
	public:
		static int isOnBattle();
		static int isOnMenu();
		static std::string GetActiveWindowTitle();

		static int __fastcall lua_pcallk(void* a1, int a2, int a3, int a4);
		static int __fastcall lua_getfield(void* a1, int idx, const char *k);
		static int __fastcall luaL_loadfile(void* a1, char* file);
		static int __fastcall lua_gettop(void* a1);
		static int __fastcall lua_call(void* a1, int a2, int a3);

		static int __fastcall menugamefunction(__int64 a1);

		//static int __fastcall luaB_dofile(lua_State* L);
		static __int64 LState;
		static __int64 LStateGame;
		static void ExecuteLuaInitial();
		static void ExecuteLuaFunction(char* funct);
		static void ExecuteLuaFile(char* path);
		static void* GetLuaState();
		static int GetProperty(char* prop);

		static void UpdateTiming();
		static float LastSavedTime;
		static float ActualSavedTime;
		static float GetCurrentGameTime();
		static float GetDeltaTime();

		static __int64 GetQword(__int64 qw);
		static int GetDword(__int64 dw);
		static __int64 GetOffset(__int64 of);

		static constexpr unsigned int str2int(const char* str, int h = 0);

		static void DoGamePropertiesHook();
		static uintptr_t GlobalPointer;
		static void ReloadProperties();

		static void DoInitHook();
		static uintptr_t InitMemory;
		static void ReloadInit();

		static void DoAutoSaveHook();
		static void ccLoadScene(std::string);

		static __int64 loadCpk(__int64 a1);

		static __int64 temp_malloc_00(size_t a1, char* str);
		static __int64 spawnmenu(__int64 a1, char* str);
		static int setupmenu(__int64 window, int **a2, char **options, int a4, int a5, int a6);
		static int setupmenusimple(__int64 a1, char* a2, int a3);
		static int setuptitle(__int64 w, char* title, int a3);
		static int funct1(); // 6A27A0
		static int funct2(__int64 a1, __int64 a2);
		static int funct3(__int64 a1);
		static int funct4(__int64 a1);

		static __int64 playanm(char* a1, char* a2);
		static __int64 playanm2(__int64 a1, char* a2, char* a3);
		static __int64 playanm15(__int64 a1, __int64 a2, int a3, int a4, __int64 a45, int a5, int a6);

		static __int64 * __fastcall forsceneloading(__int64 a1);

		static __int64 __fastcall flashmalloc(__int64 a1);
		static __int64 __fastcall msgbox(__int64 a1, char* scenename);
		static __int64 __fastcall msgbox2(__int64 a1, char* a2, __int64 a3);
	};
}

#endif