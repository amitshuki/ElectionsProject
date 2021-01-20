#include "DistrictRepsList.h"


//void DistrictRepsList::resize() {
//	int i;
//	if (capacity == 0)
//		capacity++;
//	DistrictReps** newDstRepsArr = new DistrictReps*[capacity * 2];
//	for (i = 0; i < capacity * 2; i++)
//		if (i < logSize)
//			newDstRepsArr[i] = districtRepsArr[i];
//		else
//			newDstRepsArr[i] = nullptr;
//	delete[] districtRepsArr;
//	districtRepsArr = newDstRepsArr;
//	capacity *= 2;
//}

DistrictRepsList::~DistrictRepsList() {
	/*for (int i = 0; i < logSize; i++)
		delete districtRepsArr[i];
	delete[] districtRepsArr;*/
	for (auto& i : districtRepsarr)
		delete i;
}

bool DistrictRepsList::addDistrict(const int& dstSN, const int& dstRank) {
	/*if (logSize == capacity)
		resize();
	return districtRepsArr[logSize++] = new DistrictReps(dstSN, dstRank, this->round_mode);// setDistrict(dstSN, dstRank, this->round_mode);
	*/
	districtRepsarr.push_back(new DistrictReps(dstSN, dstRank, this->round_mode));
	return true;// need to change to exeptions
}
bool DistrictRepsList::addCitizenAsRep(Citizen* rep, const int& dstSN) {
	/*int i;
	for (i = 0; i < logSize; i++)
		if (districtRepsArr[i]->getDistrictSN() == dstSN)
			return districtRepsArr[i]->addRep(rep);*/
	for(auto& i:districtRepsarr)
		if (i->dstSN == dstSN)
			return i->addRep(rep);
	return false;
}

DistrictReps& DistrictRepsList::getDistRepsByDistSN(const int& distSN) {
	/*for (int i = 0; i < logSize; i++)
		if (distSN == districtRepsArr[i]->getDistrictSN())
			return *(districtRepsArr[i]);*/
	for (auto& i:districtRepsarr)
		if (i->dstSN==distSN)
			return *i;
}

void DistrictRepsList::printFirstXReps(const int& districtSN, const int& amountOfReps)const {
	/*for (int i = 0; i < logSize; i++)
		if (districtRepsArr[i]->getDistrictSN() == districtSN)
			districtRepsArr[i]->printFirstXReps(amountOfReps);*/
	for (auto& i:districtRepsarr)
		if (i->dstSN == districtSN)
			i->printFirstXReps(amountOfReps);
}


DistrictRepsList& DistrictRepsList::operator=(const DistrictRepsList& other) {
	districtRepsarr = other.districtRepsarr;
	return *this;
}
ostream& operator<<(ostream& out, const DistrictRepsList& drList) {
	/*for (int i = 0; i < drList.logSize; i++)
		out << i + 1 << ". " << *(drList.districtRepsArr[i]) << endl;*/
	int count = 0;
	for (auto& i : drList.districtRepsarr)
		out << ++count << ". " << *i << endl;
	return out;
}

bool DistrictRepsList::save(ostream& out) const {
	out.write(rcastcc(&(districtRepsarr.getLogSize())), sizeof(districtRepsarr.getLogSize()));
	//out.write(rcastcc(&capacity), sizeof(capacity));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	/*for (int i = 0; i < logSize; i++)
		if (!districtRepsArr[i]->save(out))
			return false;*/
	for (auto& i : districtRepsarr)
		if (!i->save(out))
			return false;
	return out.good();
}
bool DistrictRepsList::load(istream& in) {
	/*int wantedCapacity, wantedLogSize;
	in.read(rcastc(&wantedLogSize), sizeof(wantedLogSize));
	in.read(rcastc(&wantedCapacity), sizeof(wantedCapacity));*/
	int size;
	in.read(rcastc(&size), sizeof(size));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	/*while (capacity < wantedCapacity)
		resize();
	logSize = wantedLogSize;*/
	//TL
	/*for (int i = 0; in.good() && i < logSize; i++) {
		if (!districtRepsArr[i]) {
			districtRepsArr[i] = new DistrictReps(in);
		}
		else if (!districtRepsArr[i]->load(in))
			return false;
	}*/
	DynamicArray<DistrictReps*> newDRArr(size);
	for (auto i = 0; i < size; i++)
		newDRArr.push_back(new DistrictReps(in));
	districtRepsarr = newDRArr;
	return in.good();
}

bool DistrictRepsList::connectReps2Citizens(CitizenList& citList){
	//for (int i = 0; i < logSize; i++)// per District
	//	if (!districtRepsArr[i]->connectReps2Citizens(citList))
	//		return false;
	for (auto& i : districtRepsarr)// per District
		if (!i->connectReps2Citizens(citList))
			return false;
	return true;
}