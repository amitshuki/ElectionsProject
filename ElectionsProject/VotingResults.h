#pragma once
#include "PartyList.h"
#include "VotingResultsPerParty.h"
class VotingResults// This table is created for every district in state.
{
private:
	int electors;// Amount of electors in District.
	const Citizen* electedCandidate;// Holds a pointer to the elected candidate

	int numOfParties;// Num of parties in state
	VotingResultsPerParty* vrppArr;// Holds the representatives list for each party.
public:
	VotingResults() :electors(0), electedCandidate(nullptr), numOfParties(-1), vrppArr(nullptr) {}
	VotingResults(const int& electors, const PartyList& partyList) {
		this->electors = electors;
		this->numOfParties = partyList.getLogSize();
		electedCandidate = nullptr;
		vrppArr = new VotingResultsPerParty[numOfParties];
		for (int i = 0; i < partyList.getLogSize(); i++)
			vrppArr[i].setParty(partyList.getPartyByIndex(i));
	}
	VotingResults(const VotingResults& other) {
		electors = other.electors;
		electedCandidate = other.electedCandidate;
		numOfParties = other.numOfParties;
		vrppArr = new VotingResultsPerParty[numOfParties];
		for (int i = 0; i < numOfParties; i++)
			vrppArr[i] = other.vrppArr[i];
	}
	~VotingResults() {
		delete[] vrppArr;
	}

	

	bool setElectedCandidate(const Citizen* candidateElect) { return this->electedCandidate = candidateElect; }


	const int& getElectorsAmount()const { return electors; }
	const Citizen* const getElectedCandidate()const { return electedCandidate; }
	CitizenList& getElectedRepsListByParty(const int& partySN, const int& idx = -1) {
		if (idx >= 0 && idx < numOfParties)
			return vrppArr[idx].getRepsList();

		for (int i = 0; i < numOfParties; i++)
			if (partySN == vrppArr[i].getParty()->getSN())
				return vrppArr[i].getRepsList();
	}

	VotingResults& operator=(const VotingResults& other) {
		VotingResultsPerParty* newvrppArr = new VotingResultsPerParty[other.numOfParties];
		for (int i = 0; i < other.numOfParties; i++)
			newvrppArr[i] = other.vrppArr[i];
		delete[] vrppArr;
		vrppArr = newvrppArr;
		this->numOfParties = other.numOfParties;
		this->electors = other.electors;
		this->electedCandidate = other.electedCandidate;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const VotingResults& vr) {
		out << "The voted candidate by this district is: " << endl;
		out << *(vr.electedCandidate) << endl << endl;
		out << "Voted representatives by this district from each party:" << endl << endl;
		for (int i = 0; i < vr.numOfParties; i++)
			out << vr.vrppArr[i] << endl;

		
		return out;
	}
};

