#pragma once
#include "Party.h"
#include "myString.h"
#include "DynamicArray.h"
class PartyList
{
	DynamicArray<Party*> partyArr1;
	Party** partyArr;
	int logSize, capacity;
	RoundMode round_mode;
public:
	PartyList(const RoundMode& rm) :round_mode(rm) {}
	PartyList(istream& in) { load(in); }
	~PartyList();


	Party* addPartyToList(const myString& partName, const Citizen* candidate);
	bool addDistrictToParties(const int& dstSN, const int& dstRank);

	bool checkExistingPartyBySN(const int& sn)const;
	Party* getPartyBySN(const int& sn)const;
	const int& getLogSize()const { return partyArr1.getLogSize(); }
	Party* getPartyByIndex(const int& idx)const;

	Party* operator[](const int& idx)const { return partyArr1[idx]; }
	friend ostream& operator<<(ostream& out, const PartyList& partyList);

	bool save(ostream& out) const;
	bool load(istream& in);

	bool connectPartyreps2Citizens(CitizenList& citList);
};

