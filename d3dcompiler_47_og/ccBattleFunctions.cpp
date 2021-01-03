#include <stdio.h>
#include <iostream>

#include "ccBattleFunctions.h"
#include "d3dcompiler_47_og.h"

using namespace std;
using namespace moddingApi;

typedef uintptr_t(__fastcall * getplayerinfo)(uintptr_t, int);
getplayerinfo g_GetPlayerInfo;

typedef uintptr_t(__fastcall * getplayerinfo2)(uintptr_t, int);
getplayerinfo2 g_GetPlayerInfo2;

uintptr_t ccBattleFunctions::Battle_FillChakra(uintptr_t a1, int a2, float FillRate)
{
	g_GetPlayerInfo = (getplayerinfo)(d3dcompiler_47_og::moduleBase + 0x74A71C); // UPDATED TO 12

	uintptr_t result;
	float *MaxState;
	float *ActualState;
	float NewState;

	result = g_GetPlayerInfo(a1, a2);
	if (result)
	{
		MaxState = (float*)(result + 28);
		ActualState = (float*)(result + 24);

		if (*ActualState < *MaxState)
		{
			NewState = 50.0f;
			//NewState = *ActualState + FillRate;
			*ActualState = NewState;
			if (NewState > *MaxState)
			{
				*ActualState = *MaxState;
			}
		}
	}

	return result;
}

uintptr_t ccBattleFunctions::Battle_FillSubstitution(uintptr_t a1, int a2, float FillRate)
{
	g_GetPlayerInfo2 = (getplayerinfo)(d3dcompiler_47_og::moduleBase + 0x74A76C); // UPDATED TO 12

	uintptr_t result;
	float *MaxState;
	float *ActualState;
	float NewState;

	cout << "Player: " << a2 << endl;

	result = g_GetPlayerInfo2(a1, a2);
	if (result)
	{
		MaxState = (float*)(result + 20);
		ActualState = (float*)(result + 16);

		cout << "Actual: " << ActualState << endl;
		cout << endl;

		if (*ActualState < *MaxState)
		{
			NewState = *ActualState + FillRate;
			*ActualState = NewState;
			if (NewState > *MaxState)
			{
				*ActualState = *MaxState;
			}
		}
	}

	return result;
}