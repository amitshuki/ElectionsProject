#include "DistrictRepsList.h"

DistrictRepsList::~DistrictRepsList() {
	for (auto& i : districtRepsarr)
		delete i;
}

void DistrictRepsList::addDistrict(const int& dstSN, const int& dstRank) {
	DistrictReps* dr = new DistrictReps(dstSN, dstRank, this->round_mode);
	if (!dr)
		throw bad_alloc();
	districtRepsarr.push_back(dr);
}
void DistrictRepsList::addCitizenAsRep(Citizen* rep, const int& dstSN) {
	for (auto& i : districtRepsarr)
		if (i->dstSN == dstSN) {
			i->addRep(rep);
			return;// IMPORTANT! == If district was found - end the method.
		}
	throw no_entity_error("DistrictReps");// if district was not found - throw exception
}

DistrictReps& DistrictRepsList::getDistRepsByDistSN(const int& distSN) {
	for (auto& i:districtRepsarr)
		if (i->dstSN==distSN)
			return *i;
	throw no_entity_error("DistrictReps");// if district was not found - throw exception
}

void DistrictRepsList::printFirstXReps(const int& districtSN, const int& amountOfReps)const {
	for (auto& i : districtRepsarr) {
		if (i->dstSN == districtSN) {
			i->printFirstXReps(amountOfReps);
			return;// Important!
		}
	}
	throw no_entity_error("DistrictReps");// if district was not found - throw exception
}


DistrictRepsList& DistrictRepsList::operator=(const DistrictRepsList& other) {
	if (this != &other)
		districtRepsarr = other.districtRepsarr;
	return *this;
}
ostream& operator<<(ostream& out, const DistrictRepsList& drList) {
	int count = 0;
	for (auto& i : drList.districtRepsarr)
		out << ++count << ". " << *i << endl;
	return out;
}

void DistrictRepsList::save(ostream& out) const {
	out.write(rcastcc(&(districtRepsarr.getLogSize())), sizeof(districtRepsarr.getLogSize()));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	for (auto& i : districtRepsarr) {
		i->save(out);
		if (!out.good())
			throw outfile_error("DistrictRepsList");
	}
}
void DistrictRepsList::load(istream& in) {
	int size;
	in.read(rcastc(&size), sizeof(size));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	DynamicArray<DistrictReps*> newDRArr(size);
	DistrictReps* dr;
	try {
		for (auto i = 0; in.good() && i < size; i++) {
			dr = new DistrictReps(in);
			if (!dr) {
				for (auto& j : newDRArr)
					delete j;
				throw bad_alloc();
			}
			newDRArr.push_back(dr);
		}
	}
	catch (exception& exp) {
		cout << "DistrictRepsList loading failure: " << exp.what() << endl;
		throw infile_error("DistrictRepsList");
	}
	if (!in.good())
		throw infile_error("DistrictRepsList");
	districtRepsarr = newDRArr;
}

void DistrictRepsList::connectReps2Citizens(CitizenList& citList){
	for (auto& i : districtRepsarr) {// per District
		i->connectReps2Citizens(citList);// Connects reps(id's only) to actual citizens.
	}
}