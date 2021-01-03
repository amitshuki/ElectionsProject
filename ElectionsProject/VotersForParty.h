#pragma once
#include <iostream>
class VotersForParty//This is connection table #2
{
private:
	int numOfVoters;
	int partySN;
public:
	VotersForParty() :numOfVoters(0), partySN(-1) {}

	bool setPartySN(const int& partySN) { 
		if (this->partySN == -1)
			return this->partySN = partySN;
		
		std::cout << "Party Serial No. already set." << std::endl;
		return false;
	}
	bool addVote() { return ++numOfVoters; }

	const int& getPartySN()const { return partySN; }
	const int& getNumOfVoters()const { return numOfVoters; }

	int calcNumOfElectors(const int& totalVotes, const int& distRank)const { 
		if (numOfVoters <= 0)
			return 0;
		return (numOfVoters / totalVotes) * distRank;
	}
};

