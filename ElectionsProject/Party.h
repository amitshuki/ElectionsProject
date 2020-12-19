#pragma once
#include "DistrictRepsList.h"
#include "Citizen.h"
#include "myString.h"

class Party
{
private:
	myString name;
	int SN;
	const Citizen* candidate;
	DistrictRepsList drList;
public:
	Party() :name(""), SN(-1), candidate(nullptr) {}
	Party(const myString& newName, const int& sn, const Citizen* candidate);
	const int& getSN()const { return SN; }
	const myString& getName()const { return name; }
	const Citizen* getCandidate()const { return candidate; }

	void printResults(const int& districtSN, const int& electorsAmount);

	CitizenList& getSubRepsListInDistrict(const int& dstSN, const int& amount);
	bool addDistrict(const int& dstSN, const int& dstRank) { return drList.addDistrict(dstSN, dstRank); }
	bool addCitizenAsRep(Citizen* const rep, const int& dstSN) { return drList.addCitizenAsRep(rep, dstSN); }

	friend ostream& operator<<(ostream& out, const Party& prty);
};

