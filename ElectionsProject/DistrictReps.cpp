#include <iostream>
#include "DistrictReps.h"
using namespace std;

DistrictReps::DistrictReps(istream& in) :repsList(in) {
	in.read(rcastc(&dstSN), sizeof(dstSN));
	in.read(rcastc(&rank), sizeof(rank));
	in.read(rcastc(&round_mode), sizeof(round_mode));
}
void DistrictReps::setDistrict(const int& dstSn, const int& eRank, const RoundMode& rm){
	this->dstSN = dstSn;
	this->rank = eRank;
}
void DistrictReps::addRep(Citizen* rep) {
	if (this->rank == repsList.getLogSize())
		throw out_of_range("Representative list is full.");
	repsList.addCitizenToList(rep);
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

void DistrictReps::save(ostream& out)const {
	repsList.save(out);
	out.write(rcastcc(&dstSN), sizeof(dstSN));
	out.write(rcastcc(&rank), sizeof(rank));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	if (!out.good())
		throw outfile_error();
}
void DistrictReps::load(istream& in) {
	repsList.load(in);
	in.read(rcastc(&dstSN), sizeof(dstSN));
	in.read(rcastc(&rank), sizeof(rank));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	if (!in.good())
		throw infile_error();
}

void DistrictReps::connectReps2Citizens(CitizenList& citList) {
	int size = this->repsList.getLogSize(),cur_id;
	Citizen* cit2;
	for (int i = 0; i < size; i++) {// every rep
		cur_id = repsList[i]->getId();
		cit2 = citList.getCitizenByID(cur_id);
		delete repsList[i];// delete the "shallow" citizen
		repsList[i] = cit2;// copy the correct Citizen
	}
}