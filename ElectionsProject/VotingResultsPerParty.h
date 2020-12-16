#pragma once
#include "Party.h"
class VotingResultsPerParty
	// This class is used by each district in order to organize the elected candidates with the party they represent.
{
private:
	const Party* party;
	CitizenList repsList;	
public:
	VotingResultsPerParty():party(nullptr){}
	VotingResultsPerParty(Party* party):party(party){}
	VotingResultsPerParty(const VotingResultsPerParty& other) {
		this->party = party;
		repsList = other.repsList;
	}

	bool setParty(const Party* party) { return this->party = party; }

	CitizenList& getRepsList() { return repsList; }
	const Party* getParty() { return party; }

	VotingResultsPerParty& operator=(const VotingResultsPerParty& other) {
		this->party = party;
		repsList = other.repsList;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const VotingResultsPerParty& vrpp) {
		if (vrpp.repsList.getLogSize() > 0) {
			out << "\tParty Serial number: " << vrpp.party->getSN() << ", ";
			out << "Party Name: " << vrpp.party->getName() << endl;
			out << "\t\t||Elected Representatives:||" << endl;
			out << vrpp.repsList;
			//out << "=============================================================" << endl;
		}
		return out;
	}
};

