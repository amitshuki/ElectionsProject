#pragma once
#include "CitizenList.h"

class DistrictReps//This is connection table #1
{
private:
	int dstSN, rank;
	CitizenList repsList;
	RoundMode round_mode;
public:
	friend class DistrictRepsList;

	DistrictReps(const int& districtSN, const int& rank, const RoundMode& rm) :
		dstSN(districtSN), rank(rank), round_mode(rm), repsList(rm) {}
	DistrictReps(istream& in);
	bool setDistrict(const int& dstSn, const int& eRank,const RoundMode& rm);
	bool addRep(Citizen* rep);

	const int& getDistrictSN()const { return dstSN; }
	const int& getDistrictRank()const { return rank; }
	const CitizenList& getRepsList() const { return repsList; }

	void printFirstXReps(const int& amount) const { repsList.printFirstXReps(amount); }

	friend ostream& operator<<(ostream& out, const DistrictReps& dstReps);
	bool save(ostream& out) const;
	bool load(istream& in);

	bool connectReps2Citizens(CitizenList& citList);
};

