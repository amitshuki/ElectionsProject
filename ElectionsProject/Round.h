#pragma once
#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
#include "myString.h"
using namespace myStr;
using namespace std;

class Round
{
protected:
	CitizenList votersBook;
	DistrictList distList;
	PartyList partyList;
	bool hasAny1votedyet;
public:
	Round(const RoundMode& rm) :
		votersBook(rm, CitizenList::deleteOption::DELETE_ALL, CitizenList::saveloadOption::SAVE_AND_LOAD), partyList(rm), hasAny1votedyet(false) {}
	~Round() {}


	bool addParty(const myString& partyName, const int& candidateId);

	void showVotersBook()const;
	void showParties()const;

	bool checkExistingCitizenbyID(const int& id) const { return votersBook.checkExistingCitizenInListByID(id); }
	bool checkExistingPartyBySN(const int& sn)const { return partyList.checkExistingPartyBySN(sn); }

	bool vote(const int& id, const int& partySN);

	void showElectionsResults();
	virtual bool save(ostream& out);
	virtual bool load(istream& in);
};

