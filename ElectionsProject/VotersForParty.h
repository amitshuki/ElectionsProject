#pragma once
#include <iostream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
class VotersForParty//This is connection table #2
{
private:
	int numOfVoters;
	int partySN;
public:
	VotersForParty() :numOfVoters(0), partySN(-1) {}
	VotersForParty(const int& partySN) :numOfVoters(0), partySN(partySN) {}

	VotersForParty(istream& in) { load(in); }
	bool setPartySN(const int& partySN);

	bool addVote() { return ++numOfVoters; }
	const int& getPartySN()const { return partySN; }
	const int& getNumOfVoters()const { return numOfVoters; }

	int calcNumOfElectors(const int& totalVotes, const int& distRank)const;

	bool save(ostream& out) const;
	bool load(istream& in);
};

