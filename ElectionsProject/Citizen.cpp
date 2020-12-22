#include "Citizen.h"
using namespace std;

Citizen::Citizen() :id(-1), districtSN(-1), birthYear(-1), name(""), votedPartySN(-1), didVote(false), dst(nullptr) {}
Citizen::Citizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {
	this->name = name;
	this->id = id;
	this->birthYear = birthYear;
	this->districtSN = districtSN;
	this->votedPartySN = -1;
	this->didVote = false;
	this->dst = nullptr;
}
Citizen::Citizen(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* mdst) {
	this->name = name;
	this->id = id;
	this->birthYear = birthYear;
	this->districtSN = districtSN;
	this->votedPartySN = -1;
	this->didVote = false;
	this->dst = mdst;
}


void Citizen::vote(const int& partySN) {
	this->votedPartySN = partySN;
	this->didVote = true;
}
ostream& operator<<(ostream& out, const Citizen& cit) {
	out << "Name: " << cit.name << ", ";
	out << "ID: " << cit.id << ", ";
	out << "Birth year: " << cit.birthYear << ", ";
	out << "District serial no.: " << cit.districtSN;
	return out;
}
