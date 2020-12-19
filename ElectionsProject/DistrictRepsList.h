#pragma once
#include "DistrictReps.h"
class DistrictRepsList
{
private:
	DistrictReps* districtRepsArr;// This is the connection list in party to each district and the
									// list of the representatives.
	int logSize, capacity;
	
	void resize();
public:
	DistrictRepsList():logSize(0),capacity(0),districtRepsArr(nullptr){}
	~DistrictRepsList() {
		delete[] districtRepsArr;
	}

	bool addDistrict(const int& dstSN, const int& dstRank);
	bool addCitizenAsRep(Citizen* const rep, const int& dstSN);

	DistrictReps& getDistRepsByDistSN(const int& distSN);
	void printFirstXReps(const int& districtSN, const int& amountOfReps);

	DistrictRepsList& operator=(const DistrictRepsList& other);
	friend ostream& operator<<(ostream& out, const DistrictRepsList& drList);
};

