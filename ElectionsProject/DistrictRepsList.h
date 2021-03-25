#pragma once
#include "DistrictReps.h"
#include "DynamicArray.h"
class DistrictRepsList
{
private:
	DynamicArray<DistrictReps*> districtRepsarr;// This is the connection list in party to each district and the
									// list of the representatives.
	RoundMode round_mode;
public:
	DistrictRepsList(const RoundMode& rm) :round_mode(rm) {}
	DistrictRepsList(istream& in) { load(in); }
	~DistrictRepsList();

	void addDistrict(const int& dstSN, const int& dstRank);
	void addCitizenAsRep(Citizen* rep, const int& dstSN);

	const int& getLogSize()const { return districtRepsarr.getLogSize(); }
	DistrictReps& getDistRepsByDistSN(const int& distSN);
	void printFirstXReps(const int& districtSN, const int& amountOfReps)const;

	DistrictRepsList& operator=(const DistrictRepsList& other);
	friend ostream& operator<<(ostream& out, const DistrictRepsList& drList);

	void save(ostream& out) const;
	void load(istream& in);

	void connectReps2Citizens(CitizenList& citList);
};

