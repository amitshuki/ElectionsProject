#pragma once
#include "Party.h"
#include "myString.h"
using namespace myStr;
class PartyList
{
	Party** partyArr;
	int logSize, capacity;

	void resizeArr() {
		int i;
		if (capacity == 0)
			capacity++;
		Party** newPrtArr = new Party* [capacity * 2];
		for (i = 0; i < capacity * 2; i++)
			if (i < logSize)
				newPrtArr[i] = partyArr[i];
			else
				newPrtArr[i] = nullptr;
		delete[] partyArr;
		partyArr = newPrtArr;
		capacity *= 2;
	}
public:
	PartyList() :partyArr(nullptr), logSize(0), capacity(0) {}
	~PartyList() {
		int i;
		for (i = 0; i < logSize; i++)
			delete partyArr[i];
		delete[] partyArr;
	}

	bool addPartyToList(const myString& partName, const Citizen* candidate) {
		int partySN = rand() % (200 - 101 + 1) + 101;
		if (logSize == capacity)
			resizeArr();

		while (checkExistingPartyBySN(partySN))//Check that there is no other party with same SN
			partySN = rand() % (200 - 101 + 1) + 101;

		return partyArr[logSize++] = new Party(partName, partySN, candidate);
	}
	bool addDistrictToParties(const int& dstSN,const int& dstRank) {
		int i;
		for (i = 0; i < logSize; i++)
			if (!partyArr[i]->addDistrict(dstSN, dstRank))
				return false;
		return true;
	}

	bool checkExistingPartyBySN(const int& sn)const {
		int i;
		for (i = 0; i < logSize; i++)
			if (partyArr[i]->getSN() == sn)
				return true;
		return false;
	}
	Party* const getPartyBySN(const int& sn)const {
		for (int i = 0; i < logSize; i++)
			if (partyArr[i]->getSN() == sn)
				return partyArr[i];
		return nullptr;
	}


	friend ostream& operator<<(ostream& out, const PartyList& partyList) {
		int i;
		for (i = 0; i < partyList.logSize; i++)
			out << *(partyList.partyArr[i]) << endl;
		return out;
	}



};

