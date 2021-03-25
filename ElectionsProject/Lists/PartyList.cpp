#include "PartyList.h"


PartyList::~PartyList() {
	for (auto& i : partyArr)
		delete i;
}

Party* PartyList::addPartyToList(const string& partName, const Citizen* candidate) {
	int size = partyArr.getLogSize();
	Party* new_party = new Party(partName, size + 1, candidate, this->round_mode);
	if (!new_party)
		throw bad_alloc();
	partyArr.push_back(new_party);
	return new_party;
}
void PartyList::addDistrictToParties(const int& dstSN, const int& dstRank) {
	for (auto& i : partyArr) {// add District to each party!
		i->addDistrict(dstSN, dstRank);
	}
}
bool PartyList::checkExistingPartyBySN(const int& sn)const {
	for (auto& i : partyArr)
		if (i->getSN() == sn)
			return true;
	return false;
}
Party* PartyList::getPartyBySN(const int& sn)const {
	for (auto& i : partyArr)
		if (i->getSN() == sn)
			return i;
	return nullptr;
}

Party* PartyList::getPartyByIndex(const int& idx)const {
	if (idx >= 0 && idx < partyArr.getLogSize())
		return partyArr[idx];
	throw range_error("Index out of range");
}

PartyList& PartyList::operator=(const PartyList& other) {
	if (this != &other)
		this->partyArr = other.partyArr;
	return *this;
}

ostream& operator<<(ostream& out, const PartyList& partyList) {
	int count = 0;
	for (auto& i : partyList.partyArr)
		out << ++count << ". " << *i << endl;
	return out;
}

void PartyList::save(ostream& out) const {
	out.write(rcastcc(&partyArr.getLogSize()), sizeof(partyArr.getLogSize()));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	for (auto& i : partyArr) {
		i->save(out);
		if (!out.good())
			throw outfile_error("PartyList");
	}
}
void PartyList::load(istream& in) {
	int size;
	in.read(rcastc(&size), sizeof(size));
	in.read(rcastc(&round_mode), sizeof(round_mode));

	DynamicArray<Party*>newPrtArr(size);
	Party* party;
	try {
		for (auto i = 0; in.good() && i < size; i++) {
			party = new Party(in);
			if (!party) {
				for (auto& j : newPrtArr)
					delete j;
				throw bad_alloc();
			}
			newPrtArr.push_back(party);
		}
	}
	catch (exception& exp) {
		cout << "PartyList loading failure: " << exp.what() << endl;
		throw infile_error("PartyList");
	}
	if (!in.good())
		throw infile_error("PartyList");
	partyArr = newPrtArr;
}

void PartyList::connectPartyreps2Citizens(CitizenList& citList) {
	for (auto& i : partyArr) {
		i->connectPartyreps2Citizens(citList);
	}
}