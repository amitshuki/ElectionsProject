#pragma once
#include "Party.h"
#include "myString.h"
class PartyList
{
	Party** partyArr;
	int logSize, capacity;
	RoundMode round_mode;
	void resizeArr();
public:
	PartyList(const RoundMode& rm) :partyArr(nullptr), logSize(0), capacity(0), round_mode(rm) {}
	~PartyList();

	Party* const addPartyToList(const myString& partName, const Citizen* candidate);
	bool addDistrictToParties(const int& dstSN, const int& dstRank);

	bool checkExistingPartyBySN(const int& sn)const;
	Party* const getPartyBySN(const int& sn)const;

	const int& getLogSize()const { return logSize; }
	
	Party* getPartyByIndex(const int& idx)const;

	Party* operator[](const int& idx)const;
	friend ostream& operator<<(ostream& out, const PartyList& partyList);

	bool save(ostream& out);
	bool load(istream& in);
};

