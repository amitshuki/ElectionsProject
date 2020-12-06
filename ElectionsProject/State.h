#pragma once
#include <string>
#include "District.h"
#include "Citizen.h"
#include "Party.h"
#include "VotingResults.h"
using namespace std;
class State
{
private:
	Citizen* citizenArr;
	District* districtArr;
	Party* partiesArr;
public:
	State();
	~State();
	void addDistrict(const string& districtName,int rank);
	void addCitizen(string name, int id, Date dob, int districtSN);
	void addParty(string partyName, int candidateId);
	void addCitizenAsPartyRep(int id, int partySN, int districtSN);
	void printDistricts();
	void printCitizens();
	void printParties();
	void vote(int id, int partySN);
	VotingResults& calcResults();
};

