#pragma once
#include "DistrictList.h"
#include "District.h"
#include "Citizen.h"
#include "CitizenList.h"
#include "Party.h"
#include "PartyList.h"
#include "myString.h"
using namespace myStr;
using namespace std;


class State
{
private:
	CitizenList votersBook;
	DistrictList distList;
	PartyList partyList;
public:
	State() {
		srand(time(0));
	}
	~State() {
		votersBook.setDeleteOpt(CitizenList::deleteOption::DELETE_ALL);
	}


	bool addDistrict(const myString& districtName, const int& rank);
	bool addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN);
	bool addParty(const myString& partyName, const int& candidateId);
	bool addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN);

	void showVotersBook()const;
	void showDistrict()const;
	void showParties()const;

	bool checkExistingCitizenbyID(const int& id) const { return votersBook.checkExistingCitizenInListByID(id); }
	bool checkExistingDistrictBySN(const int& sn)const { return distList.checkExistingDistrictBySN(sn); }
	bool checkExistingPartyBySN(const int& sn)const { return partyList.checkExistingPartyBySN(sn); }

	bool vote(const int& id, const int& partySN);

	void showElectionsResults();

};

