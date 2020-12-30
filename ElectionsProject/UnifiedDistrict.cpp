#include "UnifiedDistrict.h"

void UnifiedDistrict::printResults(const int& winningPartyIdx, ElectorsForPartyArr& electors_for_parties) {
	int i, curElectors;
	Party* curParty;
	cout << "Voting results for " << *this << endl;
	cout << "The winner for this District, with " << electors_for_parties[winningPartyIdx].electorsAmount;
	cout << " electors and " << electors_for_parties[winningPartyIdx].votesForParty;
	cout << " votes, which are " << electors_for_parties[winningPartyIdx].precentage << "% of the total votes is:" << endl;
	cout << *(electors_for_parties[winningPartyIdx].party->getCandidate()) << endl;
	cout << "===============================================================" << endl;

	for (i = 0; i < electors_for_parties.getSize(); i++) {
		curParty = electors_for_parties[i].party;
		curElectors = electors_for_parties[i].electorsAmount;
		curParty->printResults(this->districtSN, curElectors);
	}
}
ElectorsForPartyArr& UnifiedDistrict::getVotingresults(PartyList& partyList) {
	int i, cur_voters_amount, cur_party_sn, winningPartyIdx;
	float cur_percentage;
	const int num_of_parties = partyList.getLogSize();

	//This is the returned result: size = 1 because it is a unified district
	ElectorsForPartyArr* districtResults = new ElectorsForPartyArr(1);

	// An array ordered same as partyList - counts for each party electors amount
	ElectorsForPartyArr electors_for_parties(partyList);
	
	// Calculate Electors for each party
	for (i = 0; i < num_of_parties; i++) {
		cur_party_sn = electors_for_parties[i].party->getSN();
		cur_voters_amount = voters4PartyList.getAmountOfVotersByPartySN(cur_party_sn);
		electors_for_parties[i].electorsAmount = calcElectors(cur_voters_amount);
		electors_for_parties[i].votesForParty = cur_voters_amount;
		cur_percentage = static_cast<float>(cur_voters_amount) / static_cast<float>(totalVoters) * 100;
		electors_for_parties[i].precentage = round(cur_percentage);
	}

	winningPartyIdx = getWinningPartyIdx(electors_for_parties);
	printResults(winningPartyIdx, electors_for_parties);

	electors_for_parties[winningPartyIdx].electorsAmount = this->rank;//The winning party gets all the electors - Unified District

	(*districtResults)[0] = electors_for_parties[winningPartyIdx];
	return *districtResults;
}

bool UnifiedDistrict::save(ostream& out) const {
	District::save(out);
	return out.good();
}
bool UnifiedDistrict::load(istream& in) {
	return true;
}