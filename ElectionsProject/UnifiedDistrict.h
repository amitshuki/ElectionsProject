#pragma once
#include "District.h"
class UnifiedDistrict :
    public District
{
private:
	virtual void printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties);
public:
	UnifiedDistrict(const myString& newName, const int& newRank, const int& sn):
		District(newName, newRank, sn) {}

	virtual ElectorsForPartyArr& getVotingresults(PartyList& partyList);

};

