#include "VotersForParty.h"
#include <iostream>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

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

bool VotersForParty::save(ostream& out) const {
	out.write(rcastcc(&numOfVoters), sizeof(numOfVoters));
	out.write(rcastcc(&partySN), sizeof(partySN));
	return out.good();
}
bool VotersForParty::load(istream& in) {
	in.read(rcastc(&numOfVoters), sizeof(numOfVoters));
	in.read(rcastc(&partySN), sizeof(partySN));
	return in.good();
}