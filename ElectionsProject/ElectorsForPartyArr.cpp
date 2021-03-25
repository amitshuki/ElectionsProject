#include "ElectorsForPartyArr.h"

ElectorsForPartyArr::ElectorsForPartyArr(PartyList& partyList) :arr(partyList.getLogSize()) {
	int size1 = partyList.getLogSize();
	ElectorsForParty efp;
	for (int i = 0; i < size1; i++) {
		efp = ElectorsForParty(partyList[i]);
		arr.push_back(efp);
	}
}
ElectorsForPartyArr& ElectorsForPartyArr::operator+=(const ElectorsForPartyArr& other) {
	for (int i = 0; i < arr.getLogSize(); i++) {
		for (int j = 0; j < other.getSize(); j++)
			if (arr[i].party->getSN() == other.arr[j].party->getSN()) {
				arr[i].electorsAmount += other.arr[j].electorsAmount;
				arr[i].votesForParty += other.arr[j].votesForParty;
				//Need to update percentage! somehow
				break;
			}
	}
	return *this;
}
ElectorsForPartyArr& ElectorsForPartyArr::operator=(const ElectorsForPartyArr& other) {
	if (this != &other) 
		this->arr = other.arr;
	return *this;
}
