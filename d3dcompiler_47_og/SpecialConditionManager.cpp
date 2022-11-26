#include "SpecialConditionManager.h"
#include "FileParser.h"
#include "Common.h"

#include <WinSock2.h>
#include <Windows.h>
#include "HookFunctions.h"
#include <iostream>

std::vector<SpecialConditionManager::GameCondition*> SpecialConditionManager::condList;
std::vector<SpecialConditionManager::Condition*> SpecialConditionManager::charCondList;
__int64 SpecialConditionManager::condAlloc = 0;

void SpecialConditionManager::ReadSpecialConditionParam(std::string _file)
{
	std::vector<BYTE> fileBytes = FileParser::ReadAllBytes(_file);

	int slotCount = fileBytes.size() / 0x20;

	for (int x = 0; x < slotCount; x++)
	{
		std::string slotType = "";
		int condCharacter = 0;
		int actual = (0x20 * x);

		while (actual < (0x20 * x) + 0x17)
		{
			if (fileBytes[actual] != 0x0)
			{
				slotType = slotType + (char)fileBytes[actual];
				actual++;
			}
			else
			{
				actual = (0x20 * x) + 0x17;
			}
		}

		condCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);

		uintptr_t condFunct = 0x0;
		int actualConditionIndex = -1;
		bool found = false;

		for (int x = 0; x < condList.size(); x++)
		{
			if (slotType == condList[x]->COND_TYPE)
			{
				found = true;
				x = 0x5C;
				condFunct = condList[x]->address;
			}
		}

		int basecond = 0x7C4B7C;

		if (slotType == "COND_1CMN") condFunct = 0x7C4B7C;
		else if (slotType == "COND_2SIK") condFunct = 0x7C4BE4;
		else if (slotType == "COND_2HDN") condFunct = 0x7C4C4C;
		else if (slotType == "COND_2KKS") condFunct = 0x7C4CB4;
		else if (slotType == "COND_2CYB") condFunct = 0x7C4D1C;
		else if (slotType == "COND_2SCO") condFunct = 0x7C4D84;
		else if (slotType == "COND_2DDR") condFunct = 0x7C4DEC;
		else if (slotType == "COND_3HNZ") condFunct = 0x7C4E54;
		else if (slotType == "COND_3TOB") condFunct = 0x7C4EBC;
		else if (slotType == "COND_3TYO") condFunct = 0x7C3E14;
		else if (slotType == "COND_3MDR_2") condFunct = 0x7C4F24;
		else if (slotType == "COND_3KBT") condFunct = 0x7C4F8C;
		else if (slotType == "COND_2KNK") condFunct = 0x7C4FF4;
		else if (slotType == "COND_2JRY") condFunct = 0x7C505C;
		else if (slotType == "COND_3GAR") condFunct = 0x7C50C4; // same as below
		else if (slotType == "COND_2GAV") condFunct = 0x7C50C4; // same as above
		else if (slotType == "COND_2ORC") condFunct = 0x7C512C;
		else if (slotType == "COND_5KGY") condFunct = 0x7C5194;
		else if (slotType == "COND_2FOU") condFunct = 0x7C51FC;
		else if (slotType == "COND_2DNZ") condFunct = 0x7C5264;
		else if (slotType == "COND_3GUY") condFunct = 0x7C52CC;
		else if (slotType == "COND_2KBT") condFunct = 0x7C317C;
		else if (slotType == "COND_2MDR") condFunct = 0x7C31E4;
		else if (slotType == "COND_JKKS") condFunct = 0x7C324C;
		else if (slotType == "COND_2KIB") condFunct = 0x7C32B4;
		else if (slotType == "COND_2KNN") condFunct = 0x7C331C;
		else if (slotType == "COND_2SGT") condFunct = 0x7C3384;
		else if (slotType == "COND_4MKG") condFunct = 0x7C33EC;
		else if (slotType == "COND_2NRT") condFunct = 0x7C3454; // same as below
		else if (slotType == "COND_2NRG") condFunct = 0x7C3454; // same as below
		else if (slotType == "COND_3NRT") condFunct = 0x7C3454; // same as above
		else if (slotType == "COND_2NRX") condFunct = 0x7C34BC;
		else if (slotType == "COND_3SSK") condFunct = 0x7C3524;
		else if (slotType == "COND_5TYY") condFunct = 0x7C358C;
		else if (slotType == "COND_5MDR") condFunct = 0x7C35F4;
		else if (slotType == "COND_5KDM") condFunct = 0x7C365C;
		else if (slotType == "COND_BMDR") condFunct = 0x7C36C4;
		else if (slotType == "COND_1KNK") condFunct = 0x7C372C;
		else if (slotType == "COND_2YMT") condFunct = 0x7C3794;
		else if (slotType == "COND_3MDR") condFunct = 0x7C37FC;
		else if (slotType == "COND_5SKN") condFunct = 0x7C3864;
		else if (slotType == "COND_5JRB") condFunct = 0x7C38CC;
		else if (slotType == "COND_7BRX") condFunct = 0x7C3934;
		else if (slotType == "COND_7SKD") condFunct = 0x7C399C;
		else if (slotType == "COND_7YRI") condFunct = 0x7C3A04;
		else if (slotType == "COND_7NRN") condFunct = 0x7C3A6C;
		else if (slotType == "COND_7SSX") condFunct = 0x7C3AD4;
		else if (slotType == "COND_7MMS") condFunct = 0x7C3B3C;
		else if (slotType == "COND_7KIN") condFunct = 0x7C3BA4;
		else if (slotType == "COND_7GAR") condFunct = 0x7C50C4;
		else if (slotType == "COND_7MTK") condFunct = 0x7C3C0C;
		else if (slotType == "COND_8MMS") condFunct = 0x7C3C74;
		else if (slotType == "COND_8KIN") condFunct = 0x7C3CDC;
		else if (slotType == "COND_8KNK") condFunct = 0x7C3D44;
		else if (slotType == "COND_8SIK") condFunct = 0x7C3DAC;
		else if (slotType == "COND_8TYO") condFunct = 0x7C3E14;
		else if (slotType == "COND_BKRL") condFunct = 0x7C3E7C;
		else if (slotType == "COND_BSSN") condFunct = 0x7C3EE4;
		else if (slotType == "COND_BOBT") condFunct = 0x7C3F4C;
		else if (slotType == "COND_BKRS") condFunct = 0x7C3FB4;
		else if (slotType == "COND_B3HS") condFunct = 0x7C401C;
		else if (slotType == "COND_BGKT") condFunct = 0x7C4084;
		else if (slotType == "COND_BAOD") condFunct = 0x7C40EC;
		else if (slotType == "COND_BKTY") condFunct = 0x7C4154;
		else if (slotType == "COND_1JBR") condFunct = 0x7C41BC;
		else if (slotType == "COND_2JBR") condFunct = 0x7C4224;
		else if (slotType == "COND_3JBR") condFunct = 0x7C428C;
		else if (slotType == "COND_4JBR") condFunct = 0x7C42F4;
		else if (slotType == "COND_5JBR") condFunct = 0x7C435C;
		else if (slotType == "COND_6JBR") condFunct = 0x7C43C4;
		else if (slotType == "COND_BJYD") condFunct = 0x7C442C;
		else if (slotType == "COND_GFSA") condFunct = 0x7C4494;
		else if (slotType == "COND_BKKX") condFunct = 0x7C44FC;
		else if (slotType == "COND_B5OB") condFunct = 0x7C4564;
		else if (slotType == "COND_B4NR") condFunct = 0x7C45CC;
		else if (slotType == "COND_B2NR") condFunct = 0x7C4634;
		else if (slotType == "COND_BJB1") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_BJB2") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_BJB3") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_BJB4") condFunct = 0x7C469C; // same as below
		else if (slotType == "COND_GFSA") condFunct = 0x7C469C; // same as above
		else if (slotType == "COND_BGRG") condFunct = 0x7C4704;
		else if (slotType == "COND_GZTU") condFunct = 0x7C476C;
		else if (slotType == "COND_BRSK") condFunct = 0x7C47D4;
		else if (slotType == "COND_BKMS") condFunct = 0x7C483C;
		else if (slotType == "COND_BKSR") condFunct = 0x7C48A4;
		else if (slotType == "COND_BOBK") condFunct = 0x7C490C;
		else if (slotType == "COND_BNRX") condFunct = 0x7C4974;
		else if (slotType == "COND_BSSX") condFunct = 0x7C49DC;
		else if (slotType == "COND_BISS") condFunct = 0x7C4A44;
		else if (slotType == "COND_BMNK") condFunct = 0x7C4AAC;
		else if (slotType == "COND_7MMV") condFunct = 0x7C4B14;

		SpecialConditionManager::Condition * cond = new SpecialConditionManager::Condition();
		cond->characode = condCharacter;
		cond->address = moduleBase + condFunct;
		SpecialConditionManager::charCondList.push_back(cond);

		//std::cout << "SpecialCondManager :: Found condition for " << std::hex << std::uppercase << condCharacter << " : " << slotType << std::endl;
	}
}

void SpecialConditionManager::SpecialCondFunctions()
{
	BYTE function[] = { 0x48, 0x8D, 0x05, 0x48 + 14, 0x00, 0x00, 0x00,

						0x3B, 0x38,
						0x0F, 0x84, 0x1D, 0x00, 0x00, 0x00,
						0x48, 0x8D, 0x0D, 0xFF, 0xFF, 0xFF, 0x00, // add 14
						0x48, 0x83, 0xC0, 0x10,
						0xFF, 0xC3,
						0x48, 0x3B, 0xC1,
						0x7C, 0xE6,
						0xFF, 0x15, 0x20 + 14, 0x00, 0x00, 0x00,
						0xE9, 0x10, 0x00, 0x00, 0x00,

						0x48, 0x63, 0xC3,
						0x48, 0x8D, 0x0D, 0x11 + 14, 0x00, 0x00, 0x00,
						0x48, 0x03, 0xC0,
						0xFF, 0x14, 0xC1,

						0x48, 0x8B, 0x5C, 0x24, 0x30,
						0x48, 0x83, 0xC4, 0x20,
						0x5F,
						0xC3,

						0xCC, 0xCC, 0x90, 0x90, 0x90, 0x90, // jmp qword ptr [$+6]
						0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	int funcsize = 0x55;

	int conditionCount = charCondList.size();
	int totalSize = (funcsize)+(conditionCount * 0x10) + (0x8);

	uintptr_t main_malloc = (uintptr_t)VirtualAlloc(0, totalSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	uintptr_t specialCondFunct = main_malloc + funcsize;
	uintptr_t specialCondCodes = main_malloc + funcsize + 0x8;
	uintptr_t end = main_malloc + totalSize;

	void * writeAddress = &function[0];

	int lea_rip_address = 0x31 + (conditionCount * 0x10) + 0x8 + 14;
	memcpy((void*)(&function[0] + 0x12), &lea_rip_address, 0x4); // fix the lea with rip + address (points to the end of the condition list)

	// create jump back
	uintptr_t specialConditionJumpTo = 0x7C636D;
	uintptr_t jback = moduleBase + specialConditionJumpTo;
	memcpy((void*)(&function[0] + 0x4E), &jback, 8);

	// Copy function to memory, and make executable
	memcpy((void*)main_malloc, (void*)&function, funcsize);
	DWORD dwOld = 0;
	VirtualProtect((void*)main_malloc, funcsize, PAGE_EXECUTE_READWRITE, &dwOld);

	//cout << "Executable: " << std::hex << main_malloc << " to " << std::hex << (main_malloc + funcsize);

	for (int x = 0; x < conditionCount; x++)
	{
		memcpy((void*)(specialCondFunct + (x * 0x10)), (void*)(&(charCondList[x]->address)), 8);
		memcpy((void*)(specialCondCodes + (x * 0x10)), (void*)(&(charCondList[x]->characode)), 4);
	}

	// Hook original function
	uintptr_t specialConditionAddress = 0x7C55AD;
	if (condAlloc == 0) HookFunctions::Hook((void*)(moduleBase + specialConditionAddress), (void*)main_malloc, 15);
	else
	{
		// Fix address for reload
		uintptr_t placeJump = moduleBase + specialConditionAddress;

		DWORD dwOld = 0;
		VirtualProtect((void*)placeJump, 14, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy((void*)(placeJump + 6), (void*)&main_malloc, 8);
		VirtualProtect((void*)placeJump, 14, dwOld, &dwOld);
	}

	condAlloc = main_malloc;
}
