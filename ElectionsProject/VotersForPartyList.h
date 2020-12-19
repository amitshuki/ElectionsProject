#pragma once
#include <iostream>
#include "VotersForParty.h"
class VotersForPartyList
{
private:
	VotersForParty* vfpArr;
	int logSize, capacity;

	void resize();
public:
	VotersForPartyList() :logSize(0), capacity(0), vfpArr(nullptr) {}
	~VotersForPartyList() { delete[] vfpArr; }

	const int& getLogSize()const { return logSize; }

	bool addParty(const int& partySN);
	bool voteForParty(const int& partySN);

	const int& getAmountOfVotersByPartySN(const int& partySN);


	VotersForParty& getVFPByPartySN(const int& partySN);
	const VotersForParty& operator[](const int idx);
	VotersForPartyList& operator=(const VotersForPartyList& other);
};

