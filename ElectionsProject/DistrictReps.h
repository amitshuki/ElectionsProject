#pragma once
#include <iostream>
#include "CitizenList.h"

using namespace std;

class DistrictReps//This is connection table #1
{
private:
	int dstSN,rank;
	CitizenList repsList;
public:
	DistrictReps() :dstSN(-1),rank(-1),repsList() {}
	DistrictReps(const int& dstSn, const int& rank) :dstSN(dstSn), rank(rank){}
	
	~DistrictReps() {
		int i = 1;
	}
	bool setDistrict(const int& dstSn,const int& eRank) { 
		if (!(this->dstSN = dstSn) || !(this->rank = eRank))
			return false;
		return true;
	}
	bool addRep(Citizen* rep) {
		if (this->rank == repsList.getLogSize()) {
			cout << "Not enough space for more representatives in this district." << endl;
			return false;
		}
		else
			return repsList.addCitizenToList(rep);
	}

	const int& getDistrictSN()const { return dstSN; }
	const int& getDistrictRank()const { return rank; }

	friend ostream& operator<<(ostream& out, const DistrictReps& dstReps) {
		out << "District Serial Number:" << dstReps.getDistrictSN() << endl;
		if (dstReps.repsList.getLogSize() > 0) {
			out << "Representatives: " << endl;
			out << "=============== " << endl;
			out << dstReps.repsList << endl;
		}
		else
			out << "This party has no representatives for this district." << endl;
		return out;
	}
};

