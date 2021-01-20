#pragma once
#include "DistrictReps.h"
#include "DynamicArray.h"
class DistrictRepsList
{
private:
	DynamicArray<DistrictReps*> districtRepsArr1;// This is the connection list in party to each district and the
									// list of the representatives.
	DistrictReps** districtRepsArr;
	int logSize, capacity;
	RoundMode round_mode;

	//void resize();TL
public:
	DistrictRepsList(const RoundMode& rm) :/*logSize(0), capacity(0), districtRepsArr(nullptr), */round_mode(rm) {}
	DistrictRepsList(istream& in) /*:districtRepsArr(nullptr), logSize(0), capacity(0) */{ load(in); }
	~DistrictRepsList();

	bool addDistrict(const int& dstSN, const int& dstRank);
	bool addCitizenAsRep(Citizen* rep, const int& dstSN);

	const int& getLogSize()const { return logSize; }
	DistrictReps& getDistRepsByDistSN(const int& distSN);
	void printFirstXReps(const int& districtSN, const int& amountOfReps)const;

	DistrictRepsList& operator=(const DistrictRepsList& other);
	friend ostream& operator<<(ostream& out, const DistrictRepsList& drList);

	bool save(ostream& out) const;
	bool load(istream& in);

	bool connectReps2Citizens(CitizenList& citList);
};

