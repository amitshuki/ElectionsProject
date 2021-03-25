#pragma once
#include "DistrictLoader.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
#include "ElectorsForPartyArr.h"

#include "DynamicArray.h"

class DistrictList
{
private:
	DynamicArray<District*> dstArr;
public:
	DistrictList() = default;
	DistrictList(const DistrictList& other) { this->dstArr = other.dstArr; }
	DistrictList(istream& in) { load(in); }
	~DistrictList();
	// Adds a district and returns a pointer to it.
	District* addDistrictToList(const string& dstName, const int& rank,const DistrictType& dt);

	bool checkExistingDistrictBySN(const int& sn)const;
	District* getDistrictBySN(const int& sn)const;
	const int& getLogSize()const { return dstArr.getLogSize(); }

	District* operator[](const int& idx)const { return dstArr[idx]; }
	DistrictList& operator=(const DistrictList& other);
	friend ostream& operator<<(ostream& out, const DistrictList& dstList);

	const Party* getResults(int& winningPartyElectorsAmount, PartyList& partyList);

private:
	int getIndexOfWinningParty(ElectorsForPartyArr& elecForParty);

public:
	void save(ostream& out) const;
	void load(istream& in);
};

