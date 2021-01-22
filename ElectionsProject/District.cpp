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
void District::addVoteToParty(const int& partySN) {
	// Recieve the voters for party table and add a vote to the party in the current district
	voters4PartyList.getVFPByPartySN(partySN).addVote();
	totalVoters++;
}

int District::calcElectors(const int& numOfVoters) {
	if (this->totalVoters == 0.0)
		throw elections_result_exception("no one has voted yet.");
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

void District::save(ostream& out) const {
	name.save(out);
	voters4PartyList.save(out);
	out.write(rcastcc(&districtSN), sizeof(districtSN));
	out.write(rcastcc(&totalCivils), sizeof(totalCivils));
	out.write(rcastcc(&totalVoters), sizeof(totalVoters));
	out.write(rcastcc(&rank), sizeof(rank));
	if (!out.good())
		throw outfile_error("District");
}
void District::load(istream& in) {
	name.load(in);
	voters4PartyList.load(in);
	in.read(rcastc(&districtSN), sizeof(districtSN));
	in.read(rcastc(&totalCivils), sizeof(totalCivils));
	in.read(rcastc(&totalVoters), sizeof(totalVoters));
	in.read(rcastc(&rank), sizeof(rank));
	if (!in.good())
		throw infile_error("District");
}