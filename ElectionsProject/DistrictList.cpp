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
DistrictList::DistrictList() :dstArr(nullptr), logSize(0), capacity(0) {}
DistrictList::~DistrictList() {
	int i;
	for (i = 0; i < logSize; i++)
		dstArr[i]->~District();
	delete[] dstArr;
}

// Adds a district and returns a pointer to it.

District* const DistrictList::addDistrictToList(const myString& dstName, const int& rank) {
	if (logSize == capacity)
		resizeArr();

	//while (checkExistingDistrictBySN(districtSN))//Check that there is no other dist with same SN
	//	districtSN = rand() % (100 - 1 + 1) + 1;
	dstArr[logSize++] = new District(dstName, rank, logSize + 1);//districtSN);
	//cout << "Serial number: " << logSize + 1 << endl;
	return dstArr[logSize - 1];
}
bool DistrictList::checkExistingDistrictBySN(const int& sn)const {
	int i;
	for (i = 0; i < logSize; i++)
		if (dstArr[i]->getSN() == sn)
			return true;
	return false;
}
District* const DistrictList::getDistrictBySN(const int& sn)const {
	for (int i = 0; i < logSize; i++)
		if (dstArr[i]->getSN() == sn)
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
	int i, j, const num_of_parties = partyList.getLogSize();
	int winningPartySN, winningPartyIdx;
	Party* winningParty;
	// An array ordered same as partyList - counts for each party electors amount
	ElectorsForParty* electors_for_parties = new ElectorsForParty[num_of_parties];

	for (i = 0; i < num_of_parties; i++)
		electors_for_parties[i].party = partyList[i];

	// Every District - prints results.
	for (i = 0; i < this->logSize/*logSize = Num of Districtrs*/; i++) {
		// Winning partySN for current district.
		winningPartySN = dstArr[i]->getVotingresults(partyList);
		for (j = 0; j < num_of_parties; j++) {
			if (electors_for_parties[j].party->getSN() == winningPartySN) {
				electors_for_parties[j].electorsAmount += dstArr[i]->getRank();
				break;
			}
		}
		cout << endl;
	}

	winningPartyIdx = getIndexOfWinningParty(electors_for_parties, num_of_parties);
	winningPartyElectorsAmount = electors_for_parties[winningPartyIdx].electorsAmount;
	winningParty = electors_for_parties[winningPartyIdx].party;
	delete[] electors_for_parties;
	return winningParty;
}

int DistrictList::getIndexOfWinningParty(ElectorsForParty* elecForParty, const int& num_of_parties) {
	int i, maxElectors = 0, keepMaxPartyIndex = 0;
	ElectorsForParty cur;
	for (i = 0; i < num_of_parties; i++) {
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