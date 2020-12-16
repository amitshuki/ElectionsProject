#pragma once
#include "DistrictList.h"
#include "District.h"
#include "Citizen.h"
#include "CitizenList.h"
#include "Party.h"
#include "PartyList.h"
#include "VotingResults.h"
#include "myString.h"
using namespace myStr;
using namespace std;


class State
{
private:
	CitizenList votersBook;
	DistrictList distList;
	PartyList partyList;
public:
	State() {
		srand(time(0));
	}
	~State() {
		votersBook.setDeleteOpt(CitizenList::deleteOption::DELETE_ALL);
	}


	bool addDistrict(const myString& districtName, const int& rank) {
		District* dst = distList.addDistrictToList(districtName, rank);// Add the district to the state's list.
		if (dst == nullptr)
			return false;
		for (int i = 0; i < partyList.getLogSize(); i++)
			if (!dst->addPartyToDistrict(partyList[i]->getSN()))// Add all the parties to the new district's voting list
				return false;
		return partyList.addDistrictToParties(dst->getSN(), dst->getRank());// Add the District to the parties list.
	}
	bool addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {
		return votersBook.addCitizenToList(new Citizen(name, id, birthYear, districtSN)) &&// Add citizen to voters book
			distList.getDistrictBySN(districtSN)->addCitizenToDistrict();// Add a citizen to the district's counter
	}
	bool addParty(const myString& partyName, const int& candidateId) {
		Citizen* const candidate = votersBook.getCitizenByID(candidateId);
		Party* newParty;
		if (!candidate) {
			cout << "Candidate does not exist in state." << endl;
			return false;
		}
		else{
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
	bool addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN) {
		Citizen* const rep = votersBook.getCitizenByID(repID);
		Party* const prt = partyList.getPartyBySN(partySN);
		District* const dst = distList.getDistrictBySN(districtSN);
		if (!rep)
			cout << "Citizen does not exist in state." << endl;
		else if (!prt)
			cout << "Party does not exist in state." << endl;
		else if (!dst)
			cout << "District does not exist in state." << endl;
		else
			return prt->addCitizenAsRep(rep, dst->getSN());
		return false;
	}

	void showVotersBook()const {
		cout << "Voters Book:" << endl;
		cout << "===========" << endl;
		cout << votersBook;
	}
	void showDistrict()const {
		cout << "Districts:" << endl;
		cout << "=========" << endl;
		cout << distList;
	}
	void showParties()const {
		cout << "Parties:" << endl;
		cout << "=======" << endl;
		cout << partyList;
	}

	bool checkExistingCitizenbyID(const int& id) const { return votersBook.checkExistingCitizenInListByID(id); }
	bool checkExistingDistrictBySN(const int& sn)const { return distList.checkExistingDistrictBySN(sn); }
	bool checkExistingPartyBySN(const int& sn)const { return partyList.checkExistingPartyBySN(sn); }

	bool vote(const int& id, const int& partySN){
		Citizen* const cit = votersBook.getCitizenByID(id);
		if (!cit->hasVoted())
			cit->vote(partySN);
		else 
			return false;
		// Add vote to the party in the district of the citizen.
		if (!distList.getDistrictBySN(cit->getDistrictSN())->addVoteToParty(partySN))
			return false;
		return true;
	}

	void showElectionsResults() { 
		int winningPartyElectorsAmount;
		Party* winningParty = distList.getResults(winningPartyElectorsAmount, partyList);
		cout << "The winner of the elections, with "<< winningPartyElectorsAmount<<" electors is: " << endl;
		cout << *(winningParty->getCandidate()) << endl;
	}

};

