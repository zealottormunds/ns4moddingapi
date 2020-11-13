#pragma warning( disable: 4307 )
#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
#pragma region Standard Imports
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ccPlayer.h"
#include "d3dcompiler_47_og.h"
#include "HookFunctions.h"
#include "ccGameProperties.h"
#include "Input.h"
#include "LuaHook.h"
#include "ccMemoryFunctions.h"
#include "ccPlayerStruct.h"
#include "Vector3.h"
#include "ccGeneralGameFunctions.h"
#include "LuaHook_Commands.h"
#include "ccBattleInputs.h"
#pragma endregion

#include "Memory.h"
#include <mmsystem.h>
#pragma region Character Imports
// 1
#include "c1CMN.h"
//#include "c1AKM.h"
//#include "c1FIR.h"
//#include "c1GAR.h"
//#include "c1HAK.h"
//#include "c1HKG.h"
//#include "c1HNT.h"
//#include "c1INO.h"
//#include "c1JBR.h"
//#include "c1KIB.h"
//#include "c1KMM.h"
//#include "c1KNK.h"
//#include "c1KRS.h"
//#include "c1NEJ.h"
//#include "c1NRT.h"
//#include "c1ROC.h"
//#include "c1SEC.h"
//#include "c1SIK.h"
//#include "c1SIN.h"
//#include "c1SKR.h"
//#include "c1SSK.h"
//#include "c1TEN.h"
//#include "c1TMR.h"
//#include "c1TYO.h"
//#include "c1ZBZ.h"

// 2
//#include "c2AKM.h"
//#include "c2ASM.h"
//#include "c2CYB.h"
//#include "c2DDR.h"
//#include "c2DNZ.h"
//#include "c2FOU.h"
//#include "c2GAR.h"
//#include "c2GAV.h"
//#include "c2GUY.h"
//#include "c2HDN.h"
//#include "c2HNT.h"
//#include "c2INO.h"
//#include "c2ITC.h"
//#include "c2JBR.h"
//#include "c2JRY.h"
//#include "c2JUG.h"
//#include "c2KAR.h"
//#include "c2KBT.h"
//#include "c2KBX.h"
//#include "c2KIB.h"
//#include "c2KKG.h"
//#include "c2KKS.h"
//#include "c2KKX.h"
//#include "c2KLB.h"
//#include "c2KNK.h"
//#include "c2KNN.h"
//#include "c2KRS.h"
//#include "c2KSM.h"
//#include "c2KZU.h"
//#include "c2MDR.h"
//#include "c2MKG.h"
//#include "c2NEJ.h"
//#include "c2NRG.h"
//#include "c2NRT.h"
//#include "c2NRX.h"
//#include "c2OBT.h"
//#include "c2OBX.h"
//#include "c2ORC.h"
//#include "c2PAR.h"
//#include "c2PEA.h"
//#include "c2RKG.h"
//#include "c2ROC.h"
//#include "c2SAI.h"
//#include "c2SCO.h"
//#include "c2SCX.h"
//#include "c2SGT.h"
//#include "c2SIK.h"
//#include "c2SIN.h"
//#include "c2SKR.h"
//#include "c2SSK.h"
//#include "c2SSY.h"
//#include "c2SSZ.h"
//#include "c2TEN.h"
//#include "c2TKG.h"
//#include "c2TMR.h"
//#include "c2TND.h"
//#include "c2TOB.h"
//#include "c2TYO.h"
//#include "c2YMT.h"

// 3
//#include "c3DRI.h"
//#include "c3GAR.h"
//#include "c3GUY.h"
//#include "c3HAN.h"
//#include "c3HNZ.h"
//#include "c3HSM.h"
//#include "c3IRK.h"
//#include "c3JBR.h"
//#include "c3KBT.h"
//#include "c3KHM.h"
//#include "c3KKS.h"
//#include "c3KLB.h"
//#include "c3KSN.h"
//#include "c3MDR.h"
//#include "c3MDR_2.h"
//#include "c3MFN.h"
//#include "c3MNT.h"
//#include "c3NGT.h"
//#include "c3NRT.h"
//#include "c3NYG.h"
//#include "c3OBT.h"
//#include "c3RUS.h"
//#include "c3SSK.h"
//#include "c3TOB.h"
//#include "c3TYO.h"
//#include "c3UTK.h"
//#include "c3WHO.h"
//#include "c3YGR.h"

// 4
//#include "c4JBR.h"
//#include "c4KKG.h"
//#include "c4MKG.h"
//#include "c4MNR.h"
//#include "c4MUU.h"
//#include "c4NRT.h"
//#include "c4RIN.h"
//#include "c4RKG.h"
//#include "c4SSI.h"

// 5
//#include "c5JBR.h"
//#include "c5JRB.h"
//#include "c5KDM.h"
//#include "c5KGY.h"
//#include "c5KRS.h"
//#include "c5MDR.h"
//#include "c5NRT.h"
//#include "c5OBT.h"
//#include "c5SKN.h"
//#include "c5SSK.h"
//#include "c5TYY.h"

// 6 - 8
//#include "c6HNB.h"
//#include "c6HNT.h"
//#include "c6JBR.h"
//#include "c6NRT.h"
//#include "c6SKR.h"
//#include "c6SSK.h"
//#include "c7BRN.h"
//#include "c7BRT.h"
//#include "c7BRX.h"
//#include "c7GAR.h"
//#include "c7KHM.h"
//#include "c7KIN.h"
//#include "c7MMS.h"
//#include "c7MMV.h"
//#include "c7MTK.h"
//#include "c7NRN.h"
//#include "c7NRT.h"
//#include "c7SKD.h"
//#include "c7SKR.h"
//#include "c7SLD.h"
//#include "c7SLN.h"
//#include "c7SSK.h"
//#include "c7SSX.h"
//#include "c7YRI.h"
//#include "c8AEM.h"
//#include "c8INO.h"
//#include "c8KIB.h"
//#include "c8KIN.h"
//#include "c8KNK.h"
//#include "c8MMS.h"
//#include "c8ROC.h"
//#include "c8SAI.h"
//#include "c8SIK.h"
//#include "c8SIN.h"
//#include "c8TEN.h"
//#include "c8TMR.h"
//#include "c8TYO.h"

/* Story
#include "cABRT.h"
#include "cB1NR.h"
#include "cB1SS.h"
#include "cB2NR.h"
#include "cB3HS.h"
#include "cB4NR.h"
#include "cB5OB.h"
#include "cB6BT.h"
#include "cBAOD.h"
#include "cBGKT.h"
#include "cBGRG.h"
#include "cBGRN.h"
#include "cBGUY.h"
#include "cBGYU.h"
#include "cBHSM.h"
#include "cBISS.h"
#include "cBJB1.h"
#include "cBJB2.h"
#include "cBJB3.h"
#include "cBJB4.h"
#include "cBJYD.h"
#include "cBJYG.h"
#include "cBKGV.h"
#include "cBKGY.h"
#include "cBKKK.h"
#include "cBKKS.h"
#include "cBKKU.h"
#include "cBKKX.h"
#include "cBKMS.h"
#include "cBKRL.h"
#include "cBKRS.h"
#include "cBKSR.h"
#include "cBKTY.h"
#include "cBMDJ.h"
#include "cBMDK.h"
#include "cBMDR.h"
#include "cBMDT.h"
#include "cBMHR.h"
#include "cBMKJ.h"
#include "cBMNK.h"
#include "cBNRC.h"
#include "cBNRG.h"
#include "cBNRT.h"
#include "cBNRX.h"
#include "cBOBK.h"
#include "cBOBR.h"
#include "cBOBS.h"
#include "cBOBT.h"
#include "cBOBZ.h"
#include "cBRMD.h"
#include "cBRSK.h"
#include "cBSSC.h"
#include "cBSSK.h"
#include "cBSSN.h"
#include "cBSSX.h"
#include "cBSSZ.h"
#include "cBTSK.h"
#include "cGFSA.h"
#include "cGMHR.h"
#include "cGZTU.h"
#include "cJKKS.h"
#include "cTYYP.h"
*/
#pragma endregion

using namespace std;
using namespace moddingApi;

//Cancel Variables
float ACDStartup = 60;

int prevFrame = 0;
int prevBattle = 0;
ccBattleInputs* inputState;
int timeflag = 0;
int support1timeflag = 0;
int support2timeflag = 0;
int timer = 3000;
int support1timer = 3000;
int support2timer = 3000;


int stageNumber;
int soundNumber;
int stageselectedNumber;
void ccPlayer::Start()
{
	// Currently this function does nothing.
}

// This function is ran every frame all the time. 
void ccPlayer::Loop()
{
	/*External::Memory memory = External::Memory("NSUNS4.exe");
	uintptr_t baseAddr = memory.getModule("NSUNS4.exe");
	uintptr_t stageAddr = memory.getAddress(baseAddr + 0x016BC888, { 0x90,0x128,0x50,0x18 });
	uintptr_t stageselectedAddr = stageAddr + 4;

	stageNumber = memory.read<int>(stageAddr);
	int stageselectedNumber = memory.read<int>(stageselectedAddr);
	*/
	//cout << "GetModuleHandle(0): " << hex << int(GetModuleHandle(NULL)) << endl << "Module Base: " << hex << int(d3dcompiler_47_og::moduleBase) << endl << endl;
	// Get keyboard keys and update their state. This is useful for using keyboard hooks, like pressing a key to do a certain function.

	Input::UpdateKeys();

	// If the state of isOnBattle is different, then it means we entered/quitted a battle
	if (ccGameProperties::isOnBattle() != prevBattle)
	{
		prevBattle = ccGameProperties::isOnBattle();
		if (prevBattle == 0)
		{
			// Code for when we quit a battle
			for (int x = 0; x < 2; x++)
			{
				cout << "Quit Battle" << endl;
				if (plMain[x] != 0)
				{
					DeleteCharacter(plMainId[x], x);
				}
			}
		}
		else
		{
			// Code for when we enter a battle
			for (int x = 0; x < 2; x++)
			{
				cout << "Entered Battle" << endl;
				if (stageNumber == 48 && stageselectedNumber == 1)
				{
					if (x == 0)
					{
						cout << "Sound Played" << endl;
						PlaySound(TEXT("mywavsound.wav"), NULL, SND_ASYNC);
					}
				}
				uintptr_t s = GetPlayerStatus(x);
				uintptr_t p = GetPlayerInfo(x);
				uintptr_t es = GetPlayerStatus(1 - x);
				uintptr_t ep = GetPlayerInfo(1 - x);

				if (s != 0 && p != 0)
				{
					int charaid = GetPlayerIntProperty(p, s, "characode");
					int echaraid = GetPlayerIntProperty(ep, es, "characode");
					// matchup[0] = charcode2str(charaid);
					// matchup[1] = charcode2str(echaraid);
					InitializeCharacter(charaid, x);
					inputState = (new ccBattleInputs());
				}
			}
		}
	}

	// If we're not in a battle, stop the code
	if (ccGameProperties::isOnBattle() == 0) return;
	// This is the loop code for every player.
	for (int x = 0; x < 2; x++)
	{
		cout << "2 Match Began" << endl;
		if (stageNumber == 48)
		{
			cout << "Test";
			PlaySound(TEXT("mywavsound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		// Get player x info
		uintptr_t s = GetPlayerStatus(x);
		uintptr_t p = GetPlayerInfo(x);
		float storm_gauge = GetStormGauge(x);
		int count = GetMatchCount();

		//if (x == 0) cout << hex << int(GetPlayerIntProperty(s, p, "characode")) << endl; Sleep(1000);
		//if (GetPlayerIntProperty(p, s, "attackid") == 151) { SetPlayerIntProperty(p, s, "attackid", 74); }
		//cout << "Match Count: " << *(int*)count << endl; Sleep(1000);
		//cout << "Storm Gauge: " << hex << *(float*)(int*)storm_gauge << endl; Sleep(1000);

		// Get enemy info
		uintptr_t es = GetPlayerStatus(1 - x);
		uintptr_t ep = GetPlayerInfo(1 - x);

		// Get Support Info
		uintptr_t ss1 = GetPlayerStatus(2 - x);
		uintptr_t sp1 = GetPlayerInfo(2 - x);
		uintptr_t ss2 = GetPlayerStatus(4 - x);
		uintptr_t sp2 = GetPlayerInfo(4 - x);
		uintptr_t ess1 = GetPlayerStatus(3 - x);
		uintptr_t esp1 = GetPlayerInfo(3 - x);
		uintptr_t ess2 = GetPlayerStatus(5 - x);
		uintptr_t esp2 = GetPlayerInfo(5 - x);

		// Sub Support Info

		// If pointers are null, stop the function.
		if (s == 0 || p == 0) return;

		// If pointers aren't null, let's check the health of the current player.
		float h = GetPlayerFloatProperty(p, s, "health");
		if (h <= 0) return; // If the health is 0 or less than 0, stop the code.

		//Stage Test

		// This disables armor break
		if (GetPlayerFloatProperty(p, s, "armor") < 45.0f) { SetPlayerFloatProperty(p, s, "armor", 45.0f); }
		if (GetPlayerFloatProperty(ep, es, "armor") < 45.0f) { SetPlayerFloatProperty(ep, es, "armor", 45.0f); }
		if (GetPlayerFloatProperty(sp1, ss1, "armor") < 45.0f) { SetPlayerFloatProperty(sp1, ss1, "armor", 45.0f); }
		if (GetPlayerFloatProperty(esp1, ess1, "armor") < 45.0f) { SetPlayerFloatProperty(esp1, ess1, "armor", 45.0f); }
		if (GetPlayerFloatProperty(sp2, ss2, "armor") < 45.0f) { SetPlayerFloatProperty(sp2, ss2, "armor", 45.0f); }
		if (GetPlayerFloatProperty(esp2, ess2, "armor") < 45.0f) { SetPlayerFloatProperty(esp2, ess2, "armor", 45.0f); }

		//Combo Properties on Tilt
		if (GetPlayerIntProperty(p, s, "pstate") == 66) { SetPlayerIntProperty(p, s, "pstate", 63); }
		if (GetPlayerIntProperty(ep, es, "pstate") == 66) { SetPlayerIntProperty(ep, es, "pstate", 63); }
		if (GetPlayerIntProperty(sp1, ss1, "pstate") == 66) { SetPlayerIntProperty(sp1, ss1, "pstate", 63); }
		//Enemy
		if (GetPlayerIntProperty(esp1, ess1, "pstate") == 66) { SetPlayerIntProperty(esp1, ess1, "pstate", 63); }
		if (GetPlayerIntProperty(sp2, ss2, "pstate") == 66) { SetPlayerIntProperty(sp2, ss2, "pstate", 63); }
		if (GetPlayerIntProperty(esp2, ess2, "pstate") == 66) { SetPlayerIntProperty(esp2, ess2, "pstate", 63); }

		//Better Air Dash
		if ((GetPlayerIntProperty(p, s, "pstate") == 16) && (GetPlayerIntProperty(p, s, "attackid") == 37)) { SetPlayerFloatProperty(p, s, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(p, s, "attackid") == 38) { SetPlayerFloatProperty(p, s, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(sp1, ss1, "pstate") == 16) && (GetPlayerIntProperty(sp1, ss1, "attackid") == 37)) { SetPlayerFloatProperty(sp1, ss1, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(sp1, ss1, "attackid") == 38) { SetPlayerFloatProperty(sp1, ss1, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(sp2, ss2, "pstate") == 16) && (GetPlayerIntProperty(sp2, ss2, "attackid") == 37)) { SetPlayerFloatProperty(sp2, ss2, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(sp2, ss2, "attackid") == 38) { SetPlayerFloatProperty(sp2, ss2, "anmspeed", 1.0f); }

		//Enemy
		if ((GetPlayerIntProperty(ep, es, "pstate") == 16) && (GetPlayerIntProperty(ep, es, "attackid") == 37)) { SetPlayerFloatProperty(ep, es, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(ep, es, "attackid") == 38) { SetPlayerFloatProperty(ep, es, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(esp1, ess1, "pstate") == 16) && (GetPlayerIntProperty(esp1, ess1, "attackid") == 37)) { SetPlayerFloatProperty(esp1, ess1, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(esp1, ess1, "attackid") == 38) { SetPlayerFloatProperty(esp1, ess1, "anmspeed", 1.0f); }
		if ((GetPlayerIntProperty(esp2, ess2, "pstate") == 16) && (GetPlayerIntProperty(esp2, ess2, "attackid") == 37)) { SetPlayerFloatProperty(esp2, ess2, "anmspeed", ACDStartup); }
		if (GetPlayerIntProperty(esp2, ess2, "attackid") == 38) { SetPlayerFloatProperty(esp2, ess2, "anmspeed", 1.0f); }

		//Cover Fire
		if ((GetPlayerIntProperty(p, s, "pstate") == 67) && (GetPlayerIntProperty(p, s, "attackid") == 151) && (GetPlayerIntProperty(p, s, "prevpstate") == 214)) { SetPlayerIntProperty(p, s, "npstate", 70); SetPlayerIntProperty(p, s, "pstateflag", 1); }
		if ((GetPlayerIntProperty(p, s, "pstate") == 68) && (GetPlayerIntProperty(p, s, "attackid") == 171) && (GetPlayerIntProperty(p, s, "prevpstate") == 214)) { SetPlayerIntProperty(p, s, "npstate", 71); SetPlayerIntProperty(p, s, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp1, ss1, "pstate") == 67) && (GetPlayerIntProperty(sp1, ss1, "attackid") == 151) && (GetPlayerIntProperty(sp1, ss1, "prevpstate") == 214)) { SetPlayerIntProperty(sp1, ss1, "npstate", 70); SetPlayerIntProperty(sp1, ss1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp1, ss1, "pstate") == 68) && (GetPlayerIntProperty(sp1, ss1, "attackid") == 171) && (GetPlayerIntProperty(sp1, ss1, "prevpstate") == 214)) { SetPlayerIntProperty(sp1, ss1, "npstate", 71); SetPlayerIntProperty(sp1, ss1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp2, ss2, "pstate") == 67) && (GetPlayerIntProperty(sp2, ss2, "attackid") == 151) && (GetPlayerIntProperty(sp2, ss2, "prevpstate") == 214)) { SetPlayerIntProperty(sp2, ss2, "npstate", 70); SetPlayerIntProperty(sp2, ss2, "pstateflag", 1); }
		if ((GetPlayerIntProperty(sp2, ss2, "pstate") == 68) && (GetPlayerIntProperty(sp2, ss2, "attackid") == 171) && (GetPlayerIntProperty(sp2, ss2, "prevpstate") == 214)) { SetPlayerIntProperty(sp2, ss2, "npstate", 71); SetPlayerIntProperty(sp2, ss2, "pstateflag", 1); }
		//Enemy
		if ((GetPlayerIntProperty(ep, es, "pstate") == 67) && (GetPlayerIntProperty(ep, es, "attackid") == 151) && (GetPlayerIntProperty(ep, es, "prevpstate") == 214)) { SetPlayerIntProperty(ep, es, "npstate", 70); SetPlayerIntProperty(ep, es, "pstateflag", 1); }
		if ((GetPlayerIntProperty(ep, es, "pstate") == 68) && (GetPlayerIntProperty(ep, es, "attackid") == 171) && (GetPlayerIntProperty(ep, es, "prevpstate") == 214)) { SetPlayerIntProperty(ep, es, "npstate", 71); SetPlayerIntProperty(ep, es, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp1, ess1, "pstate") == 67) && (GetPlayerIntProperty(esp1, ess1, "attackid") == 151) && (GetPlayerIntProperty(esp1, ess1, "prevpstate") == 214)) { SetPlayerIntProperty(esp1, ess1, "npstate", 70); SetPlayerIntProperty(esp1, ess1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp1, ess1, "pstate") == 68) && (GetPlayerIntProperty(esp1, ess1, "attackid") == 171) && (GetPlayerIntProperty(esp1, ess1, "prevpstate") == 214)) { SetPlayerIntProperty(esp1, ess1, "npstate", 71); SetPlayerIntProperty(esp1, ess1, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp2, ess2, "pstate") == 67) && (GetPlayerIntProperty(esp2, ess2, "attackid") == 151) && (GetPlayerIntProperty(esp2, ess2, "prevpstate") == 214)) { SetPlayerIntProperty(esp2, ess2, "npstate", 70); SetPlayerIntProperty(esp2, ess2, "pstateflag", 1); }
		if ((GetPlayerIntProperty(esp2, ess2, "pstate") == 68) && (GetPlayerIntProperty(esp2, ess2, "attackid") == 171) && (GetPlayerIntProperty(esp2, ess2, "prevpstate") == 214)) { SetPlayerIntProperty(esp2, ess2, "npstate", 71); SetPlayerIntProperty(esp2, ess2, "pstateflag", 1); }
		//"Support Health"
		


		/*
		//Sub Test Code
		float sub = GetPlayerFloatProperty(p, s, "sub");
		float support1sub = GetPlayerFloatProperty(sp1, ss1, "sub");
		float support2sub = GetPlayerFloatProperty(sp2, ss2, "sub");
		cout << "Flag: " << timeflag << endl;
		if (GetPlayerIntProperty(p, s, "pstate") == 109 && timeflag == 0 || GetPlayerIntProperty(p, s, "pstate") == 117 && timeflag == 0)
		{
			timeflag++;
			timer = 3000;
		}
		if (GetPlayerIntProperty(p, s, "pstate") == 109 || GetPlayerIntProperty(p, s, "pstate") == 117)
		{
			timer = 3000;
		}
		if (GetPlayerIntProperty(sp1, ss1, "pstate") == 109 && timeflag == 0 || GetPlayerIntProperty(sp1, ss1, "pstate") == 117 && timeflag == 0)
		{
			//support1timeflag++;
			//support1timer = 3000;
			timeflag++;
			timer = 3000;
		}
		if (GetPlayerIntProperty(sp1, ss1, "pstate") == 109 || GetPlayerIntProperty(sp1, ss1, "pstate") == 117)
		{
			//support1timer = 3000;
			timer = 3000;
		}
		if (GetPlayerIntProperty(sp2, ss2, "pstate") == 109 && timeflag == 0 || GetPlayerIntProperty(sp2, ss2, "pstate") == 117 && timeflag == 0)
		{
			//support2timeflag++;
			//support2timer = 3000;
			timeflag++;
			timer = 3000;
		}
		if (GetPlayerIntProperty(sp2, ss2, "pstate") == 109 || GetPlayerIntProperty(sp2, ss2, "pstate") == 117)
		{
			//support2timer = 3000;
			timer = 3000;
		}
		if (timeflag != 0)
		{
			if (timer != 0) timer--;
			cout << "Timer: " << timer << endl;
 			SetPlayerFloatProperty(p, s, "maxsub", sub);
			if (timer == 0)
			{
				timeflag = 0;
			}
		}
		/*if (support1timeflag != 0)
		{
			if (support1timer != 0) support1timer--;
			cout << "Support1Timer: " << support1timer << endl;
			SetPlayerFloatProperty(sp1, ss1, "maxsub", support1sub);
			SetPlayerFloatProperty(sp1, ss1, "health", h - 0.02f);
			if (support1timer == 0)
			{
				support1timeflag = 0;
			}
		}
		if (support2timeflag != 0)
		{
			if (support2timer != 0) support2timer--;
			cout << "Support2Timer: " << support2timer << endl;
			SetPlayerFloatProperty(sp2, ss2, "maxsub", support2sub);
			SetPlayerFloatProperty(sp2, ss2, "health", h - 0.02f);
			if (support2timer == 0)
			{
				support2timeflag = 0;
			}
		}*/
		
		if (timer == 0) { SetPlayerFloatProperty(p, s, "maxsub", 100.0f); }
		// Custom player code in here
		if (ccGameProperties::isOnMenu() == false && prevFrame != ccGeneralGameFunctions::GetCurrentFrame()) {
			DoCharacterLoop(GetPlayerIntProperty(p, s, "characode"), x);
			ccBattleInputs::Loop(x);
		}
	}
	// Get next frame
	prevFrame = ccGeneralGameFunctions::GetCurrentFrame();
}

uintptr_t ccPlayer::plMain[6] = { 0, 0, 0, 0, 0, 0 };
int ccPlayer::plMainId[6] = { 0, 0, 0, 0, 0, 0 };

#pragma region General Functions
vector<uintptr_t> ccPlayer::memcpy_verify(vector<uintptr_t> ptrs, vector<uintptr_t> offsets, size_t size) {
	// Validate that the proper data is being passed to the function
	if (!ptrs.empty() && !offsets.empty() && ptrs.size() == offsets.size() && size > 0) {
		uintptr_t off = 0; // Temporary offset variable to add to non-beginning offset values

		// Loop through the pointer list
		for (int i = 0; i < int(ptrs.size()); i++) {
			if (off == 0) memcpy(&ptrs[i], (void*)offsets[i], size); // memcpy on the first pointer
			else memcpy(&ptrs[i], (void*)(off + offsets[i]), size); // memcpy on the non-beginning pointers

			if (ptrs[i] == 0) break; // Stop any operations when a pointer is 0
			off = ptrs[i]; // If everything looks good, set the temporary offset var to the currently copied pointer.
		}
		return ptrs; // Return the resulting pointer list
	}
	else {
		return vector<uintptr_t>(ptrs.size(), 0); // If there's an error, return a list of 0 pointers
	}
}
int ccPlayer::LoopForNum(int loopAmt, uintptr_t compare, uintptr_t (*f)(int)) {
	int n = -1;
	for (int x = 0; x < loopAmt; x++)
	{
		if (compare == f(x)) n = x;
	}
	return n;
}
constexpr unsigned int ccPlayer::str2int(const char* str, int h = 0) { return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h]; }
string ccPlayer::charcode2str(int charcode) {
	switch (charcode) {
		case 0x01: return "2nrt";
		case 0x02: return "2nrx";
		case 0x03: return "2ssk";
		case 0x04: return "2ssy";
		case 0x05: return "2skr";
		case 0x06: return "2roc";
		case 0x07: return "2nej";
		case 0x08: return "2ten";
		case 0x09: return "2ino";
		case 0x0A: return "2sik";
		case 0x0B: return "2tyo";
		case 0x0C: return "2kib";
		case 0x0D: return "2sin";
		case 0x0E: return "2hnt";
		case 0x0F: return "2gar";
		case 0x10: return "2knk";
		case 0x11: return "2tmr";
		case 0x12: return "2kks";
		case 0x13: return "2guy";
		case 0x14: return "2asm";
		case 0x15: return "2jry";
		case 0x16: return "2tnd";
		case 0x17: return "2orc";
		case 0x18: return "2kbt";
		case 0x19: return "2itc";
		case 0x1A: return "2ksm";
		case 0x1B: return "2cyb";
		case 0x1C: return "2sai";
		case 0x1D: return "2ymt";
		case 0x1E: return "2sco";
		case 0x1F: return "2ddr";
		case 0x20: return "2hdn";
		case 0x21: return "2kzu";
		case 0x22: return "2sgt";
		case 0x23: return "2jug";
		case 0x24: return "2kar";
		case 0x25: return "2tob";
		case 0x26: return "2knn";
		case 0x27: return "2pea";
		case 0x28: return "2klb";
		case 0x29: return "2akm";
		case 0x2A: return "2krs";
		case 0x2B: return "2par";
		case 0x2C: return "2kkg";
		case 0x2D: return "2fou";
		case 0x2E: return "1nrt";
		case 0x2F: return "1ssk";
		case 0x30: return "1skr";
		case 0x31: return "1roc";
		case 0x32: return "1nej";
		case 0x33: return "1hnt";
		case 0x34: return "1gar";
		case 0x35: return "1hkg";
		case 0x36: return "1kmm";
		case 0x37: return "2nrg";
		case 0x38: return "2ssz";
		case 0x39: return "2mdr";
		case 0x3A: return "2dnz";
		case 0x3B: return "2rkg";
		case 0x3C: return "2tkg";
		case 0x3D: return "2mkg";
		case 0x3E: return "1zbz";
		case 0x3F: return "1hak";
		case 0x40: return "1fir";
		case 0x41: return "1sec";
		case 0x42: return "2kkx";
		case 0x43: return "2obt";
		case 0x44: return "2kbx";
		case 0x45: return "2scx";
		case 0x46: return "3mdr";
		case 0x47: return "3dri";
		case 0x48: return "3rus";
		case 0x49: return "3tob";
		case 0x4A: return "3ygr";
		case 0x4B: return "3utk";
		case 0x4C: return "3mfn";
		case 0x4D: return "3han";
		case 0x4E: return "3nyg";
		case 0x4F: return "3who";
		case 0x50: return "3klb";
		case 0x51: return "3hnz";
		case 0x52: return "3ngt";
		case 0x53: return "3tyo";
		case 0x54: return "3nrt";
		case 0x55: return "3ssk";
		case 0x56: return "3gar";
		case 0x57: return "4mkg";
		case 0x58: return "4muu";
		case 0x59: return "4rkg";
		case 0x5A: return "4kkg";
		case 0x5B: return "3kks";
		case 0x5C: return "3khm";
		case 0x5D: return "3irk";
		case 0x5E: return "3kbt";
		case 0x5F: return "3obt";
		case 0x60: return "4ssi";
		case 0x61: return "1ten";
		case 0x62: return "1ino";
		case 0x63: return "1sik";
		case 0x64: return "1tyo";
		case 0x65: return "1kib";
		case 0x66: return "1akm";
		case 0x67: return "1sin";
		case 0x68: return "1tmr";
		case 0x69: return "1knk";
		case 0x6A: return "1krs";
		case 0x6B: return "4nrt";
		case 0x6C: return "3ksn";
		case 0x6D: return "3mnt";
		case 0x6E: return "3hsm";
		case 0x6F: return "3mdr_2";
		case 0x70: return "2gav";
		case 0x71: return "5obt";
		case 0x72: return "5mdr";
		case 0x73: return "5jrb";
		case 0x74: return "5kdm";
		case 0x75: return "5skn";
		case 0x76: return "5tyy";
		case 0x77: return "bhsm";
		case 0x78: return "bmdr";
		case 0x79: return "bmkj";
		case 0x7A: return "4rin";
		case 0x7B: return "6nrt";
		case 0x7C: return "5kgy";
		case 0x7D: return "tyyp";
		case 0x7E: return "6ssk";
		case 0x7F: return "6hnt";
		case 0x80: return "6skr";
		case 0x81: return "5nrt";
		case 0x82: return "5ssk";
		case 0x83: return "6hnb";
		case 0x84: return "2obx";
		case 0x85: return "bjb1";
		case 0x86: return "bjb2";
		case 0x87: return "bjb3";
		case 0x88: return "bjb4";
		case 0x89: return "b4nr";
		case 0x8A: return "bkkx";
		case 0x8B: return "b5ob";
		case 0x8C: return "bkrl";
		case 0x8D: return "bssn";
		case 0x8E: return "bobt";
		case 0x8F: return "bgkt";
		case 0x90: return "baod";
		case 0x91: return "bkty";
		case 0x92: return "b2nr";
		case 0x93: return "1jbr";
		case 0x94: return "2jbr";
		case 0x95: return "3jbr";
		case 0x96: return "4jbr";
		case 0x97: return "5jbr";
		case 0x98: return "6jbr";
		case 0x99: return "gfsa";
		case 0x9A: return "bjyd";
		case 0x9B: return "bkrs";
		case 0x9C: return "gmhr";
		case 0x9D: return "btsk";
		case 0x9E: return "bkku";
		case 0x9F: return "7brt";
		case 0xA0: return "7sld";
		case 0xA1: return "bgrg";
		case 0xA2: return "gztu";
		case 0xA3: return "bobr";
		case 0xA4: return "bobs";
		case 0xA5: return "bmdj";
		case 0xA6: return "brmd";
		case 0xA7: return "brsk";
		case 0xA8: return "bkms";
		case 0xA9: return "bksr";
		case 0xAA: return "bgyu";
		case 0xAB: return "bjyg";
		case 0xAC: return "bnrt";
		case 0xAD: return "bssk";
		case 0xAE: return "bkgy";
		case 0xAF: return "bobz";
		case 0xB0: return "bkgv";
		case 0xB1: return "bkkk";
		case 0xB2: return "bnrx";
		case 0xB3: return "bssx";
		case 0xB4: return "bnrc";
		case 0xB5: return "bssc";
		case 0xB6: return "jkks";
		case 0xB7: return "bobk";
		case 0xB8: return "5krs";
		case 0xB9: return "b6bt";
		case 0xBA: return "bkks";
		case 0xBB: return "bmdt";
		case 0xBC: return "bmdk";
		case 0xBD: return "bmhr";
		case 0xBE: return "7nrt";
		case 0xBF: return "7ssk";
		case 0xC0: return "bnrg";
		case 0xC1: return "bssz";
		case 0xC2: return "b1nr";
		case 0xC3: return "b1ss";
		case 0xC4: return "3guy";
		case 0xC5: return "b3hs";
		case 0xC6: return "bguy";
		case 0xC7: return "bgrn";
		case 0xC8: return "7nrn";
		case 0xC9: return "7ssx";
		case 0xCA: return "7skr";
		case 0xCB: return "7gar";
		case 0xCC: return "7khm";
		case 0xCD: return "7brn";
		case 0xCE: return "7brx";
		case 0xCF: return "7sln";
		case 0xD0: return "7skd";
		case 0xD1: return "7mms";
		case 0xD2: return "7kin";
		case 0xD3: return "7yri";
		case 0xD4: return "4mnr";
	case 0xD5: return "biss";
	case 0xD6: return "bmnk";
	case 0xD7: return "7mmv";
	case 0xD8: return "7mtk";
	case 0xD9: return "abrt";
	case 0xDA: return "8mms";
	case 0xDB: return "8kin";
	case 0xDC: return "8ino";
	case 0xDD: return "8sik";
	case 0xDE: return "8tyo";
	case 0xDF: return "8kib";
	case 0xE0: return "8sin";
	case 0xE1: return "8roc";
	case 0xE2: return "8ten";
	case 0xE3: return "8knk";
	case 0xE4: return "8tmr";
	case 0xE5: return "8sai";
	case 0xE6: return "8aem";
	case 0xE7: return "rskr";
	case 0xE8: return "3ssy";
	case 0xE9: return "2lar";
	}
}
void ccPlayer::SetTimerValue(int timerValue, int maxTimer, bool value) {
	if (timerValue < 0 && !value) timerValue--;
	if (timerValue >= 0) {
		value = true;
		timerValue = maxTimer;
	}
}
#pragma endregion

#pragma region GetPlayer Functions
// Placeholder functions
int ccPlayer::GetCanDoJutsuChakra(uintptr_t p, uintptr_t s) { return 0; }
int ccPlayer::GetAwakenedState(uintptr_t p, uintptr_t s) { return 0; }

uintptr_t ccPlayer::GetSystemInfo()
{
	uintptr_t result;
	memcpy(&result, (void*)d3dcompiler_47_og::systemInfo, 8);;
	return result;
}
uintptr_t ccPlayer::GetStormPointer(int n) { return GetSystemInfo() + (n == 0 ? 0x4C : 0xB4); }
float ccPlayer::GetStormGauge(int n) { return *(float*)GetStormPointer(n); }
uintptr_t ccPlayer::GetMatchPointer() { return GetSystemInfo() + 0x1E8; }
int ccPlayer::GetMatchCount() { return *(int*)GetMatchPointer(); }
uintptr_t ccPlayer::GetPlayerLSCostPointer(uintptr_t p) {
	
	// Initialize pointers
	uintptr_t p1 = 0, p2 = 0, p3 = 0;
	vector<uintptr_t> ptrs, offsets;

	// Execute memory copy/verification functionalities
	memcpy(&p2, (void*)(p + 0x14E20), 8);
	p3 = p2 + 0x10;
	return !(p3 == 0) ? p3 : 0;
}
uintptr_t ccPlayer::GetPlayerStatus(int n)
{
	// Initialize pointers and the core offset
	uintptr_t p1 = 0, p2 = 0, p3 = 0, p4 = 0;
	uintptr_t mb_offset = d3dcompiler_47_og::moduleBase - 0xC00 + 0x161B738;
	vector<uintptr_t> ptrs, offsets;

	// Depending on whether "n" is set to 1 or not will change which offsets we use
	switch (n)
	{
		// Player 2
		case 1: offsets = { mb_offset, 0x20, 0x90 }; break;
		// Player 1 Support 1
		case 2: offsets = { mb_offset, 0x20, 0x08 }; break;
		// Player 2 Support 1
		case 3: offsets = { mb_offset, 0x20, 0x98 }; break;
		// Player 1 Support 2
		case 4: offsets = { mb_offset, 0x20, 0x10 }; break;
		// Player 2 Support 2
		case 5: offsets = { mb_offset, 0x20, 0xA0 }; break;
		// Player 1
		default: offsets = { mb_offset, 0x20, 0x00 }; break;
	}
	// Execute memory copy/verification functionalities
	ptrs = memcpy_verify({ p1, p2, p3 }, offsets, 8);
	p1 = ptrs[0], p2 = ptrs[1], p3 = ptrs[2];
	if (p1 == 0 || p2 == 0 || p3 == 0) return 0;

	// If the memory pointers all copied properly, return the resulting pointer offset by 0x38, if valid
	p4 = p3 + 0x38;

	return !(p4 == 0) ? p4 : 0;
}
uintptr_t ccPlayer::GetPlayerInfo(int n)
{
	uintptr_t a = ccPlayer::GetPlayerStatus(n);
	if (a == 0) return 0;
	uintptr_t b = a - 8;
	uintptr_t c = 0;
	memcpy(&c, (void*)b, 8);
	return c + 0x70;
}

int ccPlayer::GetPlayerStatusNumber(uintptr_t s) { return LoopForNum(2, s, ccPlayer::GetPlayerStatus); }
int ccPlayer::GetPlayerInfoNumber(uintptr_t p) { return LoopForNum(2, p, ccPlayer::GetPlayerInfo); }



// The function below gets a float pointer from the player.
float* ccPlayer::GetPlayerFloatPointer(uintptr_t p, uintptr_t s, char* prop)
{
	float* result;

	if (s == 0 || p == 0) return 0;

	switch (ccGameProperties::str2int(prop))
	{
		case ccPlayer::str2int("posx"): result = (float*)(p + 0x00); break;
		case ccPlayer::str2int("posz"): result = (float*)(p + 0x04); break;
		case ccPlayer::str2int("posy"): result = (float*)(p + 0x08); break;
		case ccPlayer::str2int("health"): result = (float*)(s + 0x00); break;
		case ccPlayer::str2int("maxhealth"): result = (float*)(s + 0x04); break;
		case ccPlayer::str2int("chakra"): result = (float*)(s + 0x08); break;
		case ccPlayer::str2int("maxchakra"): result = (float*)(s + 0x0C); break;
		case ccPlayer::str2int("sub"): result = (float*)(s + 0x10); break;
		case ccPlayer::str2int("maxsub"): result = (float*)(s + 0x14); break;
		case ccPlayer::str2int("armor"): result = (float*)(s + 0x20); break;
		case ccPlayer::str2int("maxarmor"): result = (float*)(s + 0x24); break;
		case ccPlayer::str2int("gravity"): result = (float*)(p + 0xE8); break;
		case ccPlayer::str2int("zmomentum"): result = (float*)(p + 0xEC); break;
		case ccPlayer::str2int("modelscale"): result = (float*)(p + 0x190); break;
		case ccPlayer::str2int("anmspeed"): result = (float*)(p + 0x1020); break;
		case ccPlayer::str2int("movespeed"): result = (float*)(p + 0x14104); break;
		case ccPlayer::str2int("guard"): result = (float*)(p + 0x149F0); break;
		case ccPlayer::str2int("maxguard"): result = (float*)(p + 0x149F4); break;
	}

	return result;
}

float ccPlayer::GetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop)
{
	float* ptr = GetPlayerFloatPointer(p, s, prop);

	if (ptr == 0) return 0;

	return *ptr;
}

int* ccPlayer::GetPlayerIntPointer(uintptr_t p, uintptr_t s, char* prop)
{
	int* val;

	switch (ccPlayer::str2int(prop))
	{
		case ccPlayer::str2int("uitem"): val = (int*)(s + 0x38); break;
		case ccPlayer::str2int("ditem"): val = (int*)(s + 0x3C); break;
		case ccPlayer::str2int("litem"): val = (int*)(s + 0x40); break;
		case ccPlayer::str2int("ritem"): val = (int*)(s + 0x44); break;
		case ccPlayer::str2int("characode"): val = (int*)(p + 0xC1C); break;
		case ccPlayer::str2int("enablechar"): val = (int*)(p + 0xC38); break;
		case ccPlayer::str2int("cancontrol"): val = (int*)(p + 0xC3C); break;
		case ccPlayer::str2int("enableanm"): val = (int*)(p + 0xC40); break;
		case ccPlayer::str2int("displaymdl"): val = (int*)(p + 0xC48); break;
		case ccPlayer::str2int("pstate"): val = (int*)(p + 0xC50); break;
		case ccPlayer::str2int("prevpstate"): val = (int*)(p + 0xC54); break;
		case ccPlayer::str2int("npstate"): val = (int*)(p + 0xC58); break;
		case ccPlayer::str2int("pstateflag"): val = (int*)(p + 0xC6C); break;
		case ccPlayer::str2int("attackid"): val = (int*)(p + 0x1010); break;
		case ccPlayer::str2int("prevattackid"): val = (int*)(p + 0x1024); break;
		case ccPlayer::str2int("anmtimer"): val = (int*)(p + 0x14138); break;
	}

	return val;
}

int ccPlayer::GetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop)
{
	int* val = GetPlayerIntPointer(p, s, prop);
	return *val;
}

// Gets the player position in a Vector3
Vector3 ccPlayer::GetPlayerPosition(uintptr_t p, uintptr_t s)
{
	return Vector3
	(
		GetPlayerFloatProperty(p, s, "posx"),
		GetPlayerFloatProperty(p, s, "posy"),
		GetPlayerFloatProperty(p, s, "posz")
	);
}

// Calculates the distance between two given players
float ccPlayer::GetPlayerDistance(uintptr_t p, uintptr_t s, uintptr_t ep, uintptr_t es)
{
	return Vector3::Distance(GetPlayerPosition(p, s), GetPlayerPosition(ep, es));
}
#pragma endregion

#pragma region SetPlayer Functions
void ccPlayer::SetPlayerLSCost(uintptr_t p, float value) {
	float* ptr = (float*)GetPlayerLSCostPointer(p);
	*ptr = value > 0 ? value : 0.01f;
}
void ccPlayer::SetStormGauge(int n, float value) {
	float* ptr = (float*)(GetSystemInfo() + (n == 0 ? 0x4C : 0xB4));
	*ptr = value > 0 ? value : 0.01f;
}
void ccPlayer::SetMatchCount(int value) {
	int* ptr = (int*)(GetSystemInfo() + 0x1E8);
	*ptr = value > 0 ? value : 1;
	cout << "New Count Value: " << hex << int(*ptr) << endl;
}

// The function below sets a float property from the player to a specific value
void ccPlayer::SetPlayerFloatProperty(uintptr_t p, uintptr_t s, char* prop, float value)
{
	float* ptr = GetPlayerFloatPointer(p, s, prop);

	if (ptr == 0) return;

	*ptr = value > 0 ? value : 0.01f;
}

void ccPlayer::SetPlayerIntProperty(uintptr_t p, uintptr_t s, char* prop, int value)
{
	int* val = GetPlayerIntPointer(p, s, prop);
	*val = value > 0 ? value : 1;
}
void ccPlayer::SetPlayerStateProperty(uintptr_t p, uintptr_t s, int prop) {
	int* nps = GetPlayerIntPointer(p, s, "npstate");
	int* psf = GetPlayerIntPointer(p, s, "pstateflag");

	*psf = 1;
	*nps = prop;
}
// Unfinished, needs a list of all properties we know of
void ccPlayer::SetPlayerStatePropertyEasy(uintptr_t p, uintptr_t s, char* prop) {
	int* nps = GetPlayerIntPointer(p, s, "npstate");
	int* psf = GetPlayerIntPointer(p, s, "pstateflag");

}
#pragma endregion

#pragma region Character Functions
void ccPlayer::InitializeCharacter(int c, int plNum)
{
	uintptr_t plm = 0;

	c1CMN* cmn = (new c1CMN(plNum));
	switch (c)
	{
		/*
		#pragma region 1
		{ case 0x66: c1AKM * c_1akm = (new c1AKM(plNum)); plm = (DWORD)(c_1akm); plMain[plNum] = plm; } break;
		{ case 0x40: c1FIR * c_1fir = (new c1FIR(plNum)); plm = (DWORD)(c_1fir); plMain[plNum] = plm; } break;
		{ case 0x34: c1GAR * c_1gar = (new c1GAR(plNum)); plm = (DWORD)(c_1gar); plMain[plNum] = plm; } break;
		{ case 0x3F: c1HAK * c_1hak = (new c1HAK(plNum)); plm = (DWORD)(c_1hak); plMain[plNum] = plm; } break;
		{ case 0x35: c1HKG * c_1hkg = (new c1HKG(plNum)); plm = (DWORD)(c_1hkg); plMain[plNum] = plm; } break;
		{ case 0x33: c1HNT * c_1hnt = (new c1HNT(plNum)); plm = (DWORD)(c_1hnt); plMain[plNum] = plm; } break;
		{ case 0x62: c1INO * c_1ino = (new c1INO(plNum)); plm = (DWORD)(c_1ino); plMain[plNum] = plm; } break;
		{ case 0x93: c1JBR * c_1jbr = (new c1JBR(plNum)); plm = (DWORD)(c_1jbr); plMain[plNum] = plm; } break;
		{ case 0x65: c1KIB * c_1kib = (new c1KIB(plNum)); plm = (DWORD)(c_1kib); plMain[plNum] = plm; } break;
		{ case 0x36: c1KMM * c_1kmm = (new c1KMM(plNum)); plm = (DWORD)(c_1kmm); plMain[plNum] = plm; } break;
		{ case 0x69: c1KNK * c_1knk = (new c1KNK(plNum)); plm = (DWORD)(c_1knk); plMain[plNum] = plm; } break;
		{ case 0x6A: c1KRS * c_1krs = (new c1KRS(plNum)); plm = (DWORD)(c_1krs); plMain[plNum] = plm; } break;
		{ case 0x32: c1NEJ * c_1nej = (new c1NEJ(plNum)); plm = (DWORD)(c_1nej); plMain[plNum] = plm; } break;
		{ case 0x2E: c1NRT * c_1nrt = (new c1NRT(plNum)); plm = (DWORD)(c_1nrt); plMain[plNum] = plm; } break;
		{ case 0x31: c1ROC * c_1roc = (new c1ROC(plNum)); plm = (DWORD)(c_1roc); plMain[plNum] = plm; } break;
		{ case 0x41: c1SEC * c_1sec = (new c1SEC(plNum)); plm = (DWORD)(c_1sec); plMain[plNum] = plm; } break;
		{ case 0x63: c1SIK * c_1sik = (new c1SIK(plNum)); plm = (DWORD)(c_1sik); plMain[plNum] = plm; } break;
		{ case 0x67: c1SIN * c_1sin = (new c1SIN(plNum)); plm = (DWORD)(c_1sin); plMain[plNum] = plm; } break;
		{ case 0x30: c1SKR * c_1skr = (new c1SKR(plNum)); plm = (DWORD)(c_1skr); plMain[plNum] = plm; } break;
		{ case 0x2F: c1SSK * c_1ssk = (new c1SSK(plNum)); plm = (DWORD)(c_1ssk); plMain[plNum] = plm; } break;
		{ case 0x61: c1TEN * c_1ten = (new c1TEN(plNum)); plm = (DWORD)(c_1ten); plMain[plNum] = plm; } break;
		{ case 0x68: c1TMR * c_1tmr = (new c1TMR(plNum)); plm = (DWORD)(c_1tmr); plMain[plNum] = plm; } break;
		{ case 0x64: c1TYO * c_1tyo = (new c1TYO(plNum)); plm = (DWORD)(c_1tyo); plMain[plNum] = plm; } break;
		{ case 0x3E: c1ZBZ * c_1zbz = (new c1ZBZ(plNum)); plm = (DWORD)(c_1zbz); plMain[plNum] = plm; } break;
		#pragma endregion
		#pragma region 2
		{ case 0x29: c2AKM * c_2akm = (new c2AKM(plNum)); plm = (DWORD)(c_2akm); plMain[plNum] = plm; } break;
		{ case 0x14: c2ASM * c_2asm = (new c2ASM(plNum)); plm = (DWORD)(c_2asm); plMain[plNum] = plm; } break;
		{ case 0x1B: c2CYB * c_2cyb = (new c2CYB(plNum)); plm = (DWORD)(c_2cyb); plMain[plNum] = plm; } break;
		{ case 0x1F: c2DDR * c_2ddr = (new c2DDR(plNum)); plm = (DWORD)(c_2ddr); plMain[plNum] = plm; } break;
		{ case 0x3A: c2DNZ * c_2dnz = (new c2DNZ(plNum)); plm = (DWORD)(c_2dnz); plMain[plNum] = plm; } break;
		{ case 0x2D: c2FOU * c_2fou = (new c2FOU(plNum)); plm = (DWORD)(c_2fou); plMain[plNum] = plm; } break;
		{ case 0x0F: c2GAR * c_2gar = (new c2GAR(plNum)); plm = (DWORD)(c_2gar); plMain[plNum] = plm; } break;
		{ case 0x70: c2GAV * c_2gav = (new c2GAV(plNum)); plm = (DWORD)(c_2gav); plMain[plNum] = plm; } break;
		{ case 0x13: c2GUY * c_2guy = (new c2GUY(plNum)); plm = (DWORD)(c_2guy); plMain[plNum] = plm; } break;
		{ case 0x20: c2HDN * c_2hdn = (new c2HDN(plNum)); plm = (DWORD)(c_2hdn); plMain[plNum] = plm; } break;
		{ case 0x0E: c2HNT * c_2hnt = (new c2HNT(plNum)); plm = (DWORD)(c_2hnt); plMain[plNum] = plm; } break;
		{ case 0x09: c2INO * c_2ino = (new c2INO(plNum)); plm = (DWORD)(c_2ino); plMain[plNum] = plm; } break;
		{ case 0x19: c2ITC * c_2itc = (new c2ITC(plNum)); plm = (DWORD)(c_2itc); plMain[plNum] = plm; } break;
		{ case 0x94: c2JBR * c_2jbr = (new c2JBR(plNum)); plm = (DWORD)(c_2jbr); plMain[plNum] = plm; } break;
		{ case 0x15: c2JRY * c_2jry = (new c2JRY(plNum)); plm = (DWORD)(c_2jry); plMain[plNum] = plm; } break;
		{ case 0x23: c2JUG * c_2jug = (new c2JUG(plNum)); plm = (DWORD)(c_2jug); plMain[plNum] = plm; } break;
		{ case 0x24: c2KAR * c_2kar = (new c2KAR(plNum)); plm = (DWORD)(c_2kar); plMain[plNum] = plm; } break;
		{ case 0x18: c2KBT * c_2kbt = (new c2KBT(plNum)); plm = (DWORD)(c_2kbt); plMain[plNum] = plm; } break;
		{ case 0x44: c2KBX * c_2kbx = (new c2KBX(plNum)); plm = (DWORD)(c_2kbx); plMain[plNum] = plm; } break;
		{ case 0x0C: c2KIB * c_2kib = (new c2KIB(plNum)); plm = (DWORD)(c_2kib); plMain[plNum] = plm; } break;
		{ case 0x2C: c2KKG * c_2kkg = (new c2KKG(plNum)); plm = (DWORD)(c_2kkg); plMain[plNum] = plm; } break;
		{ case 0x12: c2KKS * c_2kks = (new c2KKS(plNum)); plm = (DWORD)(c_2kks); plMain[plNum] = plm; } break;
		{ case 0x42: c2KKX * c_2kkx = (new c2KKX(plNum)); plm = (DWORD)(c_2kkx); plMain[plNum] = plm; } break;
		{ case 0x28: c2KLB * c_2klb = (new c2KLB(plNum)); plm = (DWORD)(c_2klb); plMain[plNum] = plm; } break;
		{ case 0x10: c2KNK * c_2knk = (new c2KNK(plNum)); plm = (DWORD)(c_2knk); plMain[plNum] = plm; } break;
		{ case 0x26: c2KNN * c_2knn = (new c2KNN(plNum)); plm = (DWORD)(c_2knn); plMain[plNum] = plm; } break;
		{ case 0x2A: c2KRS * c_2krs = (new c2KRS(plNum)); plm = (DWORD)(c_2krs); plMain[plNum] = plm; } break;
		{ case 0x1A: c2KSM * c_2ksm = (new c2KSM(plNum)); plm = (DWORD)(c_2ksm); plMain[plNum] = plm; } break;
		{ case 0x21: c2KZU * c_2kzu = (new c2KZU(plNum)); plm = (DWORD)(c_2kzu); plMain[plNum] = plm; } break;
		{ case 0x39: c2MDR * c_2mdr = (new c2MDR(plNum)); plm = (DWORD)(c_2mdr); plMain[plNum] = plm; } break;
		{ case 0x3D: c2MKG * c_2mkg = (new c2MKG(plNum)); plm = (DWORD)(c_2mkg); plMain[plNum] = plm; } break;
		{ case 0x07: c2NEJ * c_2nej = (new c2NEJ(plNum)); plm = (DWORD)(c_2nej); plMain[plNum] = plm; } break;
		{ case 0x37: c2NRG * c_2nrg = (new c2NRG(plNum)); plm = (DWORD)(c_2nrg); plMain[plNum] = plm; } break;
		{ case 0x01: c2NRT * c_2nrt = (new c2NRT(plNum)); plm = (DWORD)(c_2nrt); plMain[plNum] = plm; } break;
		{ case 0x02: c2NRX * c_2nrx = (new c2NRX(plNum)); plm = (DWORD)(c_2nrx); plMain[plNum] = plm; } break;
		{ case 0x43: c2OBT * c_2obt = (new c2OBT(plNum)); plm = (DWORD)(c_2obt); plMain[plNum] = plm; } break;
		{ case 0x84: c2OBX * c_2obx = (new c2OBX(plNum)); plm = (DWORD)(c_2obx); plMain[plNum] = plm; } break;
		{ case 0x17: c2ORC * c_2orc = (new c2ORC(plNum)); plm = (DWORD)(c_2orc); plMain[plNum] = plm; } break;
		{ case 0x2B: c2PAR * c_2par = (new c2PAR(plNum)); plm = (DWORD)(c_2par); plMain[plNum] = plm; } break;
		{ case 0x27: c2PEA * c_2pea = (new c2PEA(plNum)); plm = (DWORD)(c_2pea); plMain[plNum] = plm; } break;
		{ case 0x3B: c2RKG * c_2rkg = (new c2RKG(plNum)); plm = (DWORD)(c_2rkg); plMain[plNum] = plm; } break;
		{ case 0x06: c2ROC * c_2roc = (new c2ROC(plNum)); plm = (DWORD)(c_2roc); plMain[plNum] = plm; } break;
		{ case 0x1C: c2SAI * c_2sai = (new c2SAI(plNum)); plm = (DWORD)(c_2sai); plMain[plNum] = plm; } break;
		{ case 0x1E: c2SCO * c_2sco = (new c2SCO(plNum)); plm = (DWORD)(c_2sco); plMain[plNum] = plm; } break;
		{ case 0x45: c2SCX * c_2scx = (new c2SCX(plNum)); plm = (DWORD)(c_2scx); plMain[plNum] = plm; } break;
		{ case 0x22: c2SGT * c_2sgt = (new c2SGT(plNum)); plm = (DWORD)(c_2sgt); plMain[plNum] = plm; } break;
		{ case 0x0A: c2SIK * c_2sik = (new c2SIK(plNum)); plm = (DWORD)(c_2sik); plMain[plNum] = plm; } break;
		{ case 0x0D: c2SIN * c_2sin = (new c2SIN(plNum)); plm = (DWORD)(c_2sin); plMain[plNum] = plm; } break;
		{ case 0x05: c2SKR * c_2skr = (new c2SKR(plNum)); plm = (DWORD)(c_2skr); plMain[plNum] = plm; } break;
		{ case 0x03: c2SSK * c_2ssk = (new c2SSK(plNum)); plm = (DWORD)(c_2ssk); plMain[plNum] = plm; } break;
		{ case 0x04: c2SSY * c_2ssy = (new c2SSY(plNum)); plm = (DWORD)(c_2ssy); plMain[plNum] = plm; } break;
		{ case 0x38: c2SSZ * c_2ssz = (new c2SSZ(plNum)); plm = (DWORD)(c_2ssz); plMain[plNum] = plm; } break;
		{ case 0x08: c2TEN * c_2ten = (new c2TEN(plNum)); plm = (DWORD)(c_2ten); plMain[plNum] = plm; } break;
		{ case 0x3C: c2TKG * c_2tkg = (new c2TKG(plNum)); plm = (DWORD)(c_2tkg); plMain[plNum] = plm; } break;
		{ case 0x11: c2TMR * c_2tmr = (new c2TMR(plNum)); plm = (DWORD)(c_2tmr); plMain[plNum] = plm; } break;
		{ case 0x16: c2TND * c_2tnd = (new c2TND(plNum)); plm = (DWORD)(c_2tnd); plMain[plNum] = plm; } break;
		{ case 0x25: c2TOB * c_2tob = (new c2TOB(plNum)); plm = (DWORD)(c_2tob); plMain[plNum] = plm; } break;
		{ case 0x0B: c2TYO * c_2tyo = (new c2TYO(plNum)); plm = (DWORD)(c_2tyo); plMain[plNum] = plm; } break;
		{ case 0x1D: c2YMT * c_2ymt = (new c2YMT(plNum)); plm = (DWORD)(c_2ymt); plMain[plNum] = plm; } break;
		#pragma endregion
		#pragma region 3
		{ case 0x47: c3DRI * c_3dri = (new c3DRI(plNum)); plm = (DWORD)(c_3dri); plMain[plNum] = plm; } break;
		{ case 0x56: c3GAR * c_3gar = (new c3GAR(plNum)); plm = (DWORD)(c_3gar); plMain[plNum] = plm; } break;
		{ case 0xC4: c3GUY * c_3guy = (new c3GUY(plNum)); plm = (DWORD)(c_3guy); plMain[plNum] = plm; } break;
		{ case 0x4D: c3HAN * c_3han = (new c3HAN(plNum)); plm = (DWORD)(c_3han); plMain[plNum] = plm; } break;
		{ case 0x51: c3HNZ * c_3hnz = (new c3HNZ(plNum)); plm = (DWORD)(c_3hnz); plMain[plNum] = plm; } break;
		{ case 0x6E: c3HSM * c_3hsm = (new c3HSM(plNum)); plm = (DWORD)(c_3hsm); plMain[plNum] = plm; } break;
		{ case 0x5D: c3IRK * c_3irk = (new c3IRK(plNum)); plm = (DWORD)(c_3irk); plMain[plNum] = plm; } break;
		{ case 0x95: c3JBR * c_3jbr = (new c3JBR(plNum)); plm = (DWORD)(c_3jbr); plMain[plNum] = plm; } break;
		{ case 0x5E: c3KBT * c_3kbt = (new c3KBT(plNum)); plm = (DWORD)(c_3kbt); plMain[plNum] = plm; } break;
		{ case 0x5C: c3KHM * c_3khm = (new c3KHM(plNum)); plm = (DWORD)(c_3khm); plMain[plNum] = plm; } break;
		{ case 0x5B: c3KKS * c_3kks = (new c3KKS(plNum)); plm = (DWORD)(c_3kks); plMain[plNum] = plm; } break;
		{ case 0x50: c3KLB * c_3klb = (new c3KLB(plNum)); plm = (DWORD)(c_3klb); plMain[plNum] = plm; } break;
		{ case 0x6C: c3KSN * c_3ksn = (new c3KSN(plNum)); plm = (DWORD)(c_3ksn); plMain[plNum] = plm; } break;
		{ case 0x46: c3MDR * c_3mdr = (new c3MDR(plNum)); plm = (DWORD)(c_3mdr); plMain[plNum] = plm; } break;
		{ case 0x6F: c3MDR_2 * c_3mdr_2 = (new c3MDR_2(plNum)); plm = (DWORD)(c_3mdr_2); plMain[plNum] = plm; } break;
		{ case 0x4C: c3MFN * c_3mfn = (new c3MFN(plNum)); plm = (DWORD)(c_3mfn); plMain[plNum] = plm; } break;
		{ case 0x6D: c3MNT * c_3mnt = (new c3MNT(plNum)); plm = (DWORD)(c_3mnt); plMain[plNum] = plm; } break;
		{ case 0x52: c3NGT * c_3ngt = (new c3NGT(plNum)); plm = (DWORD)(c_3ngt); plMain[plNum] = plm; } break;
		{ case 0x54: c3NRT * c_3nrt = (new c3NRT(plNum)); plm = (DWORD)(c_3nrt); plMain[plNum] = plm; } break;
		{ case 0x4E: c3NYG * c_3nyg = (new c3NYG(plNum)); plm = (DWORD)(c_3nyg); plMain[plNum] = plm; } break;
		{ case 0x5F: c3OBT * c_3obt = (new c3OBT(plNum)); plm = (DWORD)(c_3obt); plMain[plNum] = plm; } break;
		{ case 0x48: c3RUS * c_3rus = (new c3RUS(plNum)); plm = (DWORD)(c_3rus); plMain[plNum] = plm; } break;
		{ case 0x55: c3SSK * c_3ssk = (new c3SSK(plNum)); plm = (DWORD)(c_3ssk); plMain[plNum] = plm; } break;
		{ case 0x49: c3TOB * c_3tob = (new c3TOB(plNum)); plm = (DWORD)(c_3tob); plMain[plNum] = plm; } break;
		{ case 0x53: c3TYO * c_3tyo = (new c3TYO(plNum)); plm = (DWORD)(c_3tyo); plMain[plNum] = plm; } break;
		{ case 0x4B: c3UTK * c_3utk = (new c3UTK(plNum)); plm = (DWORD)(c_3utk); plMain[plNum] = plm; } break;
		{ case 0x4F: c3WHO * c_3who = (new c3WHO(plNum)); plm = (DWORD)(c_3who); plMain[plNum] = plm; } break;
		{ case 0x4A: c3YGR * c_3ygr = (new c3YGR(plNum)); plm = (DWORD)(c_3ygr); plMain[plNum] = plm; } break;
		#pragma endregion
		#pragma region 4
		{ case 0x96: c4JBR * c_4jbr = (new c4JBR(plNum)); plm = (DWORD)(c_4jbr); plMain[plNum] = plm; } break;
		{ case 0x5A: c4KKG * c_4kkg = (new c4KKG(plNum)); plm = (DWORD)(c_4kkg); plMain[plNum] = plm; } break;
		{ case 0x57: c4MKG * c_4mkg = (new c4MKG(plNum)); plm = (DWORD)(c_4mkg); plMain[plNum] = plm; } break;
		{ case 0xD4: c4MNR * c_4mnr = (new c4MNR(plNum)); plm = (DWORD)(c_4mnr); plMain[plNum] = plm; } break;
		{ case 0x58: c4MUU * c_4muu = (new c4MUU(plNum)); plm = (DWORD)(c_4muu); plMain[plNum] = plm; } break;
		{ case 0x6B: c4NRT * c_4nrt = (new c4NRT(plNum)); plm = (DWORD)(c_4nrt); plMain[plNum] = plm; } break;
		{ case 0x7A: c4RIN * c_4rin = (new c4RIN(plNum)); plm = (DWORD)(c_4rin); plMain[plNum] = plm; } break;
		{ case 0x59: c4RKG * c_4rkg = (new c4RKG(plNum)); plm = (DWORD)(c_4rkg); plMain[plNum] = plm; } break;
		{ case 0x60: c4SSI * c_4ssi = (new c4SSI(plNum)); plm = (DWORD)(c_4ssi); plMain[plNum] = plm; } break;
		#pragma endregion
		#pragma region 5
		{ case 0x97: c5JBR * c_5jbr = (new c5JBR(plNum)); plm = (DWORD)(c_5jbr); plMain[plNum] = plm; } break;
		{ case 0x73: c5JRB * c_5jrb = (new c5JRB(plNum)); plm = (DWORD)(c_5jrb); plMain[plNum] = plm; } break;
		{ case 0x74: c5KDM * c_5kdm = (new c5KDM(plNum)); plm = (DWORD)(c_5kdm); plMain[plNum] = plm; } break;
		{ case 0x7C: c5KGY * c_5kgy = (new c5KGY(plNum)); plm = (DWORD)(c_5kgy); plMain[plNum] = plm; } break;
		{ case 0xB8: c5KRS * c_5krs = (new c5KRS(plNum)); plm = (DWORD)(c_5krs); plMain[plNum] = plm; } break;
		{ case 0x72: c5MDR * c_5mdr = (new c5MDR(plNum)); plm = (DWORD)(c_5mdr); plMain[plNum] = plm; } break;
		{ case 0x81: c5NRT * c_5nrt = (new c5NRT(plNum)); plm = (DWORD)(c_5nrt); plMain[plNum] = plm; } break;
		{ case 0x71: c5OBT * c_5obt = (new c5OBT(plNum)); plm = (DWORD)(c_5obt); plMain[plNum] = plm; } break;
		{ case 0x75: c5SKN * c_5skn = (new c5SKN(plNum)); plm = (DWORD)(c_5skn); plMain[plNum] = plm; } break;
		{ case 0x82: c5SSK * c_5ssk = (new c5SSK(plNum)); plm = (DWORD)(c_5ssk); plMain[plNum] = plm; } break;
		{ case 0x76: c5TYY * c_5tyy = (new c5TYY(plNum)); plm = (DWORD)(c_5tyy); plMain[plNum] = plm; } break;
		#pragma endregion
		#pragma region 6 - 8
		{ case 0x83: c6HNB * c_6hnb = (new c6HNB(plNum)); plm = (DWORD)(c_6hnb); plMain[plNum] = plm; } break;
		{ case 0x7F: c6HNT * c_6hnt = (new c6HNT(plNum)); plm = (DWORD)(c_6hnt); plMain[plNum] = plm; } break;
		{ case 0x98: c6JBR * c_6jbr = (new c6JBR(plNum)); plm = (DWORD)(c_6jbr); plMain[plNum] = plm; } break;
		{ case 0x7B: c6NRT * c_6nrt = (new c6NRT(plNum)); plm = (DWORD)(c_6nrt); plMain[plNum] = plm; } break;
		{ case 0x80: c6SKR * c_6skr = (new c6SKR(plNum)); plm = (DWORD)(c_6skr); plMain[plNum] = plm; } break;
		{ case 0x7E: c6SSK * c_6ssk = (new c6SSK(plNum)); plm = (DWORD)(c_6ssk); plMain[plNum] = plm; } break;
		{ case 0xCD: c7BRN * c_7brn = (new c7BRN(plNum)); plm = (DWORD)(c_7brn); plMain[plNum] = plm; } break;
		{ case 0x9F: c7BRT * c_7brt = (new c7BRT(plNum)); plm = (DWORD)(c_7brt); plMain[plNum] = plm; } break;
		{ case 0xCE: c7BRX * c_7brx = (new c7BRX(plNum)); plm = (DWORD)(c_7brx); plMain[plNum] = plm; } break;
		{ case 0xCB: c7GAR * c_7gar = (new c7GAR(plNum)); plm = (DWORD)(c_7gar); plMain[plNum] = plm; } break;
		{ case 0xCC: c7KHM * c_7khm = (new c7KHM(plNum)); plm = (DWORD)(c_7khm); plMain[plNum] = plm; } break;
		{ case 0xD2: c7KIN * c_7kin = (new c7KIN(plNum)); plm = (DWORD)(c_7kin); plMain[plNum] = plm; } break;
		{ case 0xD1: c7MMS * c_7mms = (new c7MMS(plNum)); plm = (DWORD)(c_7mms); plMain[plNum] = plm; } break;
		{ case 0xD7: c7MMV * c_7mmv = (new c7MMV(plNum)); plm = (DWORD)(c_7mmv); plMain[plNum] = plm; } break;
		{ case 0xD8: c7MTK * c_7mtk = (new c7MTK(plNum)); plm = (DWORD)(c_7mtk); plMain[plNum] = plm; } break;
		{ case 0xC8: c7NRN * c_7nrn = (new c7NRN(plNum)); plm = (DWORD)(c_7nrn); plMain[plNum] = plm; } break;
		{ case 0xBE: c7NRT * c_7nrt = (new c7NRT(plNum)); plm = (DWORD)(c_7nrt); plMain[plNum] = plm; } break;
		{ case 0xD0: c7SKD * c_7skd = (new c7SKD(plNum)); plm = (DWORD)(c_7skd); plMain[plNum] = plm; } break;
		{ case 0xCA: c7SKR * c_7skr = (new c7SKR(plNum)); plm = (DWORD)(c_7skr); plMain[plNum] = plm; } break;
		{ case 0xA0: c7SLD * c_7sld = (new c7SLD(plNum)); plm = (DWORD)(c_7sld); plMain[plNum] = plm; } break;
		{ case 0xCF: c7SLN * c_7sln = (new c7SLN(plNum)); plm = (DWORD)(c_7sln); plMain[plNum] = plm; } break;
		{ case 0xBF: c7SSK * c_7ssk = (new c7SSK(plNum)); plm = (DWORD)(c_7ssk); plMain[plNum] = plm; } break;
		{ case 0xC9: c7SSX * c_7ssx = (new c7SSX(plNum)); plm = (DWORD)(c_7ssx); plMain[plNum] = plm; } break;
		{ case 0xD3: c7YRI * c_7yri = (new c7YRI(plNum)); plm = (DWORD)(c_7yri); plMain[plNum] = plm; } break;
		{ case 0xE6: c8AEM * c_8aem = (new c8AEM(plNum)); plm = (DWORD)(c_8aem); plMain[plNum] = plm; } break;
		{ case 0xDC: c8INO * c_8ino = (new c8INO(plNum)); plm = (DWORD)(c_8ino); plMain[plNum] = plm; } break;
		{ case 0xDF: c8KIB * c_8kib = (new c8KIB(plNum)); plm = (DWORD)(c_8kib); plMain[plNum] = plm; } break;
		{ case 0xDB: c8KIN * c_8kin = (new c8KIN(plNum)); plm = (DWORD)(c_8kin); plMain[plNum] = plm; } break;
		{ case 0xE3: c8KNK * c_8knk = (new c8KNK(plNum)); plm = (DWORD)(c_8knk); plMain[plNum] = plm; } break;
		{ case 0xDA: c8MMS * c_8mms = (new c8MMS(plNum)); plm = (DWORD)(c_8mms); plMain[plNum] = plm; } break;
		{ case 0xE1: c8ROC * c_8roc = (new c8ROC(plNum)); plm = (DWORD)(c_8roc); plMain[plNum] = plm; } break;
		{ case 0xE5: c8SAI * c_8sai = (new c8SAI(plNum)); plm = (DWORD)(c_8sai); plMain[plNum] = plm; } break;
		{ case 0xDD: c8SIK * c_8sik = (new c8SIK(plNum)); plm = (DWORD)(c_8sik); plMain[plNum] = plm; } break;
		{ case 0xE0: c8SIN * c_8sin = (new c8SIN(plNum)); plm = (DWORD)(c_8sin); plMain[plNum] = plm; } break;
		{ case 0xE2: c8TEN * c_8ten = (new c8TEN(plNum)); plm = (DWORD)(c_8ten); plMain[plNum] = plm; } break;
		{ case 0xE4: c8TMR * c_8tmr = (new c8TMR(plNum)); plm = (DWORD)(c_8tmr); plMain[plNum] = plm; } break;
		{ case 0xDE: c8TYO * c_8tyo = (new c8TYO(plNum)); plm = (DWORD)(c_8tyo); plMain[plNum] = plm; } break;
		#pragma endregion
		#pragma region Story
		
		{ case 0xD9: cABRT * c_abrt = (new cABRT(plNum)); plm = (DWORD)(c_abrt); plMain[plNum] = plm; } break;
		{ case 0xC2: cB1NR * c_b1nr = (new cB1NR(plNum)); plm = (DWORD)(c_b1nr); plMain[plNum] = plm; } break;
		{ case 0xC3: cB1SS * c_b1ss = (new cB1SS(plNum)); plm = (DWORD)(c_b1ss); plMain[plNum] = plm; } break;
		{ case 0x92: cB2NR * c_b2nr = (new cB2NR(plNum)); plm = (DWORD)(c_b2nr); plMain[plNum] = plm; } break;
		{ case 0xC5: cB3HS * c_b3hs = (new cB3HS(plNum)); plm = (DWORD)(c_b3hs); plMain[plNum] = plm; } break;
		{ case 0x89: cB4NR * c_b4nr = (new cB4NR(plNum)); plm = (DWORD)(c_b4nr); plMain[plNum] = plm; } break;
		{ case 0x8B: cB5OB * c_b5ob = (new cB5OB(plNum)); plm = (DWORD)(c_b5ob); plMain[plNum] = plm; } break;
		{ case 0xB9: cB6BT * c_b6bt = (new cB6BT(plNum)); plm = (DWORD)(c_b6bt); plMain[plNum] = plm; } break;
		{ case 0x90: cBAOD * c_baod = (new cBAOD(plNum)); plm = (DWORD)(c_baod); plMain[plNum] = plm; } break;
		{ case 0x8F: cBGKT * c_bgkt = (new cBGKT(plNum)); plm = (DWORD)(c_bgkt); plMain[plNum] = plm; } break;
		{ case 0xA1: cBGRG * c_bgrg = (new cBGRG(plNum)); plm = (DWORD)(c_bgrg); plMain[plNum] = plm; } break;
		{ case 0xC7: cBGRN * c_bgrn = (new cBGRN(plNum)); plm = (DWORD)(c_bgrn); plMain[plNum] = plm; } break;
		{ case 0xC6: cBGUY * c_bguy = (new cBGUY(plNum)); plm = (DWORD)(c_bguy); plMain[plNum] = plm; } break;
		{ case 0xAA: cBGYU * c_bgyu = (new cBGYU(plNum)); plm = (DWORD)(c_bgyu); plMain[plNum] = plm; } break;
		{ case 0x77: cBHSM * c_bhsm = (new cBHSM(plNum)); plm = (DWORD)(c_bhsm); plMain[plNum] = plm; } break;
		{ case 0xD5: cBISS * c_biss = (new cBISS(plNum)); plm = (DWORD)(c_biss); plMain[plNum] = plm; } break;
		{ case 0x85: cBJB1 * c_bjb1 = (new cBJB1(plNum)); plm = (DWORD)(c_bjb1); plMain[plNum] = plm; } break;
		{ case 0x86: cBJB2 * c_bjb2 = (new cBJB2(plNum)); plm = (DWORD)(c_bjb2); plMain[plNum] = plm; } break;
		{ case 0x87: cBJB3 * c_bjb3 = (new cBJB3(plNum)); plm = (DWORD)(c_bjb3); plMain[plNum] = plm; } break;
		{ case 0x88: cBJB4 * c_bjb4 = (new cBJB4(plNum)); plm = (DWORD)(c_bjb4); plMain[plNum] = plm; } break;
		{ case 0x9A: cBJYD * c_bjyd = (new cBJYD(plNum)); plm = (DWORD)(c_bjyd); plMain[plNum] = plm; } break;
		{ case 0xAB: cBJYG * c_bjyg = (new cBJYG(plNum)); plm = (DWORD)(c_bjyg); plMain[plNum] = plm; } break;
		{ case 0xB0: cBKGV * c_bkgv = (new cBKGV(plNum)); plm = (DWORD)(c_bkgv); plMain[plNum] = plm; } break;
		{ case 0xAE: cBKGY * c_bkgy = (new cBKGY(plNum)); plm = (DWORD)(c_bkgy); plMain[plNum] = plm; } break;
		{ case 0xB1: cBKKK * c_bkkk = (new cBKKK(plNum)); plm = (DWORD)(c_bkkk); plMain[plNum] = plm; } break;
		{ case 0xBA: cBKKS * c_bkks = (new cBKKS(plNum)); plm = (DWORD)(c_bkks); plMain[plNum] = plm; } break;
		{ case 0x9E: cBKKU * c_bkku = (new cBKKU(plNum)); plm = (DWORD)(c_bkku); plMain[plNum] = plm; } break;
		{ case 0x8A: cBKKX * c_bkkx = (new cBKKX(plNum)); plm = (DWORD)(c_bkkx); plMain[plNum] = plm; } break;
		{ case 0xA8: cBKMS * c_bkms = (new cBKMS(plNum)); plm = (DWORD)(c_bkms); plMain[plNum] = plm; } break;
		{ case 0x8C: cBKRL * c_bkrl = (new cBKRL(plNum)); plm = (DWORD)(c_bkrl); plMain[plNum] = plm; } break;
		{ case 0x9B: cBKRS * c_bkrs = (new cBKRS(plNum)); plm = (DWORD)(c_bkrs); plMain[plNum] = plm; } break;
		{ case 0xA9: cBKSR * c_bksr = (new cBKSR(plNum)); plm = (DWORD)(c_bksr); plMain[plNum] = plm; } break;
		{ case 0x91: cBKTY * c_bkty = (new cBKTY(plNum)); plm = (DWORD)(c_bkty); plMain[plNum] = plm; } break;
		{ case 0xA5: cBMDJ * c_bmdj = (new cBMDJ(plNum)); plm = (DWORD)(c_bmdj); plMain[plNum] = plm; } break;
		{ case 0xBC: cBMDK * c_bmdk = (new cBMDK(plNum)); plm = (DWORD)(c_bmdk); plMain[plNum] = plm; } break;
		{ case 0x78: cBMDR * c_bmdr = (new cBMDR(plNum)); plm = (DWORD)(c_bmdr); plMain[plNum] = plm; } break;
		{ case 0xBB: cBMDT * c_bmdt = (new cBMDT(plNum)); plm = (DWORD)(c_bmdt); plMain[plNum] = plm; } break;
		{ case 0xBD: cBMHR * c_bmhr = (new cBMHR(plNum)); plm = (DWORD)(c_bmhr); plMain[plNum] = plm; } break;
		{ case 0x79: cBMKJ * c_bmkj = (new cBMKJ(plNum)); plm = (DWORD)(c_bmkj); plMain[plNum] = plm; } break;
		{ case 0xD6: cBMNK * c_bmnk = (new cBMNK(plNum)); plm = (DWORD)(c_bmnk); plMain[plNum] = plm; } break;
		{ case 0xB4: cBNRC * c_bnrc = (new cBNRC(plNum)); plm = (DWORD)(c_bnrc); plMain[plNum] = plm; } break;
		{ case 0xC0: cBNRG * c_bnrg = (new cBNRG(plNum)); plm = (DWORD)(c_bnrg); plMain[plNum] = plm; } break;
		{ case 0xAC: cBNRT * c_bnrt = (new cBNRT(plNum)); plm = (DWORD)(c_bnrt); plMain[plNum] = plm; } break;
		{ case 0xB2: cBNRX * c_bnrx = (new cBNRX(plNum)); plm = (DWORD)(c_bnrx); plMain[plNum] = plm; } break;
		{ case 0xB7: cBOBK * c_bobk = (new cBOBK(plNum)); plm = (DWORD)(c_bobk); plMain[plNum] = plm; } break;
		{ case 0xA3: cBOBR * c_bobr = (new cBOBR(plNum)); plm = (DWORD)(c_bobr); plMain[plNum] = plm; } break;
		{ case 0xA4: cBOBS * c_bobs = (new cBOBS(plNum)); plm = (DWORD)(c_bobs); plMain[plNum] = plm; } break;
		{ case 0x8E: cBOBT * c_bobt = (new cBOBT(plNum)); plm = (DWORD)(c_bobt); plMain[plNum] = plm; } break;
		{ case 0xAF: cBOBZ * c_bobz = (new cBOBZ(plNum)); plm = (DWORD)(c_bobz); plMain[plNum] = plm; } break;
		{ case 0xA6: cBRMD * c_brmd = (new cBRMD(plNum)); plm = (DWORD)(c_brmd); plMain[plNum] = plm; } break;
		{ case 0xA7: cBRSK * c_brsk = (new cBRSK(plNum)); plm = (DWORD)(c_brsk); plMain[plNum] = plm; } break;
		{ case 0xB5: cBSSC * c_bssc = (new cBSSC(plNum)); plm = (DWORD)(c_bssc); plMain[plNum] = plm; } break;
		{ case 0xAD: cBSSK * c_bssk = (new cBSSK(plNum)); plm = (DWORD)(c_bssk); plMain[plNum] = plm; } break;
		{ case 0x8D: cBSSN * c_bssn = (new cBSSN(plNum)); plm = (DWORD)(c_bssn); plMain[plNum] = plm; } break;
		{ case 0xB3: cBSSX * c_bssx = (new cBSSX(plNum)); plm = (DWORD)(c_bssx); plMain[plNum] = plm; } break;
		{ case 0xC1: cBSSZ * c_bssz = (new cBSSZ(plNum)); plm = (DWORD)(c_bssz); plMain[plNum] = plm; } break;
		{ case 0x9D: cBTSK * c_btsk = (new cBTSK(plNum)); plm = (DWORD)(c_btsk); plMain[plNum] = plm; } break;
		{ case 0x99: cGFSA * c_gfsa = (new cGFSA(plNum)); plm = (DWORD)(c_gfsa); plMain[plNum] = plm; } break;
		{ case 0x9C: cGMHR * c_gmhr = (new cGMHR(plNum)); plm = (DWORD)(c_gmhr); plMain[plNum] = plm; } break;
		{ case 0xA2: cGZTU * c_gztu = (new cGZTU(plNum)); plm = (DWORD)(c_gztu); plMain[plNum] = plm; } break;
		{ case 0xB6: cJKKS * c_jkks = (new cJKKS(plNum)); plm = (DWORD)(c_jkks); plMain[plNum] = plm; } break;
		{ case 0x7D: cTYYP * c_tyyp = (new cTYYP(plNum)); plm = (DWORD)(c_tyyp); plMain[plNum] = plm; } break;
		
		#pragma endregion
*/
	}
	std::cout << "Created pl at " << hex << plm << "\n";
}
void ccPlayer::DeleteCharacter(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];

	delete &(*(c1CMN*)(plm));
	switch (c)
	{
		#pragma region 1
		/*
		case 0x66: delete & (*(c1AKM*)(plm)); break;
		case 0x40: delete & (*(c1FIR*)(plm)); break;
		case 0x34: delete & (*(c1GAR*)(plm)); break;
		case 0x3F: delete & (*(c1HAK*)(plm)); break;
		case 0x35: delete & (*(c1HKG*)(plm)); break;
		case 0x33: delete & (*(c1HNT*)(plm)); break;
		case 0x62: delete & (*(c1INO*)(plm)); break;
		case 0x93: delete & (*(c1JBR*)(plm)); break;
		case 0x65: delete & (*(c1KIB*)(plm)); break;
		case 0x36: delete & (*(c1KMM*)(plm)); break;
		case 0x69: delete & (*(c1KNK*)(plm)); break;
		case 0x6A: delete & (*(c1KRS*)(plm)); break;
		case 0x32: delete & (*(c1NEJ*)(plm)); break;
		case 0x2E: delete & (*(c1NRT*)(plm)); break;
		case 0x31: delete & (*(c1ROC*)(plm)); break;
		case 0x41: delete & (*(c1SEC*)(plm)); break;
		case 0x63: delete & (*(c1SIK*)(plm)); break;
		case 0x67: delete & (*(c1SIN*)(plm)); break;
		case 0x30: delete & (*(c1SKR*)(plm)); break;
		case 0x2F: delete & (*(c1SSK*)(plm)); break;
		case 0x61: delete & (*(c1TEN*)(plm)); break;
		case 0x68: delete & (*(c1TMR*)(plm)); break;
		case 0x64: delete & (*(c1TYO*)(plm)); break;
		case 0x3E: delete & (*(c1ZBZ*)(plm)); break;*/
		#pragma endregion
		#pragma region 2
			/*
		case 0x29: delete & (*(c2AKM*)(plm)); break;
		case 0x14: delete & (*(c2ASM*)(plm)); break;
		case 0x1B: delete & (*(c2CYB*)(plm)); break;
		case 0x1F: delete & (*(c2DDR*)(plm)); break;
		case 0x3A: delete & (*(c2DNZ*)(plm)); break;
		case 0x2D: delete & (*(c2FOU*)(plm)); break;
		case 0x0F: delete & (*(c2GAR*)(plm)); break;
		case 0x70: delete & (*(c2GAV*)(plm)); break;
		case 0x13: delete & (*(c2GUY*)(plm)); break;
		case 0x20: delete & (*(c2HDN*)(plm)); break;
		case 0x0E: delete & (*(c2HNT*)(plm)); break;
		case 0x09: delete & (*(c2INO*)(plm)); break;
		case 0x19: delete & (*(c2ITC*)(plm)); break;
		case 0x94: delete & (*(c2JBR*)(plm)); break;
		case 0x15: delete & (*(c2JRY*)(plm)); break;
		case 0x23: delete & (*(c2JUG*)(plm)); break;
		case 0x24: delete & (*(c2KAR*)(plm)); break;
		case 0x18: delete & (*(c2KBT*)(plm)); break;
		case 0x44: delete & (*(c2KBX*)(plm)); break;
		case 0x0C: delete & (*(c2KIB*)(plm)); break;
		case 0x2C: delete & (*(c2KKG*)(plm)); break;
		case 0x12: delete & (*(c2KKS*)(plm)); break;
		case 0x42: delete & (*(c2KKX*)(plm)); break;
		case 0x28: delete & (*(c2KLB*)(plm)); break;
		case 0x10: delete & (*(c2KNK*)(plm)); break;
		case 0x26: delete & (*(c2KNN*)(plm)); break;
		case 0x2A: delete & (*(c2KRS*)(plm)); break;
		case 0x1A: delete & (*(c2KSM*)(plm)); break;
		case 0x21: delete & (*(c2KZU*)(plm)); break;
		case 0x39: delete & (*(c2MDR*)(plm)); break;
		case 0x3D: delete & (*(c2MKG*)(plm)); break;
		case 0x07: delete & (*(c2NEJ*)(plm)); break;
		case 0x37: delete & (*(c2NRG*)(plm)); break;
		case 0x01: delete & (*(c2NRT*)(plm)); break;
		case 0x02: delete & (*(c2NRX*)(plm)); break;
		case 0x43: delete & (*(c2OBT*)(plm)); break;
		case 0x84: delete & (*(c2OBX*)(plm)); break;
		case 0x17: delete & (*(c2ORC*)(plm)); break;
		case 0x2B: delete & (*(c2PAR*)(plm)); break;
		case 0x27: delete & (*(c2PEA*)(plm)); break;
		case 0x3B: delete & (*(c2RKG*)(plm)); break;
		case 0x06: delete & (*(c2ROC*)(plm)); break;
		case 0x1C: delete & (*(c2SAI*)(plm)); break;
		case 0x1E: delete & (*(c2SCO*)(plm)); break;
		case 0x45: delete & (*(c2SCX*)(plm)); break;
		case 0x22: delete & (*(c2SGT*)(plm)); break;
		case 0x0A: delete & (*(c2SIK*)(plm)); break;
		case 0x0D: delete & (*(c2SIN*)(plm)); break;
		case 0x05: delete & (*(c2SKR*)(plm)); break;
		case 0x03: delete & (*(c2SSK*)(plm)); break;
		case 0x04: delete & (*(c2SSY*)(plm)); break;
		case 0x38: delete & (*(c2SSZ*)(plm)); break;
		case 0x08: delete & (*(c2TEN*)(plm)); break;
		case 0x3C: delete & (*(c2TKG*)(plm)); break;
		case 0x11: delete & (*(c2TMR*)(plm)); break;
		case 0x16: delete & (*(c2TND*)(plm)); break;
		case 0x25: delete & (*(c2TOB*)(plm)); break;
		case 0x0B: delete & (*(c2TYO*)(plm)); break;
		case 0x1D: delete & (*(c2YMT*)(plm)); break;*/
		#pragma endregion
		#pragma region 3
			/*
		case 0x47: delete & (*(c3DRI*)(plm)); break;
		case 0x56: delete & (*(c3GAR*)(plm)); break;
		case 0xC4: delete & (*(c3GUY*)(plm)); break;
		case 0x4D: delete & (*(c3HAN*)(plm)); break;
		case 0x51: delete & (*(c3HNZ*)(plm)); break;
		case 0x6E: delete & (*(c3HSM*)(plm)); break;
		case 0x5D: delete & (*(c3IRK*)(plm)); break;
		case 0x95: delete & (*(c3JBR*)(plm)); break;
		case 0x5E: delete & (*(c3KBT*)(plm)); break;
		case 0x5C: delete & (*(c3KHM*)(plm)); break;
		case 0x5B: delete & (*(c3KKS*)(plm)); break;
		case 0x50: delete & (*(c3KLB*)(plm)); break;
		case 0x6C: delete & (*(c3KSN*)(plm)); break;
		case 0x46: delete & (*(c3MDR*)(plm)); break;
		case 0x6F: delete & (*(c3MDR_2*)(plm)); break;
		case 0x4C: delete & (*(c3MFN*)(plm)); break;
		case 0x6D: delete & (*(c3MNT*)(plm)); break;
		case 0x52: delete & (*(c3NGT*)(plm)); break;
		case 0x54: delete & (*(c3NRT*)(plm)); break;
		case 0x4E: delete & (*(c3NYG*)(plm)); break;
		case 0x5F: delete & (*(c3OBT*)(plm)); break;
		case 0x48: delete & (*(c3RUS*)(plm)); break;
		case 0x55: delete & (*(c3SSK*)(plm)); break;
		case 0x49: delete & (*(c3TOB*)(plm)); break;
		case 0x53: delete & (*(c3TYO*)(plm)); break;
		case 0x4B: delete & (*(c3UTK*)(plm)); break;
		case 0x4F: delete & (*(c3WHO*)(plm)); break;
		case 0x4A: delete & (*(c3YGR*)(plm)); break;*/
		#pragma endregion
		#pragma region 4
			/*
		case 0x96: delete & (*(c4JBR*)(plm)); break;
		case 0x5A: delete & (*(c4KKG*)(plm)); break;
		case 0x57: delete & (*(c4MKG*)(plm)); break;
		case 0xD4: delete & (*(c4MNR*)(plm)); break;
		case 0x58: delete & (*(c4MUU*)(plm)); break;
		case 0x6B: delete & (*(c4NRT*)(plm)); break;
		case 0x7A: delete & (*(c4RIN*)(plm)); break;
		case 0x59: delete & (*(c4RKG*)(plm)); break;
		case 0x60: delete & (*(c4SSI*)(plm)); break;*/
		#pragma endregion
		#pragma region 5
			/*
		case 0x97: delete & (*(c5JBR*)(plm)); break;
		case 0x73: delete & (*(c5JRB*)(plm)); break;
		case 0x74: delete & (*(c5KDM*)(plm)); break;
		case 0x7C: delete & (*(c5KGY*)(plm)); break;
		case 0xB8: delete & (*(c5KRS*)(plm)); break;
		case 0x72: delete & (*(c5MDR*)(plm)); break;
		case 0x81: delete & (*(c5NRT*)(plm)); break;
		case 0x71: delete & (*(c5OBT*)(plm)); break;
		case 0x75: delete & (*(c5SKN*)(plm)); break;
		case 0x82: delete & (*(c5SSK*)(plm)); break;
		case 0x76: delete & (*(c5TYY*)(plm)); break;
		*/
		#pragma endregion
		#pragma region 6 - 8
			/*
		case 0x83: delete & (*(c6HNB*)(plm)); break;
		case 0x7F: delete & (*(c6HNT*)(plm)); break;
		case 0x98: delete & (*(c6JBR*)(plm)); break;
		case 0x7B: delete & (*(c6NRT*)(plm)); break;
		case 0x80: delete & (*(c6SKR*)(plm)); break;
		case 0x7E: delete & (*(c6SSK*)(plm)); break;
		case 0xCD: delete & (*(c7BRN*)(plm)); break;
		case 0x9F: delete & (*(c7BRT*)(plm)); break;
		case 0xCE: delete & (*(c7BRX*)(plm)); break;
		case 0xCB: delete & (*(c7GAR*)(plm)); break;
		case 0xCC: delete & (*(c7KHM*)(plm)); break;
		case 0xD2: delete & (*(c7KIN*)(plm)); break;
		case 0xD1: delete & (*(c7MMS*)(plm)); break;
		case 0xD7: delete & (*(c7MMV*)(plm)); break;
		case 0xD8: delete & (*(c7MTK*)(plm)); break;
		case 0xC8: delete & (*(c7NRN*)(plm)); break;
		case 0xBE: delete & (*(c7NRT*)(plm)); break;
		case 0xD0: delete & (*(c7SKD*)(plm)); break;
		case 0xCA: delete & (*(c7SKR*)(plm)); break;
		case 0xA0: delete & (*(c7SLD*)(plm)); break;
		case 0xCF: delete & (*(c7SLN*)(plm)); break;
		case 0xBF: delete & (*(c7SSK*)(plm)); break;
		case 0xC9: delete & (*(c7SSX*)(plm)); break;
		case 0xD3: delete & (*(c7YRI*)(plm)); break;
		case 0xE6: delete & (*(c8AEM*)(plm)); break;
		case 0xDC: delete & (*(c8INO*)(plm)); break;
		case 0xDF: delete & (*(c8KIB*)(plm)); break;
		case 0xDB: delete & (*(c8KIN*)(plm)); break;
		case 0xE3: delete & (*(c8KNK*)(plm)); break;
		case 0xDA: delete & (*(c8MMS*)(plm)); break;
		case 0xE1: delete & (*(c8ROC*)(plm)); break;
		case 0xE5: delete & (*(c8SAI*)(plm)); break;
		case 0xDD: delete & (*(c8SIK*)(plm)); break;
		case 0xE0: delete & (*(c8SIN*)(plm)); break;
		case 0xE2: delete & (*(c8TEN*)(plm)); break;
		case 0xE4: delete & (*(c8TMR*)(plm)); break;
		case 0xDE: delete & (*(c8TYO*)(plm)); break;
		*/
		#pragma endregion
		#pragma region Story
			/*
		case 0xD9: delete & (*(cABRT*)(plm)); break;
		case 0xC2: delete & (*(cB1NR*)(plm)); break;
		case 0xC3: delete & (*(cB1SS*)(plm)); break;
		case 0x92: delete & (*(cB2NR*)(plm)); break;
		case 0xC5: delete & (*(cB3HS*)(plm)); break;
		case 0x89: delete & (*(cB4NR*)(plm)); break;
		case 0x8B: delete & (*(cB5OB*)(plm)); break;
		case 0xB9: delete & (*(cB6BT*)(plm)); break;
		case 0x90: delete & (*(cBAOD*)(plm)); break;
		case 0x8F: delete & (*(cBGKT*)(plm)); break;
		case 0xA1: delete & (*(cBGRG*)(plm)); break;
		case 0xC7: delete & (*(cBGRN*)(plm)); break;
		case 0xC6: delete & (*(cBGUY*)(plm)); break;
		case 0xAA: delete & (*(cBGYU*)(plm)); break;
		case 0x77: delete & (*(cBHSM*)(plm)); break;
		case 0xD5: delete & (*(cBISS*)(plm)); break;
		case 0x85: delete & (*(cBJB1*)(plm)); break;
		case 0x86: delete & (*(cBJB2*)(plm)); break;
		case 0x87: delete & (*(cBJB3*)(plm)); break;
		case 0x88: delete & (*(cBJB4*)(plm)); break;
		case 0x9A: delete & (*(cBJYD*)(plm)); break;
		case 0xAB: delete & (*(cBJYG*)(plm)); break;
		case 0xB0: delete & (*(cBKGV*)(plm)); break;
		case 0xAE: delete & (*(cBKGY*)(plm)); break;
		case 0xB1: delete & (*(cBKKK*)(plm)); break;
		case 0xBA: delete & (*(cBKKS*)(plm)); break;
		case 0x9E: delete & (*(cBKKU*)(plm)); break;
		case 0x8A: delete & (*(cBKKX*)(plm)); break;
		case 0xA8: delete & (*(cBKMS*)(plm)); break;
		case 0x8C: delete & (*(cBKRL*)(plm)); break;
		case 0x9B: delete & (*(cBKRS*)(plm)); break;
		case 0xA9: delete & (*(cBKSR*)(plm)); break;
		case 0x91: delete & (*(cBKTY*)(plm)); break;
		case 0xA5: delete & (*(cBMDJ*)(plm)); break;
		case 0xBC: delete & (*(cBMDK*)(plm)); break;
		case 0x78: delete & (*(cBMDR*)(plm)); break;
		case 0xBB: delete & (*(cBMDT*)(plm)); break;
		case 0xBD: delete & (*(cBMHR*)(plm)); break;
		case 0x79: delete & (*(cBMKJ*)(plm)); break;
		case 0xD6: delete & (*(cBMNK*)(plm)); break;
		case 0xB4: delete & (*(cBNRC*)(plm)); break;
		case 0xC0: delete & (*(cBNRG*)(plm)); break;
		case 0xAC: delete & (*(cBNRT*)(plm)); break;
		case 0xB2: delete & (*(cBNRX*)(plm)); break;
		case 0xB7: delete & (*(cBOBK*)(plm)); break;
		case 0xA3: delete & (*(cBOBR*)(plm)); break;
		case 0xA4: delete & (*(cBOBS*)(plm)); break;
		case 0x8E: delete & (*(cBOBT*)(plm)); break;
		case 0xAF: delete & (*(cBOBZ*)(plm)); break;
		case 0xA6: delete & (*(cBRMD*)(plm)); break;
		case 0xA7: delete & (*(cBRSK*)(plm)); break;
		case 0xB5: delete & (*(cBSSC*)(plm)); break;
		case 0xAD: delete & (*(cBSSK*)(plm)); break;
		case 0x8D: delete & (*(cBSSN*)(plm)); break;
		case 0xB3: delete & (*(cBSSX*)(plm)); break;
		case 0xC1: delete & (*(cBSSZ*)(plm)); break;
		case 0x9D: delete & (*(cBTSK*)(plm)); break;
		case 0x99: delete & (*(cGFSA*)(plm)); break;
		case 0x9C: delete & (*(cGMHR*)(plm)); break;
		case 0xA2: delete & (*(cGZTU*)(plm)); break;
		case 0xB6: delete & (*(cJKKS*)(plm)); break;
		case 0x7D: delete & (*(cTYYP*)(plm)); break;
		*/
#pragma endregion
	}
	std::cout << "Deleted pl at " << hex << plm << "\n";
	plMain[plNum] = 0;
}
void ccPlayer::DoCharacterLoop(int c, int plNum)
{
	uintptr_t plm = plMain[plNum];

	(*(c1CMN*)(plm)).PreLoop(plNum);
	switch (c)
	{
		/*
		#pragma region 1
		case 0x66: (*(c1AKM*)(plm)).Loop(plNum); break;
		case 0x40: (*(c1FIR*)(plm)).Loop(plNum); break;
		case 0x34: (*(c1GAR*)(plm)).Loop(plNum); break;
		case 0x3F: (*(c1HAK*)(plm)).Loop(plNum); break;
		case 0x35: (*(c1HKG*)(plm)).Loop(plNum); break;
		case 0x33: (*(c1HNT*)(plm)).Loop(plNum); break;
		case 0x62: (*(c1INO*)(plm)).Loop(plNum); break;
		case 0x93: (*(c1JBR*)(plm)).Loop(plNum); break;
		case 0x65: (*(c1KIB*)(plm)).Loop(plNum); break;
		case 0x36: (*(c1KMM*)(plm)).Loop(plNum); break;
		case 0x69: (*(c1KNK*)(plm)).Loop(plNum); break;
		case 0x6A: (*(c1KRS*)(plm)).Loop(plNum); break;
		case 0x32: (*(c1NEJ*)(plm)).Loop(plNum); break;
		case 0x2E: (*(c1NRT*)(plm)).Loop(plNum); break;
		case 0x31: (*(c1ROC*)(plm)).Loop(plNum); break;
		case 0x41: (*(c1SEC*)(plm)).Loop(plNum); break;
		case 0x63: (*(c1SIK*)(plm)).Loop(plNum); break;
		case 0x67: (*(c1SIN*)(plm)).Loop(plNum); break;
		case 0x30: (*(c1SKR*)(plm)).Loop(plNum); break;
		case 0x2F: (*(c1SSK*)(plm)).Loop(plNum); break;
		case 0x61: (*(c1TEN*)(plm)).Loop(plNum); break;
		case 0x68: (*(c1TMR*)(plm)).Loop(plNum); break;
		case 0x64: (*(c1TYO*)(plm)).Loop(plNum); break;
		case 0x3E: (*(c1ZBZ*)(plm)).Loop(plNum); break;
		#pragma endregion
		#pragma region 2
		case 0x29: (*(c2AKM*)(plm)).Loop(plNum); break;
		case 0x14: (*(c2ASM*)(plm)).Loop(plNum); break;
		case 0x1B: (*(c2CYB*)(plm)).Loop(plNum); break;
		case 0x1F: (*(c2DDR*)(plm)).Loop(plNum); break;
		case 0x3A: (*(c2DNZ*)(plm)).Loop(plNum); break;
		case 0x2D: (*(c2FOU*)(plm)).Loop(plNum); break;
		case 0x0F: (*(c2GAR*)(plm)).Loop(plNum); break;
		case 0x70: (*(c2GAV*)(plm)).Loop(plNum); break;
		case 0x13: (*(c2GUY*)(plm)).Loop(plNum); break;
		case 0x20: (*(c2HDN*)(plm)).Loop(plNum); break;
		case 0x0E: (*(c2HNT*)(plm)).Loop(plNum); break;
		case 0x09: (*(c2INO*)(plm)).Loop(plNum); break;
		case 0x19: (*(c2ITC*)(plm)).Loop(plNum); break;
		case 0x94: (*(c2JBR*)(plm)).Loop(plNum); break;
		case 0x15: (*(c2JRY*)(plm)).Loop(plNum); break;
		case 0x23: (*(c2JUG*)(plm)).Loop(plNum); break;
		case 0x24: (*(c2KAR*)(plm)).Loop(plNum); break;
		case 0x18: (*(c2KBT*)(plm)).Loop(plNum); break;
		case 0x44: (*(c2KBX*)(plm)).Loop(plNum); break;
		case 0x0C: (*(c2KIB*)(plm)).Loop(plNum); break;
		case 0x2C: (*(c2KKG*)(plm)).Loop(plNum); break;
		case 0x12: (*(c2KKS*)(plm)).Loop(plNum); break;
		case 0x42: (*(c2KKX*)(plm)).Loop(plNum); break;
		case 0x28: (*(c2KLB*)(plm)).Loop(plNum); break;
		case 0x10: (*(c2KNK*)(plm)).Loop(plNum); break;
		case 0x26: (*(c2KNN*)(plm)).Loop(plNum); break;
		case 0x2A: (*(c2KRS*)(plm)).Loop(plNum); break;
		case 0x1A: (*(c2KSM*)(plm)).Loop(plNum); break;
		case 0x21: (*(c2KZU*)(plm)).Loop(plNum); break;
		case 0x39: (*(c2MDR*)(plm)).Loop(plNum); break;
		case 0x3D: (*(c2MKG*)(plm)).Loop(plNum); break;
		case 0x07: (*(c2NEJ*)(plm)).Loop(plNum); break;
		case 0x37: (*(c2NRG*)(plm)).Loop(plNum); break;
		case 0x01: (*(c2NRT*)(plm)).Loop(plNum); break;
		case 0x02: (*(c2NRX*)(plm)).Loop(plNum); break;
		case 0x43: (*(c2OBT*)(plm)).Loop(plNum); break;
		case 0x84: (*(c2OBX*)(plm)).Loop(plNum); break;
		case 0x17: (*(c2ORC*)(plm)).Loop(plNum); break;
		case 0x2B: (*(c2PAR*)(plm)).Loop(plNum); break;
		case 0x27: (*(c2PEA*)(plm)).Loop(plNum); break;
		case 0x3B: (*(c2RKG*)(plm)).Loop(plNum); break;
		case 0x06: (*(c2ROC*)(plm)).Loop(plNum); break;
		case 0x1C: (*(c2SAI*)(plm)).Loop(plNum); break;
		case 0x1E: (*(c2SCO*)(plm)).Loop(plNum); break;
		case 0x45: (*(c2SCX*)(plm)).Loop(plNum); break;
		case 0x22: (*(c2SGT*)(plm)).Loop(plNum); break;
		case 0x0A: (*(c2SIK*)(plm)).Loop(plNum); break;
		case 0x0D: (*(c2SIN*)(plm)).Loop(plNum); break;
		case 0x05: (*(c2SKR*)(plm)).Loop(plNum); break;
		case 0x03: (*(c2SSK*)(plm)).Loop(plNum); break;
		case 0x04: (*(c2SSY*)(plm)).Loop(plNum); break;
		case 0x38: (*(c2SSZ*)(plm)).Loop(plNum); break;
		case 0x08: (*(c2TEN*)(plm)).Loop(plNum); break;
		case 0x3C: (*(c2TKG*)(plm)).Loop(plNum); break;
		case 0x11: (*(c2TMR*)(plm)).Loop(plNum); break;
		case 0x16: (*(c2TND*)(plm)).Loop(plNum); break;
		case 0x25: (*(c2TOB*)(plm)).Loop(plNum); break;
		case 0x0B: (*(c2TYO*)(plm)).Loop(plNum); break;
		case 0x1D: (*(c2YMT*)(plm)).Loop(plNum); break;
		#pragma endregion
		#pragma region 3
		case 0x47: (*(c3DRI*)(plm)).Loop(plNum); break;
		case 0x56: (*(c3GAR*)(plm)).Loop(plNum); break;
		case 0xC4: (*(c3GUY*)(plm)).Loop(plNum); break;
		case 0x4D: (*(c3HAN*)(plm)).Loop(plNum); break;
		case 0x51: (*(c3HNZ*)(plm)).Loop(plNum); break;
		case 0x6E: (*(c3HSM*)(plm)).Loop(plNum); break;
		case 0x5D: (*(c3IRK*)(plm)).Loop(plNum); break;
		case 0x95: (*(c3JBR*)(plm)).Loop(plNum); break;
		case 0x5E: (*(c3KBT*)(plm)).Loop(plNum); break;
		case 0x5C: (*(c3KHM*)(plm)).Loop(plNum); break;
		case 0x5B: (*(c3KKS*)(plm)).Loop(plNum); break;
		case 0x50: (*(c3KLB*)(plm)).Loop(plNum); break;
		case 0x6C: (*(c3KSN*)(plm)).Loop(plNum); break;
		case 0x46: (*(c3MDR*)(plm)).Loop(plNum); break;
		case 0x6F: (*(c3MDR_2*)(plm)).Loop(plNum); break;
		case 0x4C: (*(c3MFN*)(plm)).Loop(plNum); break;
		case 0x6D: (*(c3MNT*)(plm)).Loop(plNum); break;
		case 0x52: (*(c3NGT*)(plm)).Loop(plNum); break;
		case 0x54: (*(c3NRT*)(plm)).Loop(plNum); break;
		case 0x4E: (*(c3NYG*)(plm)).Loop(plNum); break;
		case 0x5F: (*(c3OBT*)(plm)).Loop(plNum); break;
		case 0x48: (*(c3RUS*)(plm)).Loop(plNum); break;
		case 0x55: (*(c3SSK*)(plm)).Loop(plNum); break;
		case 0x49: (*(c3TOB*)(plm)).Loop(plNum); break;
		case 0x53: (*(c3TYO*)(plm)).Loop(plNum); break;
		case 0x4B: (*(c3UTK*)(plm)).Loop(plNum); break;
		case 0x4F: (*(c3WHO*)(plm)).Loop(plNum); break;
		case 0x4A: (*(c3YGR*)(plm)).Loop(plNum); break;
		#pragma endregion
		#pragma region 4
		case 0x96: (*(c4JBR*)(plm)).Loop(plNum); break;
		case 0x5A: (*(c4KKG*)(plm)).Loop(plNum); break;
		case 0x57: (*(c4MKG*)(plm)).Loop(plNum); break;
		case 0xD4: (*(c4MNR*)(plm)).Loop(plNum); break;
		case 0x58: (*(c4MUU*)(plm)).Loop(plNum); break;
		case 0x6B: (*(c4NRT*)(plm)).Loop(plNum); break;
		case 0x7A: (*(c4RIN*)(plm)).Loop(plNum); break;
		case 0x59: (*(c4RKG*)(plm)).Loop(plNum); break;
		case 0x60: (*(c4SSI*)(plm)).Loop(plNum); break;
		#pragma endregion
		#pragma region 5
		case 0x97: (*(c5JBR*)(plm)).Loop(plNum); break;
		case 0x73: (*(c5JRB*)(plm)).Loop(plNum); break;
		case 0x74: (*(c5KDM*)(plm)).Loop(plNum); break;
		case 0x7C: (*(c5KGY*)(plm)).Loop(plNum); break;
		case 0xB8: (*(c5KRS*)(plm)).Loop(plNum); break;
		case 0x72: (*(c5MDR*)(plm)).Loop(plNum); break;
		case 0x81: (*(c5NRT*)(plm)).Loop(plNum); break;
		case 0x71: (*(c5OBT*)(plm)).Loop(plNum); break;
		case 0x75: (*(c5SKN*)(plm)).Loop(plNum); break;
		case 0x82: (*(c5SSK*)(plm)).Loop(plNum); break;
		case 0x76: (*(c5TYY*)(plm)).Loop(plNum); break;
		#pragma endregion
		#pragma region 6 - 8
		case 0x83: (*(c6HNB*)(plm)).Loop(plNum); break;
		case 0x7F: (*(c6HNT*)(plm)).Loop(plNum); break;
		case 0x98: (*(c6JBR*)(plm)).Loop(plNum); break;
		case 0x7B: (*(c6NRT*)(plm)).Loop(plNum); break;
		case 0x80: (*(c6SKR*)(plm)).Loop(plNum); break;
		case 0x7E: (*(c6SSK*)(plm)).Loop(plNum); break;
		case 0xCD: (*(c7BRN*)(plm)).Loop(plNum); break;
		case 0x9F: (*(c7BRT*)(plm)).Loop(plNum); break;
		case 0xCE: (*(c7BRX*)(plm)).Loop(plNum); break;
		case 0xCB: (*(c7GAR*)(plm)).Loop(plNum); break;
		case 0xCC: (*(c7KHM*)(plm)).Loop(plNum); break;
		case 0xD2: (*(c7KIN*)(plm)).Loop(plNum); break;
		case 0xD1: (*(c7MMS*)(plm)).Loop(plNum); break;
		case 0xD7: (*(c7MMV*)(plm)).Loop(plNum); break;
		case 0xD8: (*(c7MTK*)(plm)).Loop(plNum); break;
		case 0xC8: (*(c7NRN*)(plm)).Loop(plNum); break;
		case 0xBE: (*(c7NRT*)(plm)).Loop(plNum); break;
		case 0xD0: (*(c7SKD*)(plm)).Loop(plNum); break;
		case 0xCA: (*(c7SKR*)(plm)).Loop(plNum); break;
		case 0xA0: (*(c7SLD*)(plm)).Loop(plNum); break;
		case 0xCF: (*(c7SLN*)(plm)).Loop(plNum); break;
		case 0xBF: (*(c7SSK*)(plm)).Loop(plNum); break;
		case 0xC9: (*(c7SSX*)(plm)).Loop(plNum); break;
		case 0xD3: (*(c7YRI*)(plm)).Loop(plNum); break;
		case 0xE6: (*(c8AEM*)(plm)).Loop(plNum); break;
		case 0xDC: (*(c8INO*)(plm)).Loop(plNum); break;
		case 0xDF: (*(c8KIB*)(plm)).Loop(plNum); break;
		case 0xDB: (*(c8KIN*)(plm)).Loop(plNum); break;
		case 0xE3: (*(c8KNK*)(plm)).Loop(plNum); break;
		case 0xDA: (*(c8MMS*)(plm)).Loop(plNum); break;
		case 0xE1: (*(c8ROC*)(plm)).Loop(plNum); break;
		case 0xE5: (*(c8SAI*)(plm)).Loop(plNum); break;
		case 0xDD: (*(c8SIK*)(plm)).Loop(plNum); break;
		case 0xE0: (*(c8SIN*)(plm)).Loop(plNum); break;
		case 0xE2: (*(c8TEN*)(plm)).Loop(plNum); break;
		case 0xE4: (*(c8TMR*)(plm)).Loop(plNum); break;
		case 0xDE: (*(c8TYO*)(plm)).Loop(plNum); break;
		#pragma endregion
		#pragma region Story
		
		case 0xD9: (*(cABRT*)(plm)).Loop(plNum); break;
		case 0xC2: (*(cB1NR*)(plm)).Loop(plNum); break;
		case 0xC3: (*(cB1SS*)(plm)).Loop(plNum); break;
		case 0x92: (*(cB2NR*)(plm)).Loop(plNum); break;
		case 0xC5: (*(cB3HS*)(plm)).Loop(plNum); break;
		case 0x89: (*(cB4NR*)(plm)).Loop(plNum); break;
		case 0x8B: (*(cB5OB*)(plm)).Loop(plNum); break;
		case 0xB9: (*(cB6BT*)(plm)).Loop(plNum); break;
		case 0x90: (*(cBAOD*)(plm)).Loop(plNum); break;
		case 0x8F: (*(cBGKT*)(plm)).Loop(plNum); break;
		case 0xA1: (*(cBGRG*)(plm)).Loop(plNum); break;
		case 0xC7: (*(cBGRN*)(plm)).Loop(plNum); break;
		case 0xC6: (*(cBGUY*)(plm)).Loop(plNum); break;
		case 0xAA: (*(cBGYU*)(plm)).Loop(plNum); break;
		case 0x77: (*(cBHSM*)(plm)).Loop(plNum); break;
		case 0xD5: (*(cBISS*)(plm)).Loop(plNum); break;
		case 0x85: (*(cBJB1*)(plm)).Loop(plNum); break;
		case 0x86: (*(cBJB2*)(plm)).Loop(plNum); break;
		case 0x87: (*(cBJB3*)(plm)).Loop(plNum); break;
		case 0x88: (*(cBJB4*)(plm)).Loop(plNum); break;
		case 0x9A: (*(cBJYD*)(plm)).Loop(plNum); break;
		case 0xAB: (*(cBJYG*)(plm)).Loop(plNum); break;
		case 0xB0: (*(cBKGV*)(plm)).Loop(plNum); break;
		case 0xAE: (*(cBKGY*)(plm)).Loop(plNum); break;
		case 0xB1: (*(cBKKK*)(plm)).Loop(plNum); break;
		case 0xBA: (*(cBKKS*)(plm)).Loop(plNum); break;
		case 0x9E: (*(cBKKU*)(plm)).Loop(plNum); break;
		case 0x8A: (*(cBKKX*)(plm)).Loop(plNum); break;
		case 0xA8: (*(cBKMS*)(plm)).Loop(plNum); break;
		case 0x8C: (*(cBKRL*)(plm)).Loop(plNum); break;
		case 0x9B: (*(cBKRS*)(plm)).Loop(plNum); break;
		case 0xA9: (*(cBKSR*)(plm)).Loop(plNum); break;
		case 0x91: (*(cBKTY*)(plm)).Loop(plNum); break;
		case 0xA5: (*(cBMDJ*)(plm)).Loop(plNum); break;
		case 0xBC: (*(cBMDK*)(plm)).Loop(plNum); break;
		case 0x78: (*(cBMDR*)(plm)).Loop(plNum); break;
		case 0xBB: (*(cBMDT*)(plm)).Loop(plNum); break;
		case 0xBD: (*(cBMHR*)(plm)).Loop(plNum); break;
		case 0x79: (*(cBMKJ*)(plm)).Loop(plNum); break;
		case 0xD6: (*(cBMNK*)(plm)).Loop(plNum); break;
		case 0xB4: (*(cBNRC*)(plm)).Loop(plNum); break;
		case 0xC0: (*(cBNRG*)(plm)).Loop(plNum); break;
		case 0xAC: (*(cBNRT*)(plm)).Loop(plNum); break;
		case 0xB2: (*(cBNRX*)(plm)).Loop(plNum); break;
		case 0xB7: (*(cBOBK*)(plm)).Loop(plNum); break;
		case 0xA3: (*(cBOBR*)(plm)).Loop(plNum); break;
		case 0xA4: (*(cBOBS*)(plm)).Loop(plNum); break;
		case 0x8E: (*(cBOBT*)(plm)).Loop(plNum); break;
		case 0xAF: (*(cBOBZ*)(plm)).Loop(plNum); break;
		case 0xA6: (*(cBRMD*)(plm)).Loop(plNum); break;
		case 0xA7: (*(cBRSK*)(plm)).Loop(plNum); break;
		case 0xB5: (*(cBSSC*)(plm)).Loop(plNum); break;
		case 0xAD: (*(cBSSK*)(plm)).Loop(plNum); break;
		case 0x8D: (*(cBSSN*)(plm)).Loop(plNum); break;
		case 0xB3: (*(cBSSX*)(plm)).Loop(plNum); break;
		case 0xC1: (*(cBSSZ*)(plm)).Loop(plNum); break;
		case 0x9D: (*(cBTSK*)(plm)).Loop(plNum); break;
		case 0x99: (*(cGFSA*)(plm)).Loop(plNum); break;
		case 0x9C: (*(cGMHR*)(plm)).Loop(plNum); break;
		case 0xA2: (*(cGZTU*)(plm)).Loop(plNum); break;
		case 0xB6: (*(cJKKS*)(plm)).Loop(plNum); break;
		case 0x7D: (*(cTYYP*)(plm)).Loop(plNum); break;
		
		#pragma endregion
		*/
	}
	(*(c1CMN*)(plm)).PostLoop(plNum);
}

#pragma endregion
