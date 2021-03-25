#pragma once
#include <iostream>
#include "my_exceptions.h"
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
	void setPartySN(const int& partySN);

	void addVote() { ++numOfVoters; }
	const int& getPartySN()const { return partySN; }
	const int& getNumOfVoters()const { return numOfVoters; }

	int calcNumOfElectors(const int& totalVotes, const int& distRank)const;

	void save(ostream& out) const;
	void load(istream& in);
};

