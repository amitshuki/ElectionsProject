#pragma once
#include "ElectorsForPartyArr.h"
#include "District.h"
class DividedDistrict :
    public District
{
private:
	virtual void printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties)const;
public:
	DividedDistrict(const myString& newName, const int& newRank, const int& sn) :
		District(newName, newRank, sn) {}
	DividedDistrict(istream& in) :District(in) {}
	virtual ElectorsForPartyArr& getVotingresults(PartyList& partyList);

	virtual void save(ostream& out) const { District::save(out); }
	virtual void load(istream& in){ District::load(in); }
};

