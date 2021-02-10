#include "BattleFunctions.h"
#include "d3dcompiler_47_og.h"
#include "ccGameProperties.h"
#include <xmmintrin.h>
#include <iostream>
#pragma warning( disable: 4307 )

using namespace std;
using namespace moddingApi;

int __fastcall BattleFunctions::ChangeSubstitutionState(__int64 a1, float a2, float a3)
{
	__int64 v3; // rbx@1
	float newSub; // xmm6_4@1
	signed __int64 v5; // rax@1
	__int64 v6; // rdi@2
	__int64 v7; // rdi@3
	unsigned int v8; // ebx@4
	int v9; // er8@4

	v3 = a1;
	newSub = a3;

	__int64 tempaddress = *(__int64*)((*(__int64*)(a1)) + 0xC20);
	typedef signed int(__fastcall * fc_sub_temporalfunct)();
	fc_sub_temporalfunct sub_temporalfunct = (fc_sub_temporalfunct)(tempaddress);
	v5 = sub_temporalfunct();

	if (!v5)
	{
		v6 = ccGameProperties::GetQword(0x14161C8C8);
		if (v6)
		{
			cout << "is v6" << endl;

			tempaddress = *(__int64*)((*(__int64*)(v3)) + 0x40);
			typedef signed int(__fastcall * fc_sub_temporalfunct2)(__int64 a);
			fc_sub_temporalfunct2 sub_temporalfunct2 = (fc_sub_temporalfunct2)(tempaddress);
			__int64 tempvalue = sub_temporalfunct2(v3);

			v5 = 104 * tempvalue;
			v7 = v5 + v6 + 24;
			if (v7)
			{
				cout << "is v7 " << (*(int(**)(void))(*(__int64 *)(v3 + 0xB00) + 32)) << endl;

				//v8 = (*(int(**)(void))(*(__int64 *)(v3 + 0xB00) + 32))();
				//typedef signed int(__fastcall * fc_sub_temporalfunct3)();
				//fc_sub_temporalfunct3 sub_temporalfunct3 = (fc_sub_temporalfunct3)(tempaddress);
				//v8 = sub_temporalfunct3();

				// 0x74A3E4 fc_player_getMaxSub __int64 int
				typedef signed __int64(__fastcall * fc_player_getMaxSub)(__int64 a, unsigned int b);
				fc_player_getMaxSub player_getMaxSub = (fc_player_getMaxSub)(d3dcompiler_47_og::moduleBase + 0x74A3E4);
				player_getMaxSub(v7, v8);

				if (a3 >= a2)
					newSub = a2;

				// 0x74AC10 fc_player_setActualSub __int64 uint int float
				typedef signed __int64(__fastcall * fc_player_setActualSub)(__int64 a, unsigned int b, int a3, float newSub);
				fc_player_setActualSub player_setActualSub = (fc_player_setActualSub)(d3dcompiler_47_og::moduleBase + 0x74AC10);
				v5 = player_setActualSub(v7, v8, v9, newSub);
			}
		}

		cout << "finished" << endl;
	}

	return 0;
}
