#pragma once
#include "ElectorsForPartyArr.h"
#include "District.h"
class DividedDistrict :
    public District
{
private:
	virtual void printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties)const;
	void swap(ElectorsForParty& a, ElectorsForParty& b);
	int partition(ElectorsForPartyArr& electors_for_party, const int& low, const int& high);
	void quickSort(ElectorsForPartyArr& electors_for_party, const int& low, const int& high);

public:
	DividedDistrict(const myString& newName, const int& newRank, const int& sn) :
		District(newName, newRank, sn) {}
	DividedDistrict(istream& in) :District(in) {}
	virtual ElectorsForPartyArr& getVotingresults(PartyList& partyList);

	virtual bool save(ostream& out) const;
	virtual bool load(istream& in){ return District::load(in); }
};

