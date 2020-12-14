#pragma once
#include "PartyList.h"
#include "VotingResults.h"
#include "VotersForPartyList.h"
#include "myString.h"
using namespace myStr;

class District
{
private:
	int SN, totalCivils, totalVoters, rank; /* total voters - filled only when  round is initiated (init -1)
													  rank - given randomly */
	myString name;
	VotersForPartyList vfpList;// Contains a list of all the parties (serial nums) and how many voted for them in the district.
public:
	District(){
		totalCivils = totalVoters = 0;
		SN = rank = -1;
		name = "";
	}
	District(const myString& newName,const int& newRank,const int& sn){
		SN = sn;
		totalVoters = totalCivils = 0;
		rank = newRank;
		name = newName;
	}

	~District(){
		//Add voters for party
	}

	const int& getSN()const { return SN; }
	const int& getRank()const { return rank; }
	const int& getTotalCivils()const { return totalCivils; }
	const int& getTotalVoters()const { return totalVoters; }

	bool addCitizenToDistrict() { return ++totalCivils; }

	bool addVoteToParty(const int& partySN) {
		// Recieve the voters for party table and add a vote to the party in the current district
		if (!vfpList.getVFPByPartySN(partySN).addVote())
			return false;
		totalVoters++;
		return true;
	}
	bool addPartyToDistrict(const int& partySN) { return vfpList.addParty(partySN); }

	VotingResults& getVotingResults(const PartyList& partyList){
		int i, numOfElectors, maxNumOfElectors = 0, votedCandidateIndex;
		VotingResults* vr = new VotingResults(this->rank, partyList);
		Party* curParty;

		for (votedCandidateIndex = i = 0; i < partyList.getLogSize(); i++) {

			curParty = partyList.getPartyByIndex(i);
			numOfElectors =
				vfpList.getVFPByPartySN(curParty->getSN()).calcNumOfElectors(totalVoters, rank);

			// Add the reps from EACH party according to num of Electors.
			vr->getElectedRepsListByParty(curParty->getSN(), i) =
				curParty->getSubRepsListInDistrict(this->SN, numOfElectors);

			if (numOfElectors > maxNumOfElectors) {
				votedCandidateIndex = i;
				maxNumOfElectors = numOfElectors;
				vr->setElectedCandidate(curParty->getCandidate());
			}
			else if (numOfElectors == maxNumOfElectors) {// If tie -> take the party with the smallest SN.
				if (curParty->getSN() < partyList.getPartyByIndex(votedCandidateIndex)->getSN()) {
					votedCandidateIndex = i;
					vr->setElectedCandidate(curParty->getCandidate());
				}
			}// else if
		}//for
		return *vr;
	}//getVotingResults

	friend ostream& operator<<(ostream& out, const District& dst) {
		out << "District Serial Number: " << dst.SN << ", ";
		out << "Name: " << dst.name << ", ";
		out << "Number of electors: " << dst.rank;
		return out;
	}
};

