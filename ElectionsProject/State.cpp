#include "State.h"


bool State::addDistrict(const myString& districtName, const int& rank) {
	District* dst = distList.addDistrictToList(districtName, rank);// Add the district to the state's list.
	if (dst == nullptr)
		return false;
	for (int i = 0; i < partyList.getLogSize(); i++)
		if (!dst->addPartyToDistrict(partyList[i]->getSN()))// Add all the parties to the new district's voting list
			return false;
	return partyList.addDistrictToParties(dst->getSN(), dst->getRank());// Add the District to the parties list.
}
bool State::addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {
	District* dst = this->distList.getDistrictBySN(districtSN);
	return votersBook.addCitizenToList(new Citizen(name, id, birthYear, districtSN, dst)) &&// Add citizen to voters book
		dst->addCitizenToDistrict();// Add a citizen to the district's counter
}
bool State::addParty(const myString& partyName, const int& candidateId) {
	Citizen* const candidate = votersBook.getCitizenByID(candidateId);
	Party* newParty;
	if (!candidate) {
		//cout << "Candidate does not exist in state." << endl;
		return false;
	}
	else {
		// Add the party to the state's list
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
bool State::addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN) {
	Citizen* const rep = votersBook.getCitizenByID(repID);
	Party* const prt = partyList.getPartyBySN(partySN);
	District* const dst = distList.getDistrictBySN(districtSN);
	if (rep && prt && dst)
		return prt->addCitizenAsRep(rep, dst->getSN());
	return false;
}

void State::showVotersBook()const {
	cout << "Voters Book:" << endl;
	cout << "===========" << endl;
	cout << votersBook;
}
void State::showDistrict()const {
	cout << "Districts:" << endl;
	cout << "=========" << endl;
	cout << distList;
}
void State::showParties()const {
	cout << "Parties:" << endl;
	cout << "=======" << endl;
	cout << partyList;
}

bool State::vote(const int& id, const int& partySN) {
	Citizen* cit = votersBook.getCitizenByID(id);
	if (!cit->hasVoted())
		cit->vote(partySN);
	else
		return false;

	// Add vote to the party in the district of the citizen.
	District* dst = cit->getDistrict();
	if(!dst->addVoteToParty(partySN))
		return false;
	return true;
}

void State::showElectionsResults() {
	int winningPartyElectorsAmount;
	Party* winningParty = distList.getResults(winningPartyElectorsAmount, partyList);
	cout << "The winner of the elections, with " << winningPartyElectorsAmount << " electors is: " << endl;
	cout << *(winningParty->getCandidate()) << endl;
}