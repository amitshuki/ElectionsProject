#pragma once

class VotersForParty//This is connection table #2
{
private:
	int numOfVoters;
	int partySN;
public:
	VotersForParty() :numOfVoters(0), partySN(-1) {}

	bool setPartySN(const int& partySN);

	bool addVote() { return ++numOfVoters; }
	const int& getPartySN()const { return partySN; }
	const int& getNumOfVoters()const { return numOfVoters; }

	int calcNumOfElectors(const int& totalVotes, const int& distRank)const;
};

