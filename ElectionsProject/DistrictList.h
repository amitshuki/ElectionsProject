#pragma once
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
			delete dstArr[i];
		delete[] dstArr;
	}

	// Adds a district and returns a pointer to it.
	District* addDistrictToList(const myString& dstName,const int& rank) {
		int districtSN = rand() % (100 - 1 + 1) + 1;
		if (logSize == capacity)
			resizeArr();

		while (checkExistingDistrictBySN(districtSN))//Check that there is no other dist with same SN
			districtSN = rand() % (100 - 1 + 1) + 1;
		dstArr[logSize++] = new District(dstName, rank, districtSN);
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
	

	friend ostream& operator<<(ostream& out, const DistrictList& dstList) {
		int i;
		for (i = 0; i < dstList.logSize; i++)
			out << *(dstList.dstArr[i]) << endl;
		return out;
	}

};

