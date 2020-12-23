#pragma once
#include "Round.h"
class RegularRound :
    public Round
{
public:
	RegularRound() :Round(RoundMode::REGULAR){}
	bool addDistrict(const myString& districtName, const int& rank, const DistrictType& dt);
	bool addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN);
	bool addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN);

	void showDistrict()const;
	bool checkExistingDistrictBySN(const int& sn)const { return distList.checkExistingDistrictBySN(sn); }

};

