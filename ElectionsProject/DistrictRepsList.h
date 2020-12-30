#pragma once
#include "DistrictReps.h"
class DistrictRepsList
{
private:
	DistrictReps** districtRepsArr;// This is the connection list in party to each district and the
									// list of the representatives.
	int logSize, capacity;
	RoundMode round_mode;

	void resize();
public:
	DistrictRepsList(const RoundMode& rm) :logSize(0), capacity(0), districtRepsArr(nullptr), round_mode(rm) {}
	~DistrictRepsList() {
		for (int i = 0; i < logSize; i++)
			delete districtRepsArr[i];
		delete[] districtRepsArr;
	}

	bool addDistrict(const int& dstSN, const int& dstRank);
	bool addCitizenAsRep(Citizen* const rep, const int& dstSN);

	const int& getLogSize()const { return logSize; }
	DistrictReps& getDistRepsByDistSN(const int& distSN);
	void printFirstXReps(const int& districtSN, const int& amountOfReps);

	DistrictRepsList& operator=(const DistrictRepsList& other);
	friend ostream& operator<<(ostream& out, const DistrictRepsList& drList);

	bool save(ostream& out);
	bool load(istream& in);
};

