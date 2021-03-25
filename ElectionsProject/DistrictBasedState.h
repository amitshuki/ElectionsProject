#pragma once
#include "State.h"
class DistrictBasedState :
    public State
{
public:
	DistrictBasedState() :State(RoundMode::REGULAR) {}
	DistrictBasedState(istream& in) :State(in) {}

	void addDistrict(const string& districtName, const int& rank, const DistrictType& dt);
	void addCitizen(const string& name, const int& id, const int& birthYear, const int& districtSN);
	void addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN);

	void showDistrict()const;
	bool checkExistingDistrictBySN(const int& sn)const { return distList.checkExistingDistrictBySN(sn); }
	virtual void save(ostream& out) const{ State::save(out); }
	virtual void load(istream& in){ State::load(in); }
};

