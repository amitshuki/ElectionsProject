#pragma once
#include <iostream>
#include "VotersForParty.h"
#include "DynamicArray.h"
class VotersForPartyList
{
private:
	DynamicArray<VotersForParty> vfpArr1;

public:
	VotersForPartyList() = default;
	VotersForPartyList(istream& in){ load(in); }

	const int& getLogSize()const { return vfpArr1.getLogSize(); }

	bool addParty(const int& partySN);
	bool voteForParty(const int& partySN);

	const int& getAmountOfVotersByPartySN(const int& partySN);


	VotersForParty& getVFPByPartySN(const int& partySN);
	const VotersForParty& operator[](const int idx)const { return vfpArr1[idx]; }
	VotersForPartyList& operator=(const VotersForPartyList& other);

	bool save(ostream& out) const;
	bool load(istream& in);
};

