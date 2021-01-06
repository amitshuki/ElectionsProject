#include "PartyList.h"

using namespace myStr;
void PartyList::resizeArr() {
	int i;
	if (capacity == 0)
		capacity++;
	Party** newPrtArr = new Party * [capacity * 2];
	for (i = 0; i < capacity * 2; i++)
		if (i < logSize)
			newPrtArr[i] = partyArr[i];
		else
			newPrtArr[i] = nullptr;
	delete[] partyArr;
	partyArr = newPrtArr;
	capacity *= 2;
}
PartyList::~PartyList() {
	int i;
	for (i = 0; i < logSize; i++)
		delete partyArr[i];
	delete[] partyArr;
}

Party* const PartyList::addPartyToList(const myString& partName, const Citizen* candidate) {
	if (logSize == capacity)
		resizeArr();
	return partyArr[logSize++] = new Party(partName, logSize + 1, candidate, this->round_mode);
}
bool PartyList::addDistrictToParties(const int& dstSN, const int& dstRank) {
	int i;
	for (i = 0; i < logSize; i++)
		if (!partyArr[i]->addDistrict(dstSN, dstRank))
			return false;
	return true;
}

bool PartyList::checkExistingPartyBySN(const int& sn)const {
	int i;
	for (i = 0; i < logSize; i++)
		if (partyArr[i]->getSN() == sn)
			return true;
	return false;
}
Party* const PartyList::getPartyBySN(const int& sn)const {
	for (int i = 0; i < logSize; i++)
		if (partyArr[i]->getSN() == sn)
			return partyArr[i];
	return nullptr;
}


Party* PartyList::getPartyByIndex(const int& idx)const {
	if (idx >= 0 && idx < logSize)
		return partyArr[idx];
	return nullptr;
}

Party* PartyList::operator[](const int& idx)const {
	if (idx >= 0 && idx < logSize)
		return partyArr[idx];
	return nullptr;
}
ostream& operator<<(ostream& out, const PartyList& partyList) {
	int i;
	for (i = 0; i < partyList.logSize; i++)
		out << i + 1 << ". " << *(partyList.partyArr[i]) << endl;
	return out;
}

bool PartyList::save(ostream& out) const {
	out.write(rcastcc(&logSize), sizeof(logSize));
	out.write(rcastcc(&capacity), sizeof(capacity));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	for (auto i = 0; i < logSize; i++)
		if (!partyArr[i]->save(out))
			return false;
	return out.good();
}
bool PartyList::load(istream& in) {
	int wantedCapacity, wantedLogSize;
	in.read(rcastc(&wantedLogSize), sizeof(wantedLogSize));
	in.read(rcastc(&wantedCapacity), sizeof(wantedCapacity));
	in.read(rcastc(&round_mode), sizeof(round_mode));

	while (capacity < wantedCapacity)
		resizeArr();
	logSize = wantedLogSize;

	for (auto i = 0; in.good() && i < logSize; i++)
		if (!partyArr[i])
			partyArr[i] = new Party(in);
		else if(!partyArr[i]->load(in))
			return false;
	return in.good();
}

bool PartyList::connectPartyreps2Citizens(CitizenList& citList) {
	for (int i = 0; i < logSize; i++)// Per Party
		if (!partyArr[i]->connectPartyreps2Citizens(citList))
			return false;
	return true;
}