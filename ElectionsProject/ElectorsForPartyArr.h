#pragma once
#include "Party.h"
#include "PartyList.h"

struct ElectorsForParty {
	int electorsAmount = 0;
	int votesForParty = 0;
	float precentage = 0.0;
	Party* party = nullptr;
};

class ElectorsForPartyArr
{
private:
	ElectorsForParty* arr;
	int size;
public:
	ElectorsForPartyArr() :arr(nullptr), size(0) {}
	ElectorsForPartyArr(const int& size);
	ElectorsForPartyArr(PartyList& partyList);
	~ElectorsForPartyArr() { delete[] arr; }

	const int& getSize()const { return size; }

	ElectorsForPartyArr& operator+=(const ElectorsForPartyArr& other);
	ElectorsForParty& operator[](const int& idx);
	ElectorsForPartyArr& operator=(const ElectorsForPartyArr& other);
};

