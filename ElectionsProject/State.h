#pragma once
#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
#include "myString.h"
#include <ctime>
using namespace myStr;
using namespace std;

struct Date {
	int day, month, year;
	Date():day(-1), month(-1), year(-1) {}
	Date(const int& d, const int& m, const int& y) :day(d), month(m), year(y) {}
	bool operator==(const Date& other)const;
	friend ostream& operator<<(ostream& out, const Date& dt);
};

class State
{
protected:
	CitizenList votersBook;
	DistrictList distList;
	PartyList partyList;
	bool hasAny1votedyet;
	Date date;
public:
	State(const RoundMode& rm) :
		votersBook(rm,
			CitizenList::deleteOption::DELETE_ALL,
			CitizenList::saveloadOption::SAVE_AND_LOAD),
		partyList(rm), hasAny1votedyet(false) {}
	State(istream& in);
	virtual ~State() {}
	

	bool addParty(const myString& partyName, const int& candidateId);

	void showVotersBook()const;
	void showParties()const;

	bool checkExistingCitizenbyID(const int& id) const { return votersBook.checkExistingCitizenInListByID(id); }
	bool checkExistingPartyBySN(const int& sn)const { return partyList.checkExistingPartyBySN(sn); }

	bool vote(const int& id, const int& partySN);

	void showElectionsResults();

	bool setDate(const int& d, const int& m, const int& y);

	virtual bool save(ostream& out) const;
	virtual bool load(istream& in);

	bool connectCitizensToDistricts();
};

