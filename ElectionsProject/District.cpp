#include "District.h"

District::District() {
	totalCivils = totalVoters = 0;
	districtSN = rank = -1;
	name = "";
}
District::District(const myString& newName, const int& newRank, const int& sn) {
	districtSN = sn;
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

int District::calcElectors(const int& numOfVoters) {
	if (numOfVoters <= 0)
		return 0;
	float percentage = (numOfVoters * rank);
	float electors = percentage / static_cast<float>(totalVoters);
	return round(electors);
}

int District::getWinningPartyIdx(ElectorsForPartyArr& electors_for_parties) {
	int i, maxElectors = 0, keepMaxPartyIndex = 0;
	ElectorsForParty cur;
	for (i = 0; i < electors_for_parties.getSize(); i++) {
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
ostream& operator<<(ostream& out, const District& dst) {
	out << "District Serial Number: " << dst.districtSN << ", ";
	out << "Name: " << dst.name << ", ";
	out << "Rank: " << dst.rank;
	return out;
}

bool District::save(ostream& out) const {
	out.write(rcastcc(&districtSN), sizeof(districtSN));
	out.write(rcastcc(&totalCivils), sizeof(totalCivils));
	out.write(rcastcc(&totalVoters), sizeof(totalVoters));
	out.write(rcastcc(&rank), sizeof(rank));
	if (!name.save(out))
		return false;
	if (!voters4PartyList.save(out))
		return false;
	return out.good();
}
bool District::load(istream& in) {
	return true;
}