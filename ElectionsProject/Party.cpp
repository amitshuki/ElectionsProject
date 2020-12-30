#include "Party.h"
using namespace myStr;
using namespace std;

bool Party::addDistrict(const int& dstSN, const int& dstRank) {
	if (round_mode == RoundMode::REGULAR)
		return drList.addDistrict(dstSN, dstRank);
	else if (round_mode == RoundMode::SIMPLE) {
		if (drList.getLogSize() == 0)
			return drList.addDistrict(dstSN, dstRank);
	}
	return false;
}
bool Party::addCitizenAsRep(Citizen* const rep, const int& dstSN) {
	return drList.addCitizenAsRep(rep, dstSN); 
}

void Party::printResults(const int& districtSN, const int& electorsAmount) {
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

bool Party::save(ostream& out) {
	if (!name.save(out))
		return false;
	out.write(rcastcc(&partySN), sizeof(partySN));
	const int& candidateID = candidate->getId();
	out.write(rcastcc(&candidateID), sizeof(candidateID));// Write only candidate's ID!
	out.write(rcastcc(&round_mode), sizeof(round_mode));// Write only candidate's ID!
	if (!drList.save(out))
		return false;
	return out.good();
}
bool Party::load(istream& in) {
	return true;
}