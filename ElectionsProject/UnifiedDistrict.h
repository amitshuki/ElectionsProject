#pragma once
#include "District.h"
class UnifiedDistrict :
    public District
{
private:
	virtual void printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties)const;
public:
	UnifiedDistrict(const string& newName, const int& newRank, const int& sn):
		District(newName, newRank, sn) {}
	UnifiedDistrict(istream& in) :District(in) {}
	virtual ElectorsForPartyArr& getVotingresults(PartyList& partyList);

	virtual void save(ostream& out) const{ District::save(out); }
	virtual void load(istream& in){ District::load(in); }
};

