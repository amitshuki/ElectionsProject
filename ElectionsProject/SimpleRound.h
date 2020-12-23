#pragma once
#include "Round.h"
class SimpleRound :
    public Round
{
private:
	int districtSN;
public:
	SimpleRound(const int& rank);

	bool addCitizen(const myString& name, const int& id, const int& birthYear);
	bool addCitizenAsPartyRep(const int& repID, const int& partySN);
};

