#pragma once
#include "DistrictRepsList.h"
#include "Citizen.h"
#include "myString.h"

class Party
{
private:
	myString name;
	int partySN;
	const Citizen* candidate;
	int candidateID;
	DistrictRepsList drList;
	RoundMode round_mode;
	Party() :name(), partySN(-1), candidate(candidate), candidateID(-1), drList(RoundMode::REGULAR), round_mode(RoundMode::REGULAR) {}
public:
	Party(const myString& newName, const int& sn, const Citizen* candidate, const RoundMode& rm):
		name(newName), partySN(sn), candidate(candidate), drList(rm), round_mode(rm) {
		candidateID = candidate->getId();
	}
	Party(istream& in);
	const int& getSN()const { return partySN; }
	const myString& getName()const { return name; }
	const Citizen* getCandidate()const { return candidate; }


	void addDistrict(const int& dstSN, const int& dstRank);
	void addCitizenAsRep(Citizen* rep, const int& dstSN = 0);


	void printResults(const int& districtSN, const int& electorsAmount)const;
	Party& operator=(const Party& other);
	friend ostream& operator<<(ostream& out, const Party& prty);
	void save(ostream& out) const;
	void load(istream& in);
	
	void connectPartyreps2Citizens(CitizenList& citList);
};

