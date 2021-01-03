#pragma once
#include "State.h"
class DistrictBasedState :
    public State
{
public:
	DistrictBasedState() :State(RoundMode::REGULAR) {}
	DistrictBasedState(istream& in) :State(in) {}

	bool addDistrict(const myString& districtName, const int& rank, const DistrictType& dt);
	bool addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN);
	bool addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN);

	void showDistrict()const;
	bool checkExistingDistrictBySN(const int& sn)const { return distList.checkExistingDistrictBySN(sn); }
	virtual bool save(ostream& out) const;
	virtual bool load(istream& in);
};

