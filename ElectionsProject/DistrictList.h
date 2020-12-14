#pragma once
#include "VotingResults.h"
#include "District.h"
#include "myString.h"
using namespace myStr;

class DistrictList
{
private:
	District** dstArr;
	int logSize, capacity;
	void resizeArr() {
		int i;
		if (capacity == 0)
			capacity++;
		District** newDstArr = new District * [capacity * 2];
		for (i = 0; i < capacity * 2; i++)
			if (i < logSize)
				newDstArr[i] = dstArr[i];
			else
				newDstArr[i] = nullptr;
		delete[] dstArr;
		dstArr = newDstArr;
		capacity *= 2;
	}
public:
	DistrictList() :dstArr(nullptr), logSize(0), capacity(0){}
	~DistrictList() {
		int i;
		for (i = 0; i < logSize; i++)
			dstArr[i]->~District();
		delete[] dstArr;
	}

	// Adds a district and returns a pointer to it.
	
	District* const addDistrictToList(const myString& dstName,const int& rank) {
		if (logSize == capacity)
			resizeArr();

		//while (checkExistingDistrictBySN(districtSN))//Check that there is no other dist with same SN
		//	districtSN = rand() % (100 - 1 + 1) + 1;
		dstArr[logSize++] = new District(dstName, rank, logSize + 1);//districtSN);
		cout << "Serial number: " << logSize + 1 << endl;
		return dstArr[logSize - 1];
	}
	bool checkExistingDistrictBySN(const int& sn)const {
		int i;
		for (i = 0; i < logSize; i++)
			if (dstArr[i]->getSN() == sn)
				return true;
		return false;
	}
	District* const getDistrictBySN(const int& sn)const {
		for (int i = 0; i < logSize; i++)
			if (dstArr[i]->getSN() == sn)
				return dstArr[i];
		return nullptr;
	}
	const int& getLogSize()const { return logSize; }


	District* const operator[](const int& idx) {
		if (idx > logSize || idx < 0)
			return nullptr;
		return dstArr[idx];
	}
	DistrictList& operator=(const DistrictList& other) {
		District** newDstArr = new District * [other.capacity];
		for (int i = 0; i < other.logSize; i++)
			newDstArr[i] = other.dstArr[i];
		delete[] dstArr;
		dstArr = newDstArr;
		logSize = other.logSize;
		capacity = other.capacity;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const DistrictList& dstList) {
		int i;
		for (i = 0; i < dstList.logSize; i++)
			out << *(dstList.dstArr[i]) << endl;
		return out;
	}
	
	void showVotesResults(const PartyList& partyList)const {
	//	cout << "================================" << endl;
	//	cout << "||Voting results per District:||" << endl;
	//	cout << "================================" << endl;

		VotingResults curVR;
		int* electorsCountArr = new int[partyList.getLogSize()]{ 0 };
		int i, j, max = 0, keep;
		for (i = 0; i < logSize; i++) {
			cout << "======================================================================" << endl;
			cout << "||||||" << *(dstArr[i]) << "||||||" << endl;
			cout << "======================================================================" << endl;
			curVR = dstArr[i]->getVotingResults(partyList);
			
			cout << curVR << endl;
			for (j = 0; j < partyList.getLogSize(); j++)
				if (curVR.getElectedCandidate()->getId() == partyList.getPartyByIndex(j)->getCandidate()->getId())
					electorsCountArr[j] += curVR.getElectorsAmount();// if // for j 
			curVR.~VotingResults();
		}//for i
		for (keep = j = 0; j < partyList.getLogSize(); j++)
			if (electorsCountArr[j] > max) {
				max = electorsCountArr[j];
				keep = j;
			}// if // for j,keep
		cout << "The winner of the elections, with a total of " << electorsCountArr[keep] << " electors is: " << endl;
		cout << *(partyList.getPartyByIndex(keep)->getCandidate()) << endl;
	}
};

