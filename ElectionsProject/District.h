#pragma once
#include "VotersForParty.h"
class VotersForParty;
class District
{
private:
	int serialNumber, totalCivils, totalVoters, rank; /* total voters - filled only when  round is initiated (init -1)
													  rank - given randomly */
	string name;
	VotersForParty* votersForParty;
};

