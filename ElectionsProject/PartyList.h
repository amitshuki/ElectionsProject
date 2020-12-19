#pragma once
#include "Party.h"
#include "myString.h"
class PartyList
{
	Party** partyArr;
	int logSize, capacity;

	void resizeArr();
public:
	PartyList() :partyArr(nullptr), logSize(0), capacity(0) {}
	~PartyList();

	Party* const addPartyToList(const myString& partName, const Citizen* candidate);
	bool addDistrictToParties(const int& dstSN, const int& dstRank);

	bool checkExistingPartyBySN(const int& sn)const;
	Party* const getPartyBySN(const int& sn)const;

	const int& getLogSize()const { return logSize; }
	
	Party* getPartyByIndex(const int& idx)const;

	Party* operator[](const int& idx)const;
	friend ostream& operator<<(ostream& out, const PartyList& partyList);
};

