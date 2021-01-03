#pragma once
#include "DistrictRepsList.h"
#include "Citizen.h"
#include "myString.h"
using namespace myStr;
using namespace std;

class Party
{
private:
	myString name;
	int SN;
	const Citizen* candidate;
	DistrictRepsList drList;
public:
	Party() :name(""), SN(-1), candidate(nullptr) {}
	Party(const myString& newName, const int& sn, const Citizen* candidate) {
		name = newName;
		SN = sn;
		this->candidate = candidate;
	}
	~Party() {
		int i = 1;
	}

	const int& getSN()const { return SN; }
	const myString& getName()const { return name; }
	const Citizen* getCandidate()const { return candidate; }

	CitizenList& getSubRepsListInDistrict(const int& dstSN, const int& amount) {
		// Party returns a sublist of representatives in the DistrictRepsList
		return drList.getDistRepsByDistSN(dstSN).getRepsList().getSubList(amount);
	}

	bool addDistrict(const int& dstSN, const int& dstRank) { return drList.addDistrict(dstSN, dstRank); }
	bool addCitizenAsRep(Citizen* const rep, const int& dstSN) { return drList.addCitizenAsRep(rep, dstSN); }

	friend ostream& operator<<(ostream& out, const Party& prty) {
		out << "Party Serial Number: " << prty.SN << ", ";
		out << "Name: " << prty.name << endl;
		out << "Candidate: " << *(prty.candidate) << endl;
		out << "Representatives by Districts: " << endl;
		out << "============================" << endl;
		out << prty.drList << endl;
		return out;
	}
};

