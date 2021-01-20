#include "DistrictRepsList.h"

DistrictRepsList::~DistrictRepsList() {
	for (auto& i : districtRepsarr)
		delete i;
}

bool DistrictRepsList::addDistrict(const int& dstSN, const int& dstRank) {
	districtRepsarr.push_back(new DistrictReps(dstSN, dstRank, this->round_mode));
	return true;// need to change to exeptions
}
bool DistrictRepsList::addCitizenAsRep(Citizen* rep, const int& dstSN) {
	for (auto& i : districtRepsarr)
		if (i->dstSN == dstSN)
			return i->addRep(rep);
	return false;
}

DistrictReps& DistrictRepsList::getDistRepsByDistSN(const int& distSN) {
	for (auto& i:districtRepsarr)
		if (i->dstSN==distSN)
			return *i;
}

void DistrictRepsList::printFirstXReps(const int& districtSN, const int& amountOfReps)const {
	for (auto& i:districtRepsarr)
		if (i->dstSN == districtSN)
			i->printFirstXReps(amountOfReps);
}


DistrictRepsList& DistrictRepsList::operator=(const DistrictRepsList& other) {
	districtRepsarr = other.districtRepsarr;
	return *this;
}
ostream& operator<<(ostream& out, const DistrictRepsList& drList) {
	int count = 0;
	for (auto& i : drList.districtRepsarr)
		out << ++count << ". " << *i << endl;
	return out;
}

bool DistrictRepsList::save(ostream& out) const {
	out.write(rcastcc(&(districtRepsarr.getLogSize())), sizeof(districtRepsarr.getLogSize()));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	for (auto& i : districtRepsarr)
		if (!i->save(out))
			return false;
	return out.good();
}
bool DistrictRepsList::load(istream& in) {
	int size;
	in.read(rcastc(&size), sizeof(size));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	DynamicArray<DistrictReps*> newDRArr(size);
	for (auto i = 0; i < size; i++)
		newDRArr.push_back(new DistrictReps(in));
	districtRepsarr = newDRArr;
	return in.good();
}

bool DistrictRepsList::connectReps2Citizens(CitizenList& citList){
	for (auto& i : districtRepsarr)// per District
		if (!i->connectReps2Citizens(citList))
			return false;
	return true;
}