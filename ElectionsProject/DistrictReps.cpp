#include <iostream>
#include "DistrictReps.h"
using namespace std;

bool DistrictReps::setDistrict(const int& dstSn, const int& eRank, const RoundMode& rm){
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

ostream& operator<<(ostream& out, const DistrictReps& dstReps) {
	if (dstReps.round_mode == RoundMode::REGULAR)
		out << "District Serial Number:" << dstReps.getDistrictSN() << endl;
	if (dstReps.repsList.getLogSize() > 0) {
		out << "Representatives: " << endl;
		out << "=============== " << endl;
		out << dstReps.repsList << endl;
	}
	else {
		if (dstReps.round_mode == RoundMode::REGULAR)
			out << "This party has no representatives in this district." << endl;
		else
			out << "This party has no representatives." << endl;
	}
	return out;
}

bool DistrictReps::save(ostream& out) {
	out.write(rcastcc(&dstSN), sizeof(dstSN));
	out.write(rcastcc(&rank), sizeof(rank));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	if (!repsList.save(out))
		return false;
	return out.good();
}
bool DistrictReps::load(istream& in) {
	return true;
}