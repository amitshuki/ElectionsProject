#pragma once
#include "DistrictLoader.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
#include "ElectorsForPartyArr.h"
#include "myString.h"
using namespace myStr;


class DistrictList
{
private:
	District** dstArr;
	int logSize, capacity;
	void resizeArr();
public:
	DistrictList() :dstArr(nullptr), logSize(0), capacity(0) {}
	DistrictList(istream& in) :dstArr(nullptr), logSize(0), capacity(0) { load(in); }
	~DistrictList();
	// Adds a district and returns a pointer to it.
	
	District* const addDistrictToList(const myString& dstName, const int& rank,const DistrictType& dt);
	bool checkExistingDistrictBySN(const int& sn)const;
	District* getDistrictBySN(const int& sn)const;
	const int& getLogSize()const { return logSize; }




	District* const operator[](const int& idx);
	DistrictList& operator=(const DistrictList& other);
	friend ostream& operator<<(ostream& out, const DistrictList& dstList);
	

	Party* getResults(int& winningPartyElectorsAmount, PartyList& partyList);
	int getIndexOfWinningParty(ElectorsForPartyArr& elecForParty);

	bool save(ostream& out) const;
	bool load(istream& in);
};
