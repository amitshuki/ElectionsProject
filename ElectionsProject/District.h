#pragma once
#include "PartyList.h"
#include "VotersForPartyList.h"
#include "myString.h"
#include <cmath>
using namespace myStr;

struct ElectorsForParty {
	int electorsAmount = 0;
	int votesForParty = 0;
	float precentage = 0.0;
	Party* party = nullptr;
};

class District
{
private:
	int SN, totalCivils, totalVoters, rank; /* total voters - filled only when  round is initiated (init -1)
													  rank - given randomly */
	myString name;

	VotersForPartyList voters4PartyList;// Contains a list of all the parties (serial nums) and how many voted for them in the district.
public:
	District();
	District(const myString& newName, const int& newRank, const int& sn);

	const int& getSN()const { return SN; }
	const int& getRank()const { return rank; }
	const int& getTotalCivils()const { return totalCivils; }
	const int& getTotalVoters()const { return totalVoters; }

	bool addCitizenToDistrict() { return ++totalCivils; }

	bool addVoteToParty(const int& partySN);
	bool addPartyToDistrict(const int& partySN) { return voters4PartyList.addParty(partySN); }

	const int& getVotingresults(PartyList& partyList);


private:
	int getWinningPartyIdx(ElectorsForParty*& electors_for_parties, const int& num_of_parties);
	void printResults(const int& winningPartyIdx, ElectorsForParty*& electors_for_parties, const int& num_of_parties);
	int calcElectors(const int& numOfVoters);
public:
	friend ostream& operator<<(ostream& out, const District& dst);
};

