#include "Party.h"
using namespace myStr;
using namespace std;


Party::Party(const myString& newName, const int& sn, const Citizen* candidate) {
	name = newName;
	SN = sn;
	this->candidate = candidate;
}

void Party::printResults(const int& districtSN, const int& electorsAmount) {
	cout << "Party Name: " << name << ", Party Serial No.: " << SN << endl;
	drList.printFirstXReps(districtSN, electorsAmount);
}

CitizenList& Party::getSubRepsListInDistrict(const int& dstSN, const int& amount) {
	// Party returns a sublist of representatives in the DistrictRepsList
	return drList.getDistRepsByDistSN(dstSN).getRepsList().getSubList(amount);
}

ostream& operator<<(ostream& out, const Party& prty) {
	out << "Party Serial Number: " << prty.SN << ", ";
	out << "Name: " << prty.name << endl;
	out << "Candidate: " << *(prty.candidate) << endl;
	out << "Representatives by Districts: " << endl;
	out << "============================" << endl;
	out << prty.drList << endl;
	return out;
}