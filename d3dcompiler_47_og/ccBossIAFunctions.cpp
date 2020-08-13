#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ccBossIAFunctions.h"
#include "d3dcompiler_47_og.h"

using namespace moddingApi;
using namespace std;

// BossBattle_StartIaFade
typedef int(__fastcall * bossbattle_startiafade)(uintptr_t);
bossbattle_startiafade g_BossBattle_StartIaFade;

int BossBattle_StartIaFade(uintptr_t a1)
{
	g_BossBattle_StartIaFade = (bossbattle_startiafade)(d3dcompiler_47_og::moduleBase + 0x4700A4);
	return g_BossBattle_StartIaFade(a1);
}

// BossBattle_LoadBossScene
typedef int(__fastcall * bossbattle_loadbossscene)(uintptr_t);
bossbattle_loadbossscene g_BossBattle_LoadBossScene;

int BossBattle_LoadBossScene(uintptr_t sceneName)
{
	g_BossBattle_LoadBossScene = (bossbattle_loadbossscene)(d3dcompiler_47_og::moduleBase + 0x42E154);
	return g_BossBattle_LoadBossScene(sceneName);
}

// [Hook] ccSceneBoss01Phase0Load
int ccBossIAFunctions::ccSceneBoss01Phase0Load(uintptr_t a1)
{
	cout << endl << "Attempted function ccSceneBoss01_Phase0Load" << endl;
	cout << std::hex << a1 << endl;
	cout << "> ";

	BossBattle_StartIaFade(a1);
	char * scene = "ccSceneBoss01_Phase0";
	return BossBattle_LoadBossScene((uintptr_t)&scene);
}

// [Hook] ccSceneBoss01Phase1Load
int ccBossIAFunctions::ccSceneBoss01Phase1Load(uintptr_t a1)
{
	cout << endl << "Attempted function ccSceneBoss01_Phase1Load" << endl;
	cout << std::hex << a1 << endl;
	cout << "> ";

	BossBattle_StartIaFade(a1);
	char * scene = "ccSceneBoss01_Phase1";
	return BossBattle_LoadBossScene((uintptr_t)&scene);
}

// [Hook] ccSceneBoss01Phase4Load
int ccBossIAFunctions::ccSceneBoss01Phase4Load(uintptr_t a1)
{
	cout << endl << "Attempted function ccSceneBoss01_Phase4Load" << endl;
	cout << std::hex << a1 << endl;
	cout << "> ";

	BossBattle_StartIaFade(a1);
	char * scene = "ccSceneBoss01_Phase4";
	return BossBattle_LoadBossScene((uintptr_t)&scene);
}

typedef int(__fastcall * sub00)(__int64);
sub00 Sub00;
typedef __int64(__fastcall * sub01)(__int64, char*, char*);
sub01 Sub01;

// [Hook] Load Madara vs Hashirama SWORD QTE
void ccBossIAFunctions::LoadSwordQTE(uintptr_t a1, char * anmPath, char * anmName)
{
	cout << "Attempting to start QTE..." << endl;
	cout << std::hex << a1 << endl;

	Sub00 = (sub00)(d3dcompiler_47_og::moduleBase + 0x555B14);
	Sub01 = (sub01)(d3dcompiler_47_og::moduleBase + 0x5560C4);

	/*INT64 v3 = a1;

	INT64 *v4;
	v4 = (INT64*)(a1 + 520);

	INT64 result;
	if (*v4)
	{
		Sub00(*v4);
		result = Sub01(*(INT64*)(v3 + 520), anmPath, anmName);
	}*/
}

// Play IA
typedef __int64(__fastcall * ccplayia)(char *);
ccplayia g_ccPlayIA;

__int64 ccBossIAFunctions::ccPlayIA(char * IA)
{
	g_ccPlayIA = (ccplayia)(d3dcompiler_47_og::moduleBase + 0x4E0390);

	return g_ccPlayIA(IA);
}

// ccOpenHudMoney
typedef int(__fastcall * ccopenhudmoney)();
ccopenhudmoney g_ccOpenHudMoney;

int ccBossIAFunctions::ccOpenHudMoney()
{
	g_ccOpenHudMoney = (ccopenhudmoney)(d3dcompiler_47_og::moduleBase + 0x4E00D0);

	return g_ccOpenHudMoney();
}