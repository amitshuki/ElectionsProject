#pragma once
#include <iostream>
#include "CitizenList.h"

using namespace std;

class DistrictReps//This is connection table #1
{
private:
	int dstSN, rank;
	CitizenList repsList;
public:
	DistrictReps() :dstSN(-1), rank(-1) {}
	DistrictReps(const int& dstSn, const int& rank) :dstSN(dstSn), rank(rank) {}

	bool setDistrict(const int& dstSn, const int& eRank) {
		if (!(this->dstSN = dstSn) || !(this->rank = eRank))
			return false;
		return true;
	}
	bool addRep(Citizen* const rep) {
		if (this->rank == repsList.getLogSize()) {
			return false;
		}
		else {
			if (!repsList.addCitizenToList(rep))
				cout << "Representative already in list." << endl;
			return false;
		}
		return true;
	}

	const int& getDistrictSN()const { return dstSN; }
	const int& getDistrictRank()const { return rank; }
	const CitizenList& getRepsList() const { return repsList; }

	void printFirstXReps(const int& amount) { repsList.printFirstXReps(amount); }



	DistrictReps& operator=(const DistrictReps& other) {
		this->dstSN = other.dstSN;
		this->rank = other.rank;
		this->repsList = other.repsList;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const DistrictReps& dstReps) {
		out << "District Serial Number:" << dstReps.getDistrictSN() << endl;
		if (dstReps.repsList.getLogSize() > 0) {
			out << "Representatives: " << endl;
			out << "=============== " << endl;
			out << dstReps.repsList << endl;
		}
		else
			out << "This party has no representatives in this district." << endl;
		return out;
	}
};

