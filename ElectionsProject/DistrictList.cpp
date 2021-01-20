#include "DistrictList.h"

DistrictList::~DistrictList() {
	for (auto& i : dstArr)
		delete i;
}

// Adds a district and returns a pointer to it.
District* DistrictList::addDistrictToList(const myString& dstName, const int& rank, const DistrictType& dt) {
	int logSize = dstArr.getLogSize();
	if (dt == DistrictType::DIVIDED)
		dstArr.push_back(new DividedDistrict(dstName, rank, logSize + 1));
	else
		dstArr.push_back(new UnifiedDistrict(dstName, rank, logSize + 1));

	return dstArr.back();
}
bool DistrictList::checkExistingDistrictBySN(const int& sn)const {
	for (auto& i : dstArr)
		if (i->districtSN == sn)
			return true;
	return false;
}
District* DistrictList::getDistrictBySN(const int& sn)const {
	for (auto& i : dstArr)
		if (i->districtSN == sn)
			return i;
	return nullptr;
}

DistrictList& DistrictList::operator=(const DistrictList& other) {
	if (this != &other) 
		dstArr = other.dstArr;
	return *this;
}
ostream& operator<<(ostream& out, const DistrictList& dstList) {
	for (auto& i : dstList.dstArr)
		out << *i << endl;
	return out;
}


const Party* DistrictList::getResults(int& winningPartyElectorsAmount, PartyList& partyList) {
	int i, winningPartyIdx;
	const Party* winningParty;
	
	// An array ordered same as partyList - counts for each party electors amount
	ElectorsForPartyArr elects_for_parties(partyList);
	ElectorsForPartyArr temp;

	for (auto& i : dstArr) {
		temp = i->getVotingresults(partyList);//Add the current district result to the overall results.
		elects_for_parties += temp;
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
	out.write(rcastcc(&dstArr.getLogSize()), sizeof(dstArr.getLogSize()));
	for (auto& i : dstArr) {
		if (!DistrictLoader::save(out, *i))
			return false;
	}
	return out.good();
}
bool DistrictList::load(istream& in) {
	int size;
	in.read(rcastc(&size), sizeof(size));
	DynamicArray<District*> newDstArr(size);
	for (auto i = 0; i < size;i++) {
		newDstArr.push_back(DistrictLoader::load(in));
		if (!in.good())
			break;
	}
	dstArr = newDstArr;
	return in.good();
}