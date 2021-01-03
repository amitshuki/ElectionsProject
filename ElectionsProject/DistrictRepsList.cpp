#include "DistrictRepsList.h"


void DistrictRepsList::resize() {
	int i;
	if (capacity == 0)
		capacity++;
	DistrictReps** newDstRepsArr = new DistrictReps*[capacity * 2];
	for (i = 0; i < capacity * 2; i++)
		if (i < logSize)
			newDstRepsArr[i] = districtRepsArr[i];
		else
			newDstRepsArr[i] = nullptr;
	delete[] districtRepsArr;
	districtRepsArr = newDstRepsArr;
	capacity *= 2;}


bool DistrictRepsList::addDistrict(const int& dstSN, const int& dstRank) {
	if (logSize == capacity)
		resize();
	return districtRepsArr[logSize++] = new DistrictReps(dstSN, dstRank, this->round_mode);// setDistrict(dstSN, dstRank, this->round_mode);
}
bool DistrictRepsList::addCitizenAsRep(Citizen* const rep, const int& dstSN) {
	int i;
	for (i = 0; i < logSize; i++)
		if (districtRepsArr[i]->getDistrictSN() == dstSN)
			return districtRepsArr[i]->addRep(rep);
	return false;
}

DistrictReps& DistrictRepsList::getDistRepsByDistSN(const int& distSN) {
	for (int i = 0; i < logSize; i++)
		if (distSN == districtRepsArr[i]->getDistrictSN())
			return *(districtRepsArr[i]);
}

void DistrictRepsList::printFirstXReps(const int& districtSN, const int& amountOfReps) {
	for (int i = 0; i < logSize; i++)
		if (districtRepsArr[i]->getDistrictSN() == districtSN)
			districtRepsArr[i]->printFirstXReps(amountOfReps);
}


DistrictRepsList& DistrictRepsList::operator=(const DistrictRepsList& other) {
	DistrictReps** newDRArr = new DistrictReps*[other.capacity];
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
		out << i + 1 << ". " << *(drList.districtRepsArr[i]) << endl;
	return out;
}

bool DistrictRepsList::save(ostream& out) const {
	out.write(rcastcc(&logSize), sizeof(logSize));
	out.write(rcastcc(&capacity), sizeof(capacity));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	//TL
	for (int i = 0; i < logSize; i++)
		if (!districtRepsArr[i]->save(out))
			return false;
	return out.good();
}
bool DistrictRepsList::load(istream& in) {
	int wantedCapacity, wantedLogSize;
	in.read(rcastc(&wantedLogSize), sizeof(wantedLogSize));
	in.read(rcastc(&wantedCapacity), sizeof(wantedCapacity));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	while (capacity < wantedCapacity)
		resize();
	logSize = wantedLogSize;
	//TL
	for (int i = 0; in.good() && i < logSize; i++) {
		if (!districtRepsArr[i]) {
			districtRepsArr[i] = new DistrictReps(in);
		}
		else if (!districtRepsArr[i]->load(in))
			return false;
	}
	return in.good();
}

bool DistrictRepsList::connectReps2Citizens(CitizenList& citList){
	for (int i = 0; i < logSize; i++)// per District
		if (!districtRepsArr[i]->connectReps2Citizens(citList))
			return false;
	return true;
}