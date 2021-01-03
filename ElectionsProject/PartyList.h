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

	Party* const addPartyToList(const myString& partName, const Citizen* candidate) {
		int partySN = rand() % (200 - 101 + 1) + 101;
		if (logSize == capacity)
			resizeArr();

		while (checkExistingPartyBySN(partySN))//Check that there is no other party with same SN
			partySN = rand() % (200 - 101 + 1) + 101;
		cout << "Serial number: " << partySN << endl;
		return partyArr[logSize++] = new Party(partName, logSize + 1, candidate);
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

	const int& getLogSize()const { return logSize; }
	
	Party* getPartyByIndex(const int& idx)const {
		if (idx >= 0 && idx < logSize)
			return partyArr[idx];
		return nullptr;
	}

	Party* operator[](const int& idx) {
		if (idx >= 0 && idx < logSize)
			return partyArr[idx];
		return nullptr;
	}
	friend ostream& operator<<(ostream& out, const PartyList& partyList) {
		int i;
		for (i = 0; i < partyList.logSize; i++)
			out << i + 1 << ". " << *(partyList.partyArr[i]) << endl;
		return out;
	}
};

