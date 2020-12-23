#include "Citizen.h"
using namespace std;

Citizen::Citizen(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* mdst, const RoundMode& rm) {
	this->name = name;
	this->id = id;
	this->birthYear = birthYear;
	this->districtSN = districtSN;
	this->votedPartySN = -1;
	this->didVote = false;
	this->dst = mdst;
	round_mode = rm;
}


void Citizen::vote(const int& partySN) {
	this->votedPartySN = partySN;
	this->didVote = true;
}
ostream& operator<<(ostream& out, const Citizen& cit) {
	out << "Name: " << cit.name << ", ";
	out << "ID: " << cit.id << ", ";
	out << "Birth year: " << cit.birthYear;
	if (cit.round_mode == RoundMode::REGULAR)
		out << ", District serial no.: " << cit.districtSN;
	return out;
}
