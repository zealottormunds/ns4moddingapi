#include "GameSettings.h"
#include "d3dcompiler_47_og.h"
#include "ccGameProperties.h"
#include <iostream>
#include <vector>
#pragma warning( disable: 4307 )

using namespace std;
using namespace moddingApi;

vector<const char*> GameSettings::CpkToLoad;
vector<int> GameSettings::CpkPriority;

int moddingApi::GameSettings::LoadCpkInitial()
{
	__int64 v0; // rax@1
	__int64 v1; // rbx@1
	unsigned int ActualVersion; // eax@3
	unsigned int GameVersion; // ebx@3
	__int64 v4; // rbx@5
	signed __int64 v5; // rdi@5
	const char *v6; // rax@10
	void *v7; // rdx@13
	void *v8; // rbx@16
	int v9; // eax@16
	//const char *v11; // [sp+20h] [bp-188h]@12
	//int v12; // [sp+28h] [bp-180h]@12
	void *Memory; // [sp+30h] [bp-178h]@5
	int v14; // [sp+38h] [bp-170h]@5
	const char *v15; // [sp+40h] [bp-168h]@5
	unsigned __int64 v16; // [sp+48h] [bp-160h]@5
	const char *v17; // [sp+50h] [bp-158h]@5
	int v18; // [sp+58h] [bp-150h]@5
	const char *v19; // [sp+60h] [bp-148h]@5
	int v20; // [sp+68h] [bp-140h]@5
	const char *v21; // [sp+70h] [bp-138h]@5
	int v22; // [sp+78h] [bp-130h]@5
	const char *v23; // [sp+80h] [bp-128h]@5
	int v24; // [sp+88h] [bp-120h]@5
	__int64 *v25; // [sp+90h] [bp-118h]@4
	signed int v26; // [sp+98h] [bp-110h]@4
	__int64 v27; // [sp+A0h] [bp-108h]@4
	__int64 retaddr; // [sp+1A8h] [bp+0h]@1

	v0 = (__int64)&retaddr;
	v1 = ccGameProperties::GetQword(0x1416663C8);
	if (!v1) return v0;

	if (ccGameProperties::GetDword(0x1415F8244) != 1)
	{
		// 0x1CD368 addstring to buffer
		typedef signed __int64(__fastcall * fc_AddStringToBuffer)(__int64 a, __int64 b);
		fc_AddStringToBuffer AddStringToBuffer = (fc_AddStringToBuffer)(d3dcompiler_47_og::moduleBase + 0x1CD368);
		AddStringToBuffer((__int64)&Memory, ccGameProperties::GetOffset(0x1557E58));
		v7 = &Memory;

		if (v16 >= 0x10)
			v7 = Memory;

		// 0xA470F0
		typedef int(__fastcall * sub_140A47CF0)(__int64 a, __int64 b);
		sub_140A47CF0 sub_140A47CF0_f = (sub_140A47CF0)(d3dcompiler_47_og::moduleBase + 0xA470F0);
		v0 = sub_140A47CF0_f(v1, (__int64)v7);

		if (v16 >= 0x10)
		{
			v8 = Memory;

			typedef int(__fastcall * sub_140A01D60)(__int64 a);
			sub_140A01D60 sub_140A01D60_f = (sub_140A01D60)(d3dcompiler_47_og::moduleBase + 0xA01160);
			v9 = sub_140A01D60_f((__int64)&v17);

			// 0xA01080
			typedef signed __int64(__fastcall * nuccMemoryType__Function01)(__int64 a);
			nuccMemoryType__Function01 nuccMemoryType__Function01_f = (nuccMemoryType__Function01)(d3dcompiler_47_og::moduleBase + 0xA01080);
			nuccMemoryType__Function01(v9);

			// 0xA00EA0
			typedef void(__fastcall * sub_140A01AA0)(__int64 a);
			sub_140A01AA0 sub_140A01AA0_f = (sub_140A01AA0)(d3dcompiler_47_og::moduleBase + 0xA00EA0);
			sub_140A01AA0(v8);

			// 0xA01050
			typedef signed __int64(__fastcall * nuccMemoryUnknown__PopCurrent)();
			nuccMemoryUnknown__PopCurrent nuccMemoryUnknown__PopCurrent_f = (nuccMemoryUnknown__PopCurrent)(d3dcompiler_47_og::moduleBase + 0xA01050);
			v0 = nuccMemoryUnknown__PopCurrent_f();

		}
		goto LABEL_17;
	}

	// LOAD PATCH
	{
		ActualVersion = 11;
		GameVersion = ActualVersion;
		cpkdata *c = (cpkdata*)malloc(sizeof(cpkdata));

		c->path = "sim:data/patch/12/launch.cpk";
		c->priority = 1;

		typedef signed __int64(__fastcall * sub_14056C3D4)(__int64 a, __int64 b);
		sub_14056C3D4 sub_14056C3D4_f = (sub_14056C3D4)(d3dcompiler_47_og::moduleBase + 0x56B7D4);
		sub_14056C3D4_f((__int64)c, GameVersion);
	}

	// LOAD BASE GAME CPK
	{
		vector<const char*> cpks;
		vector<int> priority;
		cpks.push_back("sim:data/launch/data1.cpk");
		priority.push_back(1);
		cpks.push_back("sim:data/launch/stage1.cpk");
		priority.push_back(1);
		cpks.push_back("disc:data/launch/dataRegion.cpk");
		priority.push_back(1);
		cpks.push_back("sim:data/launch/sound.cpk");
		priority.push_back(0);
		cpks.push_back("disc:data/launch/adx2.cpk");
		priority.push_back(0);
		cpks.push_back("disc:data/launch/movie1.cpk");
		priority.push_back(0);

		v5 = cpks.size();

		int x = 0;
		cpkdata *c = (cpkdata*)malloc(sizeof(cpkdata));

		do
		{
			// 0x56B74C
			typedef signed __int64(__fastcall * sub_14056C34C)(__int64 a);
			sub_14056C34C sub_14056C34C_f = (sub_14056C34C)(d3dcompiler_47_og::moduleBase + 0x56B74C);

			c->path = cpks.at(x);
			c->priority = priority.at(x);

			v0 = sub_14056C34C_f((__int64)c);
			x++;
			--v5;
		} while (v5);
	}

	int region = *(int*)(ccGameProperties::GetQword(0x1416663C8) + 0x1D4);
	//cout << "Game region is: " << region << endl;

	if (region != 1)
	{
		if (region == 19)
		{
			v6 = "disc:data/launch/spa/dataRegion.cpk";
		}
		else
		{
			if (!ccGameProperties::GetQword(0x1416759C8))
				goto LABEL_17;
			
			// 0xA31EB0
			typedef signed __int64(__fastcall * sub_140A32AB0)(__int64 a, __int64 b, __int64 c);
			sub_140A32AB0 sub_140A32AB0_f = (sub_140A32AB0)(d3dcompiler_47_og::moduleBase + 0xA31EB0);
			sub_140A32AB0_f(ccGameProperties::GetQword(0x1416759C8), (__int64)"disc:data/launch/LANG/dataRegion.cpk", (__int64)&v27);

			v6 = (const char*)&v27;
		}

		cpkdata *c = (cpkdata*)malloc(sizeof(cpkdata));
		c->path = v6;
		c->priority = 1;

		typedef signed __int64(__fastcall * sub_14056C34C)(__int64 a);
		sub_14056C34C sub_14056C34C_f = (sub_14056C34C)(d3dcompiler_47_og::moduleBase + 0x56B74C);
		v0 = sub_14056C34C_f((__int64)c);
	}

LABEL_17:
	// LOAD CUSTOM CPK
	{
		cpkdata *c = (cpkdata*)malloc(sizeof(cpkdata));

		for (int x = 0; x < CpkToLoad.size(); x++)
		{
			typedef signed __int64(__fastcall * sub_14056C34C)(__int64 a);
			sub_14056C34C sub_14056C34C_f = (sub_14056C34C)(d3dcompiler_47_og::moduleBase + 0x56B74C);

			GameVersion = CpkPriority.at(x);
			cout << "Loaded cpk " << CpkToLoad.at(x) << endl;
			c->path = CpkToLoad.at(x);
			c->priority = 0;

			typedef signed __int64(__fastcall * sub_14056C3D4)(__int64 a, __int64 b);
			sub_14056C3D4 sub_14056C3D4_f = (sub_14056C3D4)(d3dcompiler_47_og::moduleBase + 0x56B7D4);
			sub_14056C3D4_f((__int64)c, GameVersion);
		}
	}

	if (ccGameProperties::GetQword(0x1415F8298))
	{
		//v11 = (const char *)1001;
		//v12 = 1003;

		// 0x56B284
		typedef signed __int64(__fastcall * sub_14056BE84)(__int64 a);
		sub_14056BE84 sub_14056BE84_f = (sub_14056BE84)(d3dcompiler_47_og::moduleBase + 0x56B284);
		v0 = sub_14056BE84_f(ccGameProperties::GetQword(0x1415F8298));
	}

	return v0;
}