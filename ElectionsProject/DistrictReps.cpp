#include <iostream>
#include "DistrictReps.h"
using namespace std;

DistrictReps::DistrictReps(istream& in) :repsList(in) {
	in.read(rcastc(&dstSN), sizeof(dstSN));
	in.read(rcastc(&rank), sizeof(rank));
	in.read(rcastc(&round_mode), sizeof(round_mode));
}
bool DistrictReps::setDistrict(const int& dstSn, const int& eRank, const RoundMode& rm){
	if (!(this->dstSN = dstSn) || !(this->rank = eRank))
		return false;
	return true;
}
bool DistrictReps::addRep(Citizen* rep) {
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

bool DistrictReps::save(ostream& out)const {
	if (!repsList.save(out))
		return false;
	out.write(rcastcc(&dstSN), sizeof(dstSN));
	out.write(rcastcc(&rank), sizeof(rank));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	return out.good();
}
bool DistrictReps::load(istream& in) {
	if (!repsList.load(in))
		return false;
	in.read(rcastc(&dstSN), sizeof(dstSN));
	in.read(rcastc(&rank), sizeof(rank));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	return in.good();
}

bool DistrictReps::connectReps2Citizens(CitizenList& citList) {
	int size = this->repsList.getLogSize();
	Citizen* cit1, * cit2;
	for (int i = 0; i < size; i++) {// every rep
		cit1 = repsList[i];
		cit2 = citList.getCitizenByID(cit1->getId());
		if (cit1 && cit2)
			*cit1 = *cit2;// copy the correct Citizen
		else
			return false;
	}
	return true;
}