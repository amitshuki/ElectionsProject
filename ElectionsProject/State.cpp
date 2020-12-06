#include "State.h"
State::State() {
	citizenArr = nullptr;
	districtArr = nullptr;
	partiesArr = nullptr;
}
State::~State() {
	delete[] citizenArr;
	delete[] districtArr;
	delete[] partiesArr;
}
void State::addDistrict(const string& districtName, int electorsAmount) {

}
/*
void State::addCitizen(string name, int id, Date dob, int districtSN);
void State::addParty(string partyName, int candidateId);
void State::addCitizenAsPartyRep(int id, int partySN, int districtSN);
void State::printDistricts();
void State::printCitizens();
void State::printParties();
void State::vote(int id, int partySN);
VotingResults& State::calcResults();
*/