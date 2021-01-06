#pragma once
#include "State.h"
class UniformState :
    public State
{
private:
	int districtSN;
public:
	UniformState(const int& rank);
	UniformState(istream& in) :State(in) { in.read(rcastc(&districtSN), sizeof(districtSN)); }
	bool addCitizen(const myString& name, const int& id, const int& birthYear);
	bool addCitizenAsPartyRep(const int& repID, const int& partySN);
	virtual bool save(ostream& out) const override;
	virtual bool load(istream& in) override;
};

