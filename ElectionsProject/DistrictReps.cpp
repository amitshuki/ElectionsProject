#include <iostream>
#include "DistrictReps.h"
using namespace std;

DistrictReps::DistrictReps() :dstSN(-1), rank(-1) {}
DistrictReps::DistrictReps(const int& dstSn, const int& rank) : dstSN(dstSn), rank(rank) {}

bool DistrictReps::setDistrict(const int& dstSn, const int& eRank) {
	if (!(this->dstSN = dstSn) || !(this->rank = eRank))
		return false;
	return true;
}
bool DistrictReps::addRep(Citizen* const rep) {
	if (this->rank == repsList.getLogSize())
		return false;

	if (repsList.addCitizenToList(rep))
		return true;

	return false;
}



DistrictReps& DistrictReps::operator=(const DistrictReps& other) {
	this->dstSN = other.dstSN;
	this->rank = other.rank;
	this->repsList = other.repsList;
	return *this;
}

ostream& operator<<(ostream& out, const DistrictReps& dstReps) {
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