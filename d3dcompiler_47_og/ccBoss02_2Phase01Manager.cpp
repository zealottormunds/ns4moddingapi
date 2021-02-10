#include "ccBoss02_2Phase01Manager.h"
#include "d3dcompiler_47_og.h"
#include "ccGameProperties.h"
#include "Input.h"
#include <iostream>
#pragma warning( disable: 4307 )
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace moddingApi;

__int64 __fastcall moddingApi::ccBoss02_2Phase01Manager::fc_DoFunction(__int64 a1, __int64 a2)
{
	// 0xAB6D30
	typedef __int64(__fastcall * funct)(__int64 a, __int64 b);
	funct funct_f = (funct)(d3dcompiler_47_og::moduleBase + 0xAB6D30);
	return funct_f(a1, a2);
}

// 0x41D4A4
typedef __int64(__fastcall * sub_14041E0A4)(__int64 a, int b);
sub_14041E0A4 sub_14041E0A4_f = (sub_14041E0A4)(d3dcompiler_47_og::moduleBase + 0x41D4A4);

// 0x294698
typedef __int64(__fastcall * sub_140295298)(__int64 a);
sub_140295298 sub_140295298_f = (sub_140295298)(d3dcompiler_47_og::moduleBase + 0x294698);

// 0x41E0D8
typedef __int64(__fastcall * sub_14041ECD8)(__int64 a, char a2);
sub_14041ECD8 sub_14041ECD8_f = (sub_14041ECD8)(d3dcompiler_47_og::moduleBase + 0x41E0D8);

// 0x294704
typedef __int64(__fastcall * sub_140295304)(__int64 a);
sub_140295304 sub_140295304_f = (sub_140295304)(d3dcompiler_47_og::moduleBase + 0x294704);

// 0x42303C
typedef void(__fastcall * sub_140423C3C)(__int64 a);
sub_140423C3C sub_140423C3C_f = (sub_140423C3C)(d3dcompiler_47_og::moduleBase + 0x42303C);

// 0x3A8BDC
typedef __int64(__fastcall * sub_1403A97DC)(__int64 a);
sub_1403A97DC sub_1403A97DC_f = (sub_1403A97DC)(d3dcompiler_47_og::moduleBase + 0x3A8BDC);

// 0x76BB70
typedef __int64(__fastcall * sub_14076C770)();
sub_14076C770 sub_14076C770_f = (sub_14076C770)(d3dcompiler_47_og::moduleBase + 0x76BB70);

// 0x3A8BF4
typedef __int64(__fastcall * sub_1403A97F4)(__int64 a, __int64 b, __int64 c);
sub_1403A97F4 sub_1403A97F4_f = (sub_1403A97F4)(d3dcompiler_47_og::moduleBase + 0x3A8BF4);

// 0x85A948
typedef __int64(__fastcall * GetPlayerPointer)(int a);
GetPlayerPointer GetPlayerPointer_f = (GetPlayerPointer)(d3dcompiler_47_og::moduleBase + 0x85A948);

void __fastcall ccBoss02_2Phase01Manager::BossBattleBKKU_Loop00(__int64 a1)
{
	__int64 v1; // rdi@1
	__int64 v2; // rbx@1
	__int64 v3; // rcx@1
	__int64 v4; // rax@2
	__int64 v5; // rbx@3
	char v6; // dl@8

	v1 = a1;
	v2 = fc_DoFunction(*(__int64*)(d3dcompiler_47_og::moduleBase + 0x16BDA28 - 0xC00), (__int64)"BossBattleContinueManager");
	v3 = *(__int64*)(v2 + 8);

	if (v3)
	{
		// call qword ptr [rdx + 8]
		typedef __int64(__fastcall * funct)();
		funct funct_f = (funct)(*(__int64*)((*(__int64*)v3) + 8));

		//v4 = (*(int(**)(void))(*(__int64 *)v3 + 8i64))();
		v4 = funct_f();
		v5 = (d3dcompiler_47_og::moduleBase + 0x15C1E30) == v4 ? *(__int64 *)(*(__int64 *)(v2 + 8) + 16i64) : 0i64;

		if (v5 && *(__int64*)(v1 + 328))
		{
			if (sub_14041E0A4_f(v5, 5))
			{
				sub_140295298_f(*(__int64*)(v1 + 328));
				v6 = 5;
				sub_14041ECD8_f(v5, v6);
			}
			else if (sub_14041E0A4_f(v5, 6))
			{
				sub_140295304_f(*(__int64 *)(v1 + 328));
				v6 = 6;
				sub_14041ECD8_f(v5, v6);
			}
		}
	}

	cout << "P1: " << GetPlayerPointer_f(0) << endl;
	cout << "P2: " << GetPlayerPointer_f(1) << endl;
//LABEL_12:
	//sub_140423C3C_f(v1);
	//BossBattleBKKU_Loop01(v1);
}

void __fastcall ccBoss02_2Phase01Manager::BossBattleBKKU_Loop01(__int64 a1)
{
	__int64 v1; // rbx@1
	__int64 v2; // rcx@1
	__int64 v3; // rcx@7
	__int64 v4; // rcx@10
	__int64 v5; // rcx@12

	/*Input::UpdateKeys();
	if (Input::GetKeyDown('Z'))
	{
		cout << "test" << endl;
	}
	if (Input::GetKeyDown('X'))
	{
		v4 = *(__int64 *)(v1 + 328);
		sub_1403A97F4_f(v4, (__int64)"this_is_test", 1i64);
	}*/

	v1 = a1;
	v2 = *(__int64 *)(a1 + 328);
	if (v2)
	{
		if (*(int *)(v1 + 344))
		{
			if (*(int *)(v1 + 340))
			{
				*(int *)(v1 + 340) = 0;
				sub_1403A97DC(v2);
			}
			return;
		}
		if ((unsigned int)sub_14076C770())
		{
			if (!*(int *)(v1 + 340))
				goto LABEL_9;
			*(int *)(v1 + 340) = 0;
			v3 = *(__int64 *)(v1 + 328);
			*(int *)(v1 + 336) = floor(600.0 / (float)(30.0 / (float)*((__int64 *)ccGameProperties::GetQword(0x1416663C8) + 2370)));
			sub_1403A97DC(v3);
		}
		if (*(int *)(v1 + 340))
		{
			if (*(int *)(v1 + 336) <= 0)
			{
				*(int *)(v1 + 340) = 0;
				v5 = *(__int64 *)(v1 + 328);
				*(int *)(v1 + 336) = floor(600.0 / (float)(30.0 / (float)*((__int64 *)ccGameProperties::GetQword(0x1416663C8) + 2370)));
				sub_1403A97DC(v5);
			}
			goto LABEL_13;
		}
	LABEL_9:
		if (*(int *)(v1 + 336) <= 0)
		{
			*(int *)(v1 + 340) = 1;
			v4 = *(__int64 *)(v1 + 328);
			*(int *)(v1 + 336) = floor(180.0 / (float)(30.0 / (float)*((__int64 *)ccGameProperties::GetQword(0x1416663C8) + 2370)));
			sub_1403A97F4_f(v4, (__int64)"this_is_test", 1i64);
		}
	LABEL_13:
		--*(int *)(v1 + 336);
	}
}