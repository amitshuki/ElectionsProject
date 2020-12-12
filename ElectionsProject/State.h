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
		District* dst = distList.addDistrictToList(districtName, rank);
		if (dst == nullptr)
			return false;
		return partyList.addDistrictToParties(dst->getSN(), dst->getRank());
	}
	bool addCitizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {
		if (!distList.checkExistingDistrictBySN(districtSN)) {
			cout << "Incorrect district SN." << endl;
			return false;
		}
		else
			return votersBook.addCitizenToList(new Citizen(name, id, birthYear, districtSN));
	}
	bool addParty(const myString& partyName, const int& candidateId) {
		Citizen* candidate = votersBook.getCitizenByID(candidateId);
		if (!candidate) {
			cout << "Candidate does not exist in state." << endl;
			return false;
		}
		else
			return partyList.addPartyToList(partyName, candidate);
	}
	bool addCitizenAsPartyRepInDist(const int& repID, const int& partySN, const int& districtSN) {
		Citizen* rep = votersBook.getCitizenByID(repID);
		Party* prt = partyList.getPartyBySN(partySN);
		District* dst = distList.getDistrictBySN(districtSN);
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

	void vote(int  id, int  partySN)
	{
		if (checkExistingCitizenbyID(id) && checkExistingPartyBySN(partySN))
		{
			Citizen* a = votersBook.getCitizenByID(id);

			if (a->hasVoted()) {
				cout << "Alredy vote!" << endl;
			}
			else
			{
				a->vote(partySN);
				cout << "We recorded the vote" << endl;

			}

		}


	}
	VotingResults& calcResults() 
	{

		VotersForParty* resArr = new VotersForParty[partyList.getLogsize()];
		VotersForParty




	}

};

