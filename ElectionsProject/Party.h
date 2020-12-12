#pragma once
#include "DistrictReps.h"
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
	DistrictReps* districtRepsArr;// This is the connection list in party to each district and the
									// list of the representatives.
	int districtsAmount, districtRepsArrCapacity;

	void resizeDistRepsArr() {
		int i;
		if (districtRepsArrCapacity == 0)
			districtRepsArrCapacity++;
		DistrictReps* newDstRepsArr = new DistrictReps[districtRepsArrCapacity * 2];
		for (i = 0; i < districtsAmount; i++)
				newDstRepsArr[i] = districtRepsArr[i];
		delete[] districtRepsArr;
		districtRepsArr = newDstRepsArr;
		districtRepsArrCapacity *= 2;
	}
public:
	Party() :name(""), SN(-1), candidate(nullptr), districtRepsArr(nullptr), 
		districtsAmount(0), districtRepsArrCapacity(0) {}
	Party(const myString& newName, const int& sn, const Citizen* candidate) {
		name = newName;
		SN = sn;
		this->candidate = candidate;
		districtRepsArr = nullptr;
		districtsAmount = districtRepsArrCapacity = 0;
	}
	/*Party(const Party& other) {
		name = other.name;
		SN = other.SN;
		candidateID = other.candidateID;
		districtRepsArr = new DistrictReps[other.districtRepsArrCapacity];

		for (int i = 0; i < other.districtsAmount; i++)
			districtRepsArr[i] = other.districtRepsArr[i];

		districtsAmount = other.districtsAmount;
		districtRepsArrCapacity = other.districtRepsArrCapacity;
	}*/
	~Party() {
		int i;
		if (districtRepsArrCapacity > 0) {
			for (i = 0; i < districtsAmount; i++)
				districtRepsArr[i].~DistrictReps();
			delete[] districtRepsArr;
		}
	}

	const int& getSN()const { return SN; }
	const myString& getName()const { return name; }

	bool addDistrict(const int& dstSN,const int& dstRank) {
		if (districtsAmount == districtRepsArrCapacity)
			resizeDistRepsArr();
		return districtRepsArr[districtsAmount++].setDistrict(dstSN, dstRank);
	}
	bool addCitizenAsRep(const Citizen* rep, const int& dstSN) {
		int i;
		for (i = 0; i < districtsAmount; i++)
			if (districtRepsArr[i].getDistrictSN() == dstSN)
				return districtRepsArr[i].addRep(const_cast<Citizen*>(rep));
		return false;
	}

	friend ostream& operator<<(ostream& out, const Party& prty) {
		out << "Party Serial Number:" << prty.SN << ", ";
		out << "Name :" << prty.name << endl;
		out << "Candidate :" << prty.candidate << endl;
		out << "Representatives by Districts: " << endl;
		out << "============================" << endl;
		for (int i = 0; i < prty.districtsAmount; i++)
			out << prty.districtRepsArr[i];
		return out;
	}
};

