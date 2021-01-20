#pragma once
#include "District.h"
class UnifiedDistrict :
    public District
{
private:
	virtual void printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties)const;
public:
	UnifiedDistrict(const myString& newName, const int& newRank, const int& sn):
		District(newName, newRank, sn) {}
	UnifiedDistrict(istream& in) :District(in) {}
	virtual ElectorsForPartyArr& getVotingresults(PartyList& partyList);
	virtual bool save(ostream& out) const;
	virtual bool load(istream& in){ return District::load(in); }
};

