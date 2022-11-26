#pragma once
#include <string>
#include <vector>

struct PartnerFunction
{
	std::string PARTNER_TYPE = "PARTNER_TYPE";
	__int64 address = 0;
};

struct PartnerFramework
{
	__int64 address = 0;
	int characode = 0;
};

class PartnerManager
{
public:
	static std::vector<PartnerFunction*> partnerFunctionList;
	static std::vector<PartnerFramework*> frameworkPartnerList;

	static void InitialScan();
	static void ReadPartnerSlotParam(std::string file);
	static __int64 CreatePartner(__int64 player, int characode);
};