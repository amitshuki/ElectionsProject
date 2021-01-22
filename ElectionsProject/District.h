#pragma once
#include "PartyList.h"
#include "VotersForPartyList.h"
#include "ElectorsForPartyArr.h"
#include "myString.h"
#include <cmath>
using namespace myStr;
class District
{
protected:
	int districtSN, totalCivils, totalVoters, rank; 
	myString name;
	VotersForPartyList voters4PartyList;// Contains a list of all the parties (serial nums) and how many voted for them in the district.
	District();
	District(const myString& newName, const int& newRank, const int& sn);
	District(istream& in) { load(in); }
public:
	const int& getSN()const { return districtSN; }
	const int& getRank()const { return rank; }
	const int& getTotalCivils()const { return totalCivils; }
	const int& getTotalVoters()const { return totalVoters; }

	void addCitizenToDistrict() { ++totalCivils; }

	void addVoteToParty(const int& partySN);
	void addPartyToDistrict(const int& partySN) { voters4PartyList.addParty(partySN); }

	virtual ElectorsForPartyArr& getVotingresults(PartyList& partyList) = 0;

	friend ostream& operator<<(ostream& out, const District& dst);
	
	friend class DistrictList;

	virtual void save(ostream& out) const;
	virtual void load(istream& in);

protected:
	int calcElectors(const int& numOfVoters);
	virtual void printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties) const = 0;
	int getWinningPartyIdx(ElectorsForPartyArr& electors_for_parties);
	

};

