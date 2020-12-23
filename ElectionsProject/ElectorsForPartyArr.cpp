#include "ElectorsForPartyArr.h"


ElectorsForPartyArr::ElectorsForPartyArr(const int& size) {
	arr = new ElectorsForParty[size];
	this->size = size;
}
ElectorsForPartyArr::ElectorsForPartyArr(PartyList& partyList) {
	size = partyList.getLogSize();
	arr = new ElectorsForParty[size];
	for (int i = 0; i < size; i++) {
		arr[i].party = partyList[i];
		arr[i].electorsAmount = arr[i].precentage = arr[i].votesForParty = 0;
	}
}
ElectorsForPartyArr& ElectorsForPartyArr::operator+=(const ElectorsForPartyArr& other) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < other.size; j++)
			if (this->arr[i].party->getSN() == other.arr[j].party->getSN()) {
				this->arr[i].electorsAmount += other.arr[j].electorsAmount;
				this->arr[i].votesForParty += other.arr[j].votesForParty;
				//Need to update percentage! somehow
				break;
			}
	}
	return *this;
}
ElectorsForParty& ElectorsForPartyArr::operator[](const int& idx) {
	if (idx < 0 || idx >= size)
		throw "Index not int range.";
	return arr[idx];
}
ElectorsForPartyArr& ElectorsForPartyArr::operator=(const ElectorsForPartyArr& other) {
	if (this != &other) {
		delete[] this->arr;
		this->arr = new ElectorsForParty[other.size];
		for (int i = 0; i < other.size; i++)
			this->arr[i] = other.arr[i];
		this->size = other.size;
	}
	return *this;
}
