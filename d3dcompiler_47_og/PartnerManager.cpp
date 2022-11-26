#include "PartnerManager.h"

#include "FileParser.h"
#include "PatternScan.h"
#include <iostream>

#include "Common.h"
#include <WinSock2.h>
#include <Windows.h>
#include "HookFunctions.h"

std::vector<PartnerFunction*> PartnerManager::partnerFunctionList;
std::vector<PartnerFramework*> PartnerManager::frameworkPartnerList;

void PartnerManager::InitialScan()
{
	__int64 partnerBase = PatternScan::Scan("327474693030743020722068616E64003268686130307430206C2068616E6400327474693030743020722066696E676572300000000000003268686130307430206C2066696E67657230000000000000", 0, false);
	if (partnerBase > 0) partnerBase = PatternScan::Scan("2B00000000000000", partnerBase, true) - 8;

	if (partnerBase < 1)
	{
		std::cout << "PartnerManager :: Partner search failed" << std::endl;
		return;
	}
	else
	{
		std::cout << "PartnerManager :: Found Instance" << std::endl;
	}

	int partnerCount = 0;
	__int64 actualPartner = partnerBase;

	int * checkIntA = (int*)(actualPartner + 0xA);
	short * checkIntB = (short*)(actualPartner + 0xE);
	while (*checkIntA == 0 && *checkIntB == 0)
	{
		partnerCount++;

		PartnerFunction * partner = new PartnerFunction();
		partner->address = actualPartner;

		int characode = *(int*)(actualPartner + 8);
		switch (characode)
		{
		default:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_UNK";
			std::cout << "PartnerSystem :: Unknown partner type found" << std::endl;
			break;
		}
		case 0x2B:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_2PAR";
			break;
		}
		case 0x2C:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_2KKG";
			break;
		}
		case 0x29:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_2AKM";
			break;
		}
		case 0x2A:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_2KRS";
			break;
		}
		case 0x66:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_1AKM";
			break;
		}
		case 0x6A:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_1KRS";
			break;
		}
		case 0x45:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_2SCX";
			break;
		}
		case 0xE6:
		{
			partner->PARTNER_TYPE = "PARTNER_TYPE_8AEM";
			break;
		}
		}

		PartnerManager::partnerFunctionList.push_back(partner);

		actualPartner += 0x10;
		checkIntA = (int*)(actualPartner + 0xA);
		checkIntB = (short*)(actualPartner + 0xE);
	}

	std::cout << "PartnerSystem :: Found " << partnerCount << " partners." << std::endl;
}

void PartnerManager::ReadPartnerSlotParam(std::string _file)
{
	std::vector<BYTE> fileBytes = FileParser::ReadAllBytes(_file);

	int slotCount = fileBytes.size() / 0x20;

	for (int x = 0; x < slotCount; x++)
	{
		std::string slotType = "";
		int slotCharacter = 0;
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

		slotCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);

		uintptr_t slotFunct = 0x0;
		int slotIndex = -1;
		int gamePartnerCount = PartnerManager::partnerFunctionList.size();

		for (int a = 0; a < gamePartnerCount; a++)
		{
			std::string thisSlotType = PartnerManager::partnerFunctionList[a]->PARTNER_TYPE;

			if (thisSlotType == slotType)
			{
				slotIndex = a;
				a = gamePartnerCount;
			}
		}

		if (slotIndex == -1)
		{
			std::cout << "PartnerManager :: Error loading character " << std::hex << slotCharacter << " - Attempted using an unknown type of partner (" << slotType << ")" << std::endl;
		}
		else
		{
			PartnerFramework * newPartner = new PartnerFramework();
			newPartner->address = PartnerManager::partnerFunctionList[slotIndex]->address;
			newPartner->characode = slotCharacter;

			PartnerManager::frameworkPartnerList.push_back(newPartner);
		}
	}
}

__int64 PartnerManager::CreatePartner(__int64 player, int characode)
{
	std::cout << "Attempted to create partner with characode " << std::hex << std::uppercase << characode << std::endl;

	int partnerCount = PartnerManager::frameworkPartnerList.size();
	__int64 address = 0;

	for (int x = 0; x < partnerCount; x++)
	{
		if (PartnerManager::frameworkPartnerList[x]->characode == characode)
		{
			address = PartnerManager::frameworkPartnerList[x]->address;
			x = partnerCount;
		}
	}

	std::cout << "Address: " << std::hex << std::uppercase << address << std::endl;
	address = *(__int64*)address;

	typedef __int64(__fastcall * funct)();
	funct fc = (funct)(address);
	__int64 result = 0;
	if(fc) result = fc();

	std::cout << "Result: " << std::hex << std::uppercase << result << std::endl;

	return result;
}