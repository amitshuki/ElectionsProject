#include "VotersForParty.h"
#include <iostream>
using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

void VotersForParty::setPartySN(const int& partySN){
	if (this->partySN == -1)
		this->partySN = partySN;
	else
		throw exception("Party already set.");
}

int VotersForParty::calcNumOfElectors(const int& totalVotes, const int& distRank)const {
	if (totalVotes == 0)
		throw range_error("Devide by zero");
	return (numOfVoters / totalVotes) * distRank;
}

void VotersForParty::save(ostream& out) const {
	out.write(rcastcc(&numOfVoters), sizeof(numOfVoters));
	out.write(rcastcc(&partySN), sizeof(partySN));
	if (!out.good())
		throw outfile_error("VotersForParty");
}
void VotersForParty::load(istream& in) {
	in.read(rcastc(&numOfVoters), sizeof(numOfVoters));
	in.read(rcastc(&partySN), sizeof(partySN));
	if(!in.good())
		throw infile_error("VotersForParty");
}