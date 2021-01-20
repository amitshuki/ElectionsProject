#include "ElectorsForPartyArr.h"

ElectorsForPartyArr::ElectorsForPartyArr(PartyList& partyList) :arr1(partyList.getLogSize()) {
	int size1 = partyList.getLogSize();
	ElectorsForParty efp;
	for (int i = 0; i < size1; i++) {
		efp = ElectorsForParty(partyList[i]);
		arr1.push_back(efp);
	}
}
ElectorsForPartyArr& ElectorsForPartyArr::operator+=(const ElectorsForPartyArr& other) {
	for (int i = 0; i < arr1.getLogSize(); i++) {
		for (int j = 0; j < other.getSize(); j++)
			if (arr1[i].party->getSN() == other.arr1[j].party->getSN()) {
				arr1[i].electorsAmount += other.arr1[j].electorsAmount;
				arr1[i].votesForParty += other.arr1[j].votesForParty;
				//Need to update percentage! somehow
				break;
			}
	}
	return *this;
}
ElectorsForPartyArr& ElectorsForPartyArr::operator=(const ElectorsForPartyArr& other) {
	if (this != &other) 
		this->arr1 = other.arr1;
	return *this;
}
