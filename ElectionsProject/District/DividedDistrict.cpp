#include "DividedDistrict.h"

void DividedDistrict::printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties) const{
	int i, curElectors;
	const Party* curParty;
	cout << "Voting results for " << *this << endl;
	//quickSort(electors_for_parties, 0, electors_for_parties.getSize() - 1);// Sort the array
	for (i = electors_for_parties.getSize() - 1; i >= 0; i--) {
		if (electors_for_parties[i].electorsAmount > 0) {
			cout << "This district grants " << electors_for_parties[i].electorsAmount;
			cout << " electors to: " << *(electors_for_parties[i].party->getCandidate()) << endl;
		}
	}
	cout << "===============================================================" << endl;

	for (i = electors_for_parties.getSize() - 1; i >= 0; i--) {
		curParty = electors_for_parties[i].party;
		curElectors = electors_for_parties[i].electorsAmount;
		curParty->printResults(this->districtSN, curElectors);
	}
}

ElectorsForPartyArr& DividedDistrict::getVotingresults(PartyList& partyList) {
	int i, cur_voters_amount, cur_party_sn;
	float cur_percentage;
	const int num_of_parties = partyList.getLogSize();

	// An array ordered same as partyList - counts for each party electors amount
	ElectorsForPartyArr* electors_for_parties = new ElectorsForPartyArr(partyList);
	if (!electors_for_parties)
		throw bad_alloc();
	if (totalVoters == 0)
		throw exception("Division by zero");

	// Calculate Electors for each party
	for (i = 0; i < num_of_parties; i++) {
		cur_party_sn = (*electors_for_parties)[i].party->getSN();
		cur_voters_amount = voters4PartyList.getAmountOfVotersByPartySN(cur_party_sn);

		(*electors_for_parties)[i].electorsAmount = calcElectors(cur_voters_amount);// Calculate amount of electors
		(*electors_for_parties)[i].votesForParty = cur_voters_amount;// Insert voters amount
		cur_percentage = static_cast<float>(cur_voters_amount) / static_cast<float>(totalVoters) * 100;
		(*electors_for_parties)[i].precentage = round(cur_percentage);
	}

	
	printResults(-1, *electors_for_parties);

	return *electors_for_parties;
}
