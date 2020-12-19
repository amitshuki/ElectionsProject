#include "DistrictRepsList.h"


void DistrictRepsList::resize() {
	int i;
	if (capacity == 0)
		capacity++;
	DistrictReps* newDstRepsArr = new DistrictReps[capacity * 2];
	for (i = 0; i < logSize; i++)
		newDstRepsArr[i] = districtRepsArr[i];
	delete[] districtRepsArr;
	districtRepsArr = newDstRepsArr;
	capacity *= 2;
}


bool DistrictRepsList::addDistrict(const int& dstSN, const int& dstRank) {
	if (logSize == capacity)
		resize();
	return districtRepsArr[logSize++].setDistrict(dstSN, dstRank);
}
bool DistrictRepsList::addCitizenAsRep(Citizen* const rep, const int& dstSN) {
	int i;
	for (i = 0; i < logSize; i++)
		if (districtRepsArr[i].getDistrictSN() == dstSN)
			return districtRepsArr[i].addRep(rep);
	return false;
}

DistrictReps& DistrictRepsList::getDistRepsByDistSN(const int& distSN) {
	for (int i = 0; i < logSize; i++)
		if (distSN == districtRepsArr[i].getDistrictSN())
			return districtRepsArr[i];
}

void DistrictRepsList::printFirstXReps(const int& districtSN, const int& amountOfReps) {
	for (int i = 0; i < logSize; i++)
		if (districtRepsArr[i].getDistrictSN() == districtSN)
			districtRepsArr[i].printFirstXReps(amountOfReps);
}


DistrictRepsList& DistrictRepsList::operator=(const DistrictRepsList& other) {
	DistrictReps* newDRArr = new DistrictReps[other.capacity];
	for (int i = 0; i < other.logSize; i++)
		newDRArr[i] = other.districtRepsArr[i];
	delete[] districtRepsArr;
	districtRepsArr = newDRArr;
	logSize = other.logSize;
	capacity = other.capacity;
	return *this;
}
ostream& operator<<(ostream& out, const DistrictRepsList& drList) {
	for (int i = 0; i < drList.logSize; i++)
		out << i + 1 << ". " << drList.districtRepsArr[i] << endl;
	return out;
}