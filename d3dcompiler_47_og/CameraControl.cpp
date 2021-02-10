#include "CameraControl.h"
#include "Vector3.h"
#include "d3dcompiler_47_og.h"
#include <iostream>
#include <xmmintrin.h>
#include "Input.h"
#pragma warning( disable: 4307 )

using namespace std;
using namespace moddingApi;

int __fastcall CameraControl::CameraControllerMain(__int64 a1)
{
	__int64 v1;
	int v2;

	v1 = a1;

	typedef void(__fastcall * fc_sub_1405950E0)();
	fc_sub_1405950E0 sub_1405950E0 = (fc_sub_1405950E0)(d3dcompiler_47_og::moduleBase + 0x5944E0);
	sub_1405950E0();

	v2 = *(int*)(v1 + (0x1EC));
	if (v2 > 0)
	{
		*(int*)(v1 + (0x1EC)) = v2 - 1;
	}

	//typedef __int64(__fastcall * fc_CameraFunction)(__int64 a, int b);
	//fc_CameraFunction CameraFunction = (fc_CameraFunction)(d3dcompiler_47_og::moduleBase + 0x741CA4);
	//return CameraFunction(v1, 0);

	CameraControllerLoop(v1, 0);

	return 0;
}

#include <string.h>
#include <vector>

int BOOL_QF = 0;
int INT_QF = 1;
int INT64_QF = 2;
int FLOAT_QF = 3;
int VECTOR3_QF = 4;

#include <cstdarg>
/*__int64 __fastcall QuickFunction(__int64 funct, int args, ...)
{
	typedef __int64(__fastcall * fc_temp)(...);
	fc_temp temp = (fc_temp)(d3dcompiler_47_og::moduleBase + funct);
	return temp();
}*/

struct Camera
{
	byte a[0x6C];
	float fov; // 6c
	float unk1; // 70
	float unk2; // 74
	float unk3; // 78
	float posx; // 7c
	float unk4; // 80
	float unk5; // 84
	float unk6; // 88
	float posy; // 8c
	float unk8; // 90
	float unk9; // 94
	float unk10; // 98
	float posz; // 9c
};

__int64 __fastcall QuickFunction(__int64 funct, vector<int> varTypes, vector<__int64> varPointers)
{
	// 0 = bool
	// 1 = int
	// 2 = int64
	// 3 = float
	// 4 = vector3

	switch (varTypes.size())
	{
		case 0:
		{
			typedef __int64(__fastcall * fc_temp)();
			fc_temp temp = (fc_temp)(d3dcompiler_47_og::moduleBase + funct);
			return temp();
		}
		break;
		case 1:
		{
			if (varTypes[0] == BOOL_QF)
			{
				typedef __int64(__fastcall * fc_temp)(bool a);
				fc_temp temp = (fc_temp)(d3dcompiler_47_og::moduleBase + funct);
				return temp(*(bool*)(varPointers[0]));
			}
			else if (varTypes[0] == INT_QF)
			{
				typedef __int64(__fastcall * fc_temp)(int a);
				fc_temp temp = (fc_temp)(d3dcompiler_47_og::moduleBase + funct);
				return temp(*(int*)(varPointers[0]));
			}
			else if (varTypes[0] == INT64_QF)
			{
				typedef __int64(__fastcall * fc_temp)(__int64 a);
				fc_temp temp = (fc_temp)(d3dcompiler_47_og::moduleBase + funct);
				return temp(*(__int64*)(varPointers[0]));
			}
			else if (varTypes[0] == FLOAT_QF)
			{
				typedef __int64(__fastcall * fc_temp)(float a);
				fc_temp temp = (fc_temp)(d3dcompiler_47_og::moduleBase + funct);
				return temp(*(float*)(varPointers[0]));
			}
			case 4:
			{

			}
			break;
		}
		break;
	}

	return 0;
}

__int64 __fastcall CameraControl::CameraControllerLoop(__int64 a1, int a2)
{
	__int64 v2; // rdi@1
	__int64 v3; // r14@1
	signed __int64 v4; // rax@1
	__int64 v5; // rsi@1
	__int64 v6; // r15@3
	signed int v7; // er12@3
	float *v8; // r13@10
	int v9; // eax@11
	int v10; // ebx@11
	int v11; // eax@11
	int v12; // ebx@14
	int v13; // eax@14
	float v14; // xmm0_4@15
	float v15; // xmm1_4@15
	float v16; // xmm2_4@19
	float v17; // xmm1_4@19
	float v18; // xmm0_4@25
	float v19; // xmm1_4@25
	float v20; // xmm2_4@29
	float v21; // xmm1_4@29
	float v22; // xmm0_4@34
	float v23; // xmm1_4@38
	float v24; // xmm6_4@43
	float v25; // xmm7_4@43
	Vector3 *v26; // rax@43
	float v27; // xmm0_4@43
	Vector3 v28 = Vector3(0, 0, 0); // rax@56
	Vector3 *v29; // rax@59
	float v30; // xmm6_4@59
	__int64 v31; // xmm0_8@59
	int v32; // eax@59
	__m128 v33; // xmm2@65
	float v34; // xmm2_4@65
	float v35; // xmm2_4@66
	Vector3 *v36; // rax@68
	__int64 v37; // rax@69
	__int64 v38; // rax@69
	__int64 v39; // rax@70
	__int64 v40; // rbx@70
	Vector3 *v41; // rax@75
	float v42; // xmm0_4@75
	Vector3 *v43; // rax@75
	__int64 v44; // rax@75
	Vector3 *v45; // rax@76
	float v46; // xmm0_4@76
	__int64 v47; // rax@76
	float v48; // xmm6_4@78
	__int64 v49; // rax@80
	float v50; // xmm0_4@80
	__int64 v51; // rax@81
	__int64 v52; // rax@81
	Vector3 *v53; // rax@82
	float v54; // xmm0_4@82
	__int64 v55; // rax@82
	float v56; // xmm6_4@84
	Vector3 *v57; // rax@86
	__int64 v58; // rax@86
	float v59; // xmm0_4@86
	__int64 v60; // rax@88
	__int64 v61; // rax@88
	__int64 v62; // rax@88
	__int64 v63; // rax@88
	signed int v64; // ebx@89
	Vector3 *v65; // rax@91
	Vector3 *v66; // rax@91
	Vector3 *v67; // rax@91
	float v68; // xmm0_4@91
	__int64 v69; // rax@91
	signed int v70; // eax@97
	float v71; // xmm0_4@97
	float v72; // xmm1_4@97
	float v73; // xmm7_4@103
	float v74; // xmm6_4@103
	__int64 v75; // rax@108
	float v76; // xmm0_4@108
	__int64 v77; // rax@109
	__int64 v78; // rax@109
	Vector3 *v79; // rax@110
	__int64 v80; // rax@110
	float v81; // xmm0_4@110
	__int64 v82; // rax@112
	__int64 v83; // rax@112
	__int64 v84; // rax@112
	Vector3 *v85; // rax@113
	float v86; // xmm0_4@113
	float v87; // xmm6_4@113
	Vector3 *v88; // rax@117
	float v89; // xmm0_4@117
	Vector3 *v90; // rax@117
	__int64 v91; // rax@117
	__int64 v92; // rax@117
	float v93; // xmm7_4@117
	float v94; // xmm0_4@117
	float v95; // xmm6_4@118
	float v96; // xmm0_4@124
	float v97; // xmm6_4@128
	Vector3 *v98; // rax@135
	float v99; // xmm0_4@135
	float v100; // xmm7_4@135
	__int64 v101; // rax@139
	Vector3 *v102; // rax@139
	Vector3 *v103; // rax@139
	Vector3 *v104; // rax@139
	__int64 v105; // rax@139
	float v106; // xmm6_4@139
	float v107; // xmm1_4@139
	float v108; // xmm0_4@142
	float v109; // xmm0_4@143
	float v110; // xmm6_4@143
	float v111; // xmm7_4@145
	float v112; // xmm10_4@145
	float v113; // xmm9_4@145
	float v114; // xmm1_4@147
	Vector3 *v115; // rax@153
	bool v116; // zf@153
	__int64 v117; // xmm0_8@153
	__m128 v118; // xmm0@156
	Vector3 *v119; // rax@158
	float v120; // xmm0_4@158
	Vector3 *v121; // rax@160
	__int64 v122; // rax@160
	float v123; // xmm14_4@161
	float v124; // xmm3_4@171
	Vector3 *v125; // rax@178
	float v126; // xmm0_4@178
	__int64 v127; // xmm0_8@179
	__int64 v128; // rax@181
	__int64 v129; // rbx@181
	Vector3 *v130; // rax@182
	__m128 v131; // xmm0@182
	Vector3 *v132; // rax@183
	__int64 v133; // rax@183
	__int64 v134; // rax@183
	Vector3 *v135; // rax@185
	float v136; // xmm0_4@185
	int v137; // edx@185
	__int64 v138; // rcx@185
	int v139; // er8@185
	int v140; // er9@185
	__int64 v141; // xmm0_8@186
	float v142; // xmm8_4@187
	void *v143; // rax@187
	float v144; // xmm6_4@187
	float v145; // xmm12_4@187
	float v146; // xmm9_4@187
	int v147; // edx@187
	__int64 v148; // rcx@187
	int v149; // er8@187
	int v150; // er9@187
	
	__m128 v151; // xmm11@187 AAAAAAAAAAAAAAAA _int128

	float v152; // xmm10_4@187
	float v153; // xmm7_4@187
	int v154; // edx@187
	__int64 v155; // rcx@187
	int v156; // er8@187
	int v157; // er9@187
	float *v158; // rax@187
	float FOV; // xmm6_4@187
	int v160; // ebx@188
	float v161; // xmm0_4@192
	Vector3 a1a = Vector3(0, 0, 0); // [sp+20h] [bp-3B8h]@43
	Vector3 a2a = Vector3(0, 0, 0); // [sp+30h] [bp-3A8h]@59
	Vector3 xfinal = Vector3(0, 0, 0); // [sp+40h] [bp-398h]@43
	Vector3 xvector = Vector3(0, 0, 0); // [sp+50h] [bp-388h]@10
	Vector3 a3 = Vector3(0, 0, 0); // [sp+60h] [bp-378h]@10
	float v168; // [sp+68h] [bp-370h]@43
	Vector3 v169 = Vector3(0, 0, 0); // [sp+70h] [bp-368h]@86
	float v170; // [sp+80h] [bp-358h]@10
	float v171; // [sp+88h] [bp-350h]@117
	__int64 v172; // [sp+90h] [bp-348h]@110
	float v173; // [sp+A0h] [bp-338h]@75
	Vector3 v174 = Vector3(0, 0, 0); // [sp+A8h] [bp-330h]@91
	__int64 v175; // [sp+B0h] [bp-328h]@10
	int v176; // [sp+B8h] [bp-320h]@81
	__int64 v177; // [sp+C0h] [bp-318h]@10
	float v178; // [sp+C8h] [bp-310h]@65
	float v179; // [sp+D0h] [bp-308h]@71
	float v180; // [sp+D8h] [bp-300h]@75
	int v181; // [sp+DCh] [bp-2FCh]@71
	int v182; // [sp+F0h] [bp-2E8h]@10
	int v183; // [sp+F4h] [bp-2E4h]@11
	float v184; // [sp+F8h] [bp-2E0h]@3
	float v185; // [sp+100h] [bp-2D8h]@161
	float v186; // [sp+104h] [bp-2D4h]@113
	float v187; // [sp+108h] [bp-2D0h]@117
	float v188; // [sp+10Ch] [bp-2CCh]@117
	float v189; // [sp+110h] [bp-2C8h]@139
	float v190; // [sp+114h] [bp-2C4h]@139
	float v191; // [sp+118h] [bp-2C0h]@135
	float v192; // [sp+11Ch] [bp-2BCh]@135
	float v193; // [sp+120h] [bp-2B8h]@187
	float v194; // [sp+128h] [bp-2B0h]@178
	float v195; // [sp+130h] [bp-2A8h]@178
	float v196; // [sp+138h] [bp-2A0h]@185
	Vector3 v197 = Vector3(0, 0, 0); // [sp+140h] [bp-298h]@185
	Vector3 *v198; // [sp+148h] [bp-290h]@10
	__int64 v199; // [sp+160h] [bp-278h]@81
	__int64 v200; // [sp+1A0h] [bp-238h]@10
	__int64 v201; // [sp+1B0h] [bp-228h]@81
	__int64 v202; // [sp+1F0h] [bp-1E8h]@71
	__int64 v203; // [sp+208h] [bp-1D0h]@183
	int v204; // [sp+3E8h] [bp+10h]@1
	int v205; // [sp+3F0h] [bp+18h]@11
	signed int v206; // [sp+3F8h] [bp+20h]@10

	v204 = a2;
	v2 = a1;

	typedef signed __int64(__fastcall * fc_sub_14085B548)(unsigned int a1); // 85A948
	fc_sub_14085B548 sub_14085B548 = (fc_sub_14085B548)(d3dcompiler_47_og::moduleBase + 0x85A948);
	v3 = sub_14085B548(0);
	v4 = sub_14085B548(1u);
	v5 = v4;

	if (v3 && v4)
	{
		// 7436E8
		typedef signed __int64(__fastcall * fc_sub_1407442E8)(); // 7436E8
		fc_sub_1407442E8 sub_1407442E8 = (fc_sub_1407442E8)(d3dcompiler_47_og::moduleBase + 0x7436E8);
		v6 = sub_1407442E8();

		typedef signed __int64(__fastcall * fc_sub_temporalfunct)(__int64 a, float* b, __int64 c);
		fc_sub_temporalfunct sub_temporalfunct = (fc_sub_temporalfunct)(*(__int64*)((*(__int64*)v2) + 0x88));
		sub_temporalfunct(v2, (float*)(&v183), v6);
		v7 = 0;

		// Check for 3GUY and 4D
		{
			int characterID_v3 = *(int*)(v3 + 0xC8C);
			int characterID_v5 = *(int*)(v5 + 0xC8C);
			__int64 tempaddress_v3 = *(__int64*)((*(__int64*)(v3)) + 0x11B8);
			__int64 tempaddress_v5 = *(__int64*)((*(__int64*)(v5)) + 0x11B8);
			int currentState_v3 = *(int*)(v3 + 0xCC0);
			int currentState_v5 = *(int*)(v5 + 0xCC0);

			typedef signed __int64(__fastcall * fc_sub_temporalfunct_v3)(__int64 a); // temp funct
			fc_sub_temporalfunct_v3 sub_temporalfunct_v3 = (fc_sub_temporalfunct_v3)(tempaddress_v3);
			fc_sub_temporalfunct_v3 sub_temporalfunct_v5 = (fc_sub_temporalfunct_v3)(tempaddress_v5);

			// Checks if one of the players is 0xC4 (3GUY) and if their state is 0x4D
			if ((characterID_v3 == 0xC4 && sub_temporalfunct_v3(v3) && currentState_v3 == 0x4D) || (characterID_v5 == 0xC4 && sub_temporalfunct_v5(v5) && currentState_v5 == 0x4D))
			{
				v7 = 1;
			}
		}

		// 0xA03A90 Vector3::Set_AX_AZ_to_BX_BZ
		v8 = (float*)(v2 + 0xB0);
		typedef Vector3*(__fastcall * fc_Vector3_Set_AX_AZ_to_BX_BZ)(Vector3* a, Vector3* b);
		fc_Vector3_Set_AX_AZ_to_BX_BZ sub_Vector3_Set_AX_AZ_to_BX_BZ = (fc_Vector3_Set_AX_AZ_to_BX_BZ)(d3dcompiler_47_og::moduleBase + 0xA03A90);
		sub_Vector3_Set_AX_AZ_to_BX_BZ(&xvector, (Vector3*)(v2 + 0xB0));

		// 0xA03AF0 Vector3::GetQword
		typedef Vector3*(__fastcall * fc_Vector3_GetQword)(Vector3* a);
		fc_Vector3_GetQword sub_Vector3_GetQword = (fc_Vector3_GetQword)(d3dcompiler_47_og::moduleBase + 0xA03AF0);
		sub_Vector3_GetQword(&v174); // fc_Vector2_XY_GetQword(&v174);

		// 0xA26380 sub_140A26F80 (vector3 substract and other stuff)
		typedef __int64(__fastcall * fc_sub_140A26F80)(__int64 a, Vector3* b);
		fc_sub_140A26F80 sub_140A26F80 = (fc_sub_140A26F80)(d3dcompiler_47_og::moduleBase + 0xA26380);
		sub_140A26F80(v2 + 64, &v174); //  sub_140A26F80(v2 + 64, &v174);

		sub_Vector3_Set_AX_AZ_to_BX_BZ(&v169, (Vector3*)(v2 + 0xBC)); // Vector3::Set_AX_AZ_to_BX_BZ(&v169, (v2 + 188));
		sub_Vector3_Set_AX_AZ_to_BX_BZ(&v197, (Vector3*)(v2 + 0xC8)); // Vector3::Set_AX_AZ_to_BX_BZ(&v197, (v2 + 200));
		sub_Vector3_GetQword((Vector3*)&v199);
		sub_Vector3_GetQword((Vector3*)&a3);
		sub_Vector3_GetQword((Vector3*)&v176);

		v205 = 0;
		v181 = 0;

		// 0x7438AC sub_1407444AC
		typedef signed __int64(__fastcall * sub_1407444AC)(__int64 a, __int64 b, __int64 c, __int64 d);
		sub_1407444AC f_sub_1407444AC = (sub_1407444AC)(d3dcompiler_47_og::moduleBase + 0x7438AC);
		v4 = f_sub_1407444AC(v2, (__int64)&a3, (__int64)&v176, (__int64)&v181);

		if (v4)
		{
			v9 = (int)(QuickFunction(0x5944E0, vector<int>{}, vector<__int64>{}));
			v10 = v9;
			v204 = v9;

			// 0x594410 sub_140595010
			typedef int(__fastcall * sub_140595010)(Vector3* a, int b, int c, int d);
			sub_140595010 f_sub_140595010 = (sub_140595010)(d3dcompiler_47_og::moduleBase + 0x594410);
			v4 = f_sub_140595010((Vector3*)&v177, v11, v12, v13);
			v185 = v14;

			if (v10 && v14 && *(__int64*)(v2 + 0x1EC) <= 0)
			{
				typedef int(__fastcall * sub_140595060)(Vector3* a);
				sub_140595060 f_sub_140595060 = (sub_140595060)(d3dcompiler_47_og::moduleBase + 0x594460);

				v15 = f_sub_140595060((Vector3*)&a3);
				v16 = f_sub_140595060((Vector3*)&v178);

				if (v16)
				{
					v17 = *(float *)(v2 + 480);
					v18 = *(float *)(v2 + 484);

					if (v17 < v18)
						*(float *)(v2 + 480) = v17 + *(float *)(v2 + 496);

					if (v18 < *(float *)(v2 + 480))
						*(float *)(v2 + 480) = v18;

					v19 = *(float *)(v2 + 472);
					v20 = *(float *)(v2 + 476);

					if (v19 < v20)
						*(float *)(v2 + 472) = (float)(v20 * *(float *)(v2 + 496)) + v19;

					if (v20 < *(float *)(v2 + 472))
						*(float *)(v2 + 472) = v20;
				}

				if (v15)
				{
					if (v16)
					{
						v21 = *(float *)(v2 + 480);
						v22 = *(float *)(v2 + 488);
						if (v21 < v22)
							*(float *)(v2 + 480) = v21 + *(float *)(v2 + 496);
						if (v22 < *(float *)(v2 + 480))
							*(float *)(v2 + 480) = v22;
						v23 = *(float *)(v2 + 472);
						v24 = *(float *)(v2 + 476);
						if (v23 < v24)
							*(float *)(v2 + 472) = (float)(v24 * *(float *)(v2 + 496)) + v23;
						v10 = v206;
						if (v24 < *(float *)(v2 + 472))
							*(float *)(v2 + 472) = v24;
						goto LABEL_43;
					}
				}
				else if (!v16)
				{
					v25 = *(float *)(v2 + 480);
					if (v25 > 1.0)
						*(float *)(v2 + 480) = v25 - *(float *)(v2 + 500);
					if (*(float *)(v2 + 480) < 1.0)
						*(float*)(v2 + 480) = 1.0;
					v26->x = *(float*)(v2 + 472);
					if (v26->x > 0.0)
						*(float *)(v2 + 472) = v26->x - (float)(*(float *)(v2 + 500) * *(float *)(v2 + 476));
					v10 = v206;
					if (*(float *)(v2 + 472) < 0.0)
						*(int *)(v2 + 472) = 0;
					goto LABEL_43;
				}
				v10 = v206;
			}
		LABEL_43:
			v27 = v185;
			v28.x = a3.z;
			sub_Vector3_GetQword(&a1a);

			typedef Vector3*(__fastcall * Vector3__Substract)(Vector3* a, Vector3* b, Vector3* c);
			Vector3__Substract Vector3__Substract_f = (Vector3__Substract)(d3dcompiler_47_og::moduleBase + 0xA03FF0);
			v29 = Vector3__Substract_f(&xvector, &xfinal, &a3);
			a1a.x = v29->x;
			v30 = a1a.x;
			a1a.z = v29->z;

			// 0xA03D80
			typedef int(__fastcall * sub_140A04980)(__int64 a);
			sub_140A04980 sub_140A04980_f = (sub_140A04980)(d3dcompiler_47_og::moduleBase + 0xA03D80);
			sub_140A04980_f((__int64)&a1a);

			if (v30 > 0.0)
			{
				// 0xA03F40
				typedef __int64(__fastcall * sub_140A04B40)(__int64 a);
				sub_140A04B40 sub_140A04B40_f = (sub_140A04B40)(d3dcompiler_47_og::moduleBase + 0xA03F40);
				sub_140A04B40_f((__int64)&a1a);

				if ((int)v6 == 10 && (*(int *)(v3 + 82004) == 4 && !(*(int(__fastcall **)(__int64))(*(__int64 *)v3 + 4536i64))(v3) && *(int *)(v3 + 3264) == 64 || *(int *)(v5 + 82004) == 4 && !(*(int(__fastcall **)(__int64))(*(__int64 *)v5 + 4536i64))(v5) && *(int *)(v5 + 3264) == 64))
				{
					v27 = v27 * 1.5;
				}

				if (v10)
				{
					v27 = v27 * *(float *)(v2 + 480);
				}

				if (v7)
				{
					v27 = v27 + 900.0;
					v28.x = v28.x + 200.0;

					// 0xA03EE0
					typedef Vector3*(__fastcall * Vector3_MultiplyMagnitude)(Vector3* a, Vector3* b, float mag);
					Vector3_MultiplyMagnitude Vector3_MultiplyMagnitude_f = (Vector3_MultiplyMagnitude)(d3dcompiler_47_og::moduleBase + 0xA03EE0);
					v31 = (__int64)Vector3_MultiplyMagnitude_f(&a1a, &xfinal, v27);
					a1a.x = (*(Vector3*)v31).x;
					a1a.z = (*(Vector3*)v31).z;
				}
			}

			Camera * c = ((Camera*)(v2));
			//cout << "Camera pointer: " << std::hex << v2 << endl;
			/*Input::UpdateKeys();

			if (Input::GetKeyDown('M'))
			{
				cout << "Camera pointer: " << std::hex << v2 << endl;
			}
			if (Input::GetKey('Z'))
			{
				c->posx += 30;
			}
			if (Input::GetKey('X'))
			{
				c->posx -= 30;
			}
			if (Input::GetKey('C'))
			{
				c->posz -= 30;
			}
			if (Input::GetKey('V'))
			{
				c->posz += 30;
			}
			if (Input::GetKey('B'))
			{
				c->posy -= 30;
			}
			if (Input::GetKey('N'))
			{
				c->posy += 30;
			}*/

			//(*(Camera*)(v2)).fov += 0.05;
			//v27 = v185;
			//v28->x = a3.z;
		}
	} 

	return 0;
}