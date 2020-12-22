#include "VotersForParty.h"
#include <iostream>

bool VotersForParty::setPartySN(const int& partySN) {
	if (this->partySN == -1)
		return this->partySN = partySN;

	return false;
}

int VotersForParty::calcNumOfElectors(const int& totalVotes, const int& distRank)const {
	if (numOfVoters <= 0)
		return 0;
	return (numOfVoters / totalVotes) * distRank;
}