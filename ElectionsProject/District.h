#pragma once
#include "VotersForParty.h"
class VotersForParty;
class District
{
private:
	int serialNumber, totalCivils, totalVoters, electorsAmount;
	string name;
	VotersForParty* votersForParty;
};

