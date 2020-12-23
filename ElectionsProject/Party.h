#pragma once
#include "DistrictRepsList.h"
#include "Citizen.h"
#include "myString.h"

class Party
{
private:
	myString name;
	int partySN;
	const Citizen* candidate;
	DistrictRepsList drList;
	RoundMode round_mode;
public:
	Party(const myString& newName, const int& sn, const Citizen* candidate, const RoundMode& rm):
		name(newName), partySN(sn), candidate(candidate), drList(rm), round_mode(rm) {}

	const int& getSN()const { return partySN; }
	const myString& getName()const { return name; }
	const Citizen* getCandidate()const { return candidate; }


	bool addDistrict(const int& dstSN, const int& dstRank);
	bool addCitizenAsRep(Citizen* const rep, const int& dstSN = 0);


	void printResults(const int& districtSN, const int& electorsAmount);
	friend ostream& operator<<(ostream& out, const Party& prty);
};

