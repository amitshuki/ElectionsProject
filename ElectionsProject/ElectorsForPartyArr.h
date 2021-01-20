#pragma once
#include "Party.h"
#include "PartyList.h"
#include <array>

struct ElectorsForParty {
	int electorsAmount;
	int votesForParty;
	float precentage;
	const Party* party;
	ElectorsForParty():electorsAmount(0),votesForParty(0),precentage(0.0),party(nullptr){}
	ElectorsForParty(const Party* prt) :electorsAmount(0), votesForParty(0), precentage(0.0), party(prt) {}

};

class ElectorsForPartyArr
{
private:
	DynamicArray<ElectorsForParty> arr1;
	/*ElectorsForParty* arr;
	int size;*/
public:
	ElectorsForPartyArr() /*:arr(nullptr), size(0)*/ = default;
	ElectorsForPartyArr(const int& size) :arr1(size) {}
	ElectorsForPartyArr(PartyList& partyList);
	ElectorsForPartyArr(const ElectorsForPartyArr& efpa) :arr1(efpa.arr1) {}
	~ElectorsForPartyArr() { /*delete[] arr;*/ }

	void push_back(const ElectorsForParty& efp) { arr1.push_back(efp); }
	const int& getSize()const { return arr1.getLogSize(); }

	ElectorsForPartyArr& operator+=(const ElectorsForPartyArr& other);
	ElectorsForParty& operator[](const int& idx) { return arr1[idx]; }
	ElectorsForPartyArr& operator=(const ElectorsForPartyArr& other);
};

