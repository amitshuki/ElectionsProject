#pragma once
#include "CitizenList.h"

class DistrictReps//This is connection table #1
{
private:
	int dstSN, rank;
	CitizenList repsList;
public:
	DistrictReps();
	DistrictReps(const int& dstSn, const int& rank);

	bool setDistrict(const int& dstSn, const int& eRank);
	bool addRep(Citizen* const rep);

	const int& getDistrictSN()const { return dstSN; }
	const int& getDistrictRank()const { return rank; }
	const CitizenList& getRepsList() const { return repsList; }

	void printFirstXReps(const int& amount) { repsList.printFirstXReps(amount); }

	DistrictReps& operator=(const DistrictReps& other);
	friend ostream& operator<<(ostream& out, const DistrictReps& dstReps);
};

