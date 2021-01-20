#include "Party.h"
using namespace myStr;
using namespace std;

Party::Party(istream& in) :name(in), drList(in), candidate(nullptr) {
	in.read(rcastc(&partySN), sizeof(partySN));
	in.read(rcastc(&candidateID), sizeof(candidateID));
	in.read(rcastc(&round_mode), sizeof(round_mode));
}

bool Party::addDistrict(const int& dstSN, const int& dstRank) {
	if (round_mode == RoundMode::REGULAR)
		return drList.addDistrict(dstSN, dstRank);
	else if (round_mode == RoundMode::SIMPLE) {
		if (drList.getLogSize() == 0)
			return drList.addDistrict(dstSN, dstRank);
	}
	return false;
}
bool Party::addCitizenAsRep(Citizen* rep, const int& dstSN) {
	return drList.addCitizenAsRep(rep, dstSN); 
}

void Party::printResults(const int& districtSN, const int& electorsAmount) const{
	cout << "Party Name: " << name << ", Party Serial No.: " << partySN << endl;
	drList.printFirstXReps(districtSN, electorsAmount);
}

ostream& operator<<(ostream& out, const Party& prty) {
	out << "Party Serial Number: " << prty.partySN<< ", ";
	out << "Name: " << prty.name << endl;
	out << "Candidate: " << *(prty.candidate) << endl;

	if (prty.round_mode == RoundMode::REGULAR)
		out << "Representatives by Districts: " << endl;
	else
		out << "Representatives: " << endl;
	out << "============================" << endl;
	out << prty.drList << endl;
	return out;
}

bool Party::save(ostream& out) const {
	if (!name.save(out))
		return false;
	if (!drList.save(out))
		return false;
	out.write(rcastcc(&partySN), sizeof(partySN));
	out.write(rcastcc(&candidateID), sizeof(candidateID));// Write only candidate's ID!
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	return out.good();
}
bool Party::load(istream& in) {
	if (!name.load(in))
		return false;
	if (!drList.load(in))
		return false;
	in.read(rcastc(&partySN), sizeof(partySN));
	in.read(rcastc(&candidateID), sizeof(candidateID));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	return in.good();
}

bool Party::connectPartyreps2Citizens(CitizenList& citList) {
	Citizen* cnd= citList.getCitizenByID(this->candidateID);
	if (cnd)
		this->candidate = cnd;
	else
		return false;
	return this->drList.connectReps2Citizens(citList);
}