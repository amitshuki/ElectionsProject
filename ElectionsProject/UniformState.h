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
	void addCitizen(const string& name, const int& id, const int& birthYear);
	void addCitizenAsPartyRep(const int& repID, const int& partySN);
	virtual void save(ostream& out) const override;
	virtual void load(istream& in) override{ State::load(in); }
};

