#include "PartyList.h"

using namespace myStr;
PartyList::~PartyList() {
	for (auto& i : partyArr1)
		delete i;
}

Party* PartyList::addPartyToList(const myString& partName, const Citizen* candidate) {
	int size = partyArr1.getLogSize();
	partyArr1.push_back(new Party(partName, size + 1, candidate, this->round_mode));
	return partyArr1.back();
}
bool PartyList::addDistrictToParties(const int& dstSN, const int& dstRank) {
	for (auto& i : partyArr1)
		if (!i->addDistrict(dstSN, dstRank))
			return false;
	return true;
}

bool PartyList::checkExistingPartyBySN(const int& sn)const {
	for (auto& i : partyArr1)
		if (i->getSN() == sn)
			return true;
	return false;
}
Party* PartyList::getPartyBySN(const int& sn)const {
	for (auto& i : partyArr1)
		if (i->getSN() == sn)
			return i;
	return nullptr;
}


Party* PartyList::getPartyByIndex(const int& idx)const {
	if (idx >= 0 && idx < partyArr1.getLogSize())
		return partyArr1[idx];
	return nullptr;
}

ostream& operator<<(ostream& out, const PartyList& partyList) {
	int count = 0;
	for (auto& i : partyList.partyArr1)
		out << ++count << ". " << *i << endl;
	return out;
}

bool PartyList::save(ostream& out) const {
	out.write(rcastcc(&partyArr1.getLogSize()), sizeof(partyArr1.getLogSize()));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	for (auto& i : partyArr1)
		if (!i->save(out))
			return false;
	return out.good();
}
bool PartyList::load(istream& in) {
	int size;
	in.read(rcastc(&size), sizeof(size));
	in.read(rcastc(&round_mode), sizeof(round_mode));

	DynamicArray<Party*>newPrtArr(size);

	for (auto i = 0; in.good() && i < size; i++)
		newPrtArr.push_back(new Party(in));

	partyArr1 = newPrtArr;
	return in.good();
}

bool PartyList::connectPartyreps2Citizens(CitizenList& citList) {
	for (auto& i : partyArr1)
		if (!i->connectPartyreps2Citizens(citList))
			return false;
	return true;
}