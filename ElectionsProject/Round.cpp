#include "Round.h"

bool Round::addParty(const myString& partyName, const int& candidateId) {
	Citizen* const candidate = votersBook.getCitizenByID(candidateId);
	Party* newParty;
	if (!candidate) {
		//cout << "Candidate does not exist in Round." << endl;
		return false;
	}
	else {
		// Add the party to the Round's list
		newParty = partyList.addPartyToList(partyName, candidate);
		if (newParty != nullptr)
			for (int i = 0; i < distList.getLogSize(); i++) {
				//add all of the districts to the new party
				if (!newParty->addDistrict(distList[i]->getSN(), distList[i]->getRank()))
					return false;
				// add the new party to all of the districts
				if (!distList[i]->addPartyToDistrict(newParty->getSN()))
					return false;
			}
	}
	return true;
}


void Round::showVotersBook()const {
	cout << "Voters Book:" << endl;
	cout << "===========" << endl;
	cout << votersBook;
}

void Round::showParties()const {
	cout << "Parties:" << endl;
	cout << "=======" << endl;
	cout << partyList;
}

bool Round::vote(const int& id, const int& partySN) {
	Citizen* cit = votersBook.getCitizenByID(id);
	if (!cit->hasVoted()) {
		hasAny1votedyet = true;
		cit->vote(partySN);
	}

	// Add vote to the party in the district of the citizen.
	District* dst = cit->getDistrict();
	if (!dst->addVoteToParty(partySN))
		return false;
	return true;
}

void Round::showElectionsResults() {
	if (this->hasAny1votedyet == false)
		return;
	int winningPartyElectorsAmount;// getResults updates it byRef
	Party* winningParty = distList.getResults(winningPartyElectorsAmount, partyList);
	cout << "The winner of the elections, with " << winningPartyElectorsAmount << " electors is: " << endl;
	cout << *(winningParty->getCandidate()) << endl;
}