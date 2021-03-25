#pragma once
#include <iostream>
#include "VotersForParty.h"
#include "DynamicArray.h"
#include "my_exceptions.h"
class VotersForPartyList
{
private:
	DynamicArray<VotersForParty> vfpArr;

public:
	VotersForPartyList() = default;
	VotersForPartyList(istream& in){ load(in); }

	const int& getLogSize()const { return vfpArr.getLogSize(); }

	void addParty(const int& partySN);
	void voteForParty(const int& partySN);

	const int& getAmountOfVotersByPartySN(const int& partySN);


	VotersForParty& getVFPByPartySN(const int& partySN);
	const VotersForParty& operator[](const int idx)const { return vfpArr[idx]; }
	VotersForPartyList& operator=(const VotersForPartyList& other);

	void save(ostream& out) const;
	void load(istream& in);
};

