#include "District.h"

District::District() {
	totalCivils = totalVoters = 0;
	SN = rank = -1;
	name = "";
}
District::District(const myString& newName, const int& newRank, const int& sn) {
	SN = sn;
	totalVoters = totalCivils = 0;
	rank = newRank;
	name = newName;
}


bool District::addVoteToParty(const int& partySN) {
	// Recieve the voters for party table and add a vote to the party in the current district
	if (!voters4PartyList.getVFPByPartySN(partySN).addVote())
		return false;
	totalVoters++;
	return true;
}

const int& District::getVotingresults(PartyList& partyList) {
	int i, const num_of_parties = partyList.getLogSize();
	int cur_voters_amount, cur_party_sn;

	int winningPartyIdx;

	// An array ordered same as partyList - counts for each party electors amount
	ElectorsForParty* electors_for_parties = new ElectorsForParty[num_of_parties];
	for (i = 0; i < num_of_parties; i++) {
		electors_for_parties[i].party = partyList[i];
		//cout << i << ". " << *(electors_for_parties[i].party) << endl;
	}
	float cur_percentage;
	// Calculate Electors for each party
	for (i = 0; i < num_of_parties; i++) {
		cur_party_sn = electors_for_parties[i].party->getSN();
		cur_voters_amount = voters4PartyList.getAmountOfVotersByPartySN(cur_party_sn);
		electors_for_parties[i].electorsAmount = calcElectors(cur_voters_amount);
		electors_for_parties[i].votesForParty = cur_voters_amount;
		cur_percentage = static_cast<float>(cur_voters_amount) / static_cast<float>(totalVoters) * 100;
		electors_for_parties[i].precentage = round(cur_percentage);
	}

	winningPartyIdx = getWinningPartyIdx(electors_for_parties, num_of_parties);
	printResults(winningPartyIdx, electors_for_parties, num_of_parties);

	const int& winningPartySN = electors_for_parties[winningPartyIdx].party->getSN();
	delete[] electors_for_parties;
	return winningPartySN;
}


int District::getWinningPartyIdx(ElectorsForParty*& electors_for_parties, const int& num_of_parties) {
	int i, maxElectors = 0, keepMaxPartyIndex = 0;
	Party* winningParty;
	ElectorsForParty cur;
	for (i = 0; i < num_of_parties; i++) {
		cur = electors_for_parties[i];
		if (cur.electorsAmount > maxElectors) {
			maxElectors = cur.electorsAmount;
			keepMaxPartyIndex = i;
		}
		else if (cur.electorsAmount == maxElectors) {// Need to take The party with the smallest SerialNumber
			if (cur.party->getSN() < electors_for_parties[keepMaxPartyIndex].party->getSN())
				keepMaxPartyIndex = i;
		}
	}
	return keepMaxPartyIndex;
}
void District::printResults(const int& winningPartyIdx, ElectorsForParty*& electors_for_parties, const int& num_of_parties) {
	int i, curElectors;
	Party* curParty;
	cout << "Voting results for " << *this << endl;
	cout << "The winner for this District, with " << electors_for_parties[winningPartyIdx].electorsAmount;
	cout << " electors and " << electors_for_parties[winningPartyIdx].votesForParty;
	cout << " votes, which are " << electors_for_parties[winningPartyIdx].precentage << "% of the total votes is:" << endl;
	cout << *(electors_for_parties[winningPartyIdx].party->getCandidate()) << endl;
	cout << "===============================================================" << endl;
	for (i = 0; i < num_of_parties; i++) {
		curParty = electors_for_parties[i].party;
		curElectors = electors_for_parties[i].electorsAmount;
		curParty->printResults(this->SN, curElectors);
	}
}

int District::calcElectors(const int& numOfVoters) {
	if (numOfVoters <= 0)
		return 0;
	float percentage = (numOfVoters * rank);
	float electors = percentage / static_cast<float>(totalVoters);
	return round(electors);
}
ostream& operator<<(ostream& out, const District& dst) {
	out << "District Serial Number: " << dst.SN << ", ";
	out << "Name: " << dst.name << ", ";
	out << "Rank: " << dst.rank;
	return out;
}