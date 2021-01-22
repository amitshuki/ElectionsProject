#pragma once
#include "Party.h"
#include "myString.h"
#include "DynamicArray.h"
class PartyList
{
	DynamicArray<Party*> partyArr;
	RoundMode round_mode;
public:
	PartyList(const RoundMode& rm) :round_mode(rm) {}
	PartyList(istream& in) { load(in); }
	~PartyList();

	Party* addPartyToList(const myString& partName, const Citizen* candidate);
	void addDistrictToParties(const int& dstSN, const int& dstRank);

	bool checkExistingPartyBySN(const int& sn)const;
	Party* getPartyBySN(const int& sn)const;
	Party* getPartyByIndex(const int& idx)const;

	const int& getLogSize()const { return partyArr.getLogSize(); }

	PartyList& operator=(const PartyList& other);
	Party* operator[](const int& idx)const { return partyArr[idx]; }
	friend ostream& operator<<(ostream& out, const PartyList& partyList);

	void save(ostream& out) const;
	void load(istream& in);

	void connectPartyreps2Citizens(CitizenList& citList);
};

