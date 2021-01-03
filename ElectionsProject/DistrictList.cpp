#include "DistrictList.h"
void DistrictList::resizeArr() {
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

DistrictList::~DistrictList() {
	int i;
	for (i = 0; i < logSize; i++)
		dstArr[i]->~District();
	delete[] dstArr;
}

// Adds a district and returns a pointer to it.

District* const DistrictList::addDistrictToList(const myString& dstName, const int& rank, const DistrictType& dt) {
	if (logSize == capacity)
		resizeArr();
	if (dt == DistrictType::DIVIDED)
		dstArr[logSize++] = new DividedDistrict(dstName, rank, logSize + 1);
	else
		dstArr[logSize++] = new UnifiedDistrict(dstName, rank, logSize + 1);

	return dstArr[logSize - 1];
}
bool DistrictList::checkExistingDistrictBySN(const int& sn)const {
	int i;
	for (i = 0; i < logSize; i++)
		if (dstArr[i]->districtSN== sn)
			return true;
	return false;
}
District* DistrictList::getDistrictBySN(const int& sn)const {
	for (int i = 0; i < logSize; i++)
		if (dstArr[i]->districtSN == sn)
			return dstArr[i];
	return nullptr;
}

District* const DistrictList::operator[](const int& idx) {
	if (idx > logSize || idx < 0)
		return nullptr;
	return dstArr[idx];
}
DistrictList& DistrictList::operator=(const DistrictList& other) {
	District** newDstArr = new District * [other.capacity];
	for (int i = 0; i < other.logSize; i++)
		newDstArr[i] = other.dstArr[i];
	delete[] dstArr;
	dstArr = newDstArr;
	logSize = other.logSize;
	capacity = other.capacity;
	return *this;
}
ostream& operator<<(ostream& out, const DistrictList& dstList) {
	int i;
	for (i = 0; i < dstList.logSize; i++)
		out << *(dstList.dstArr[i]) << endl;
	return out;
}


Party* DistrictList::getResults(int& winningPartyElectorsAmount, PartyList& partyList) {
	int i, winningPartyIdx;
	Party* winningParty;
	
	// An array ordered same as partyList - counts for each party electors amount
	ElectorsForPartyArr elects_for_parties(partyList);

	// Every District - prints results.
	for (i = 0; i < this->logSize/*logSize = Num of Districtrs*/; i++) {
		elects_for_parties += dstArr[i]->getVotingresults(partyList);//Add the current district result to the overall results.
		cout << endl;
	}

	winningPartyIdx = getIndexOfWinningParty(elects_for_parties);
	winningPartyElectorsAmount = elects_for_parties[winningPartyIdx].electorsAmount;
	winningParty = elects_for_parties[winningPartyIdx].party;
	return winningParty;
}

int DistrictList::getIndexOfWinningParty(ElectorsForPartyArr& elecForParty) {
	int i, maxElectors = 0, keepMaxPartyIndex = 0;
	ElectorsForParty cur;
	for (i = 0; i < elecForParty.getSize(); i++) {
		cur = elecForParty[i];
		if (cur.electorsAmount > maxElectors) {
			maxElectors = cur.electorsAmount;
			keepMaxPartyIndex = i;
		}
		else if (cur.electorsAmount == maxElectors) {// Need to take The party with the smallest SerialNumber
			if (cur.party->getSN() < elecForParty[keepMaxPartyIndex].party->getSN())
				keepMaxPartyIndex = i;
		}
	}
	return keepMaxPartyIndex;
}

bool DistrictList::save(ostream& out)const {
	out.write(rcastcc(&logSize), sizeof(logSize));
	out.write(rcastcc(&capacity), sizeof(capacity));
	for (int i = 0; i < logSize; i++)
		if (!DistrictLoader::save(out, *(dstArr[i])))
			return false;
	return out.good();
}
bool DistrictList::load(istream& in) {
	int wantedCapacity, wantedLogSize;
	in.read(rcastc(&wantedLogSize), sizeof(wantedLogSize));
	in.read(rcastc(&wantedCapacity), sizeof(wantedCapacity));

	while (capacity < wantedCapacity)
		resizeArr();

	logSize = wantedLogSize;
	for (int i = 0; in.good() && i < logSize; i++) {
		dstArr[i] = DistrictLoader::load(in);
	}
	return in.good();
}