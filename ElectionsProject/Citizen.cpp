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

bool Citizen::save(ostream& out) const {
	out.write(rcastcc(&id), sizeof(this->id));
	out.write(rcastcc(&districtSN), sizeof(this->districtSN));
	out.write(rcastcc(&birthYear), sizeof(this->birthYear));
	//Write dst! do i need it?
	name.save(out);
	out.write(rcastcc(&votedPartySN), sizeof(this->votedPartySN));
	out.write(rcastcc(&didVote), sizeof(this->didVote));
	out.write(rcastcc(&round_mode), sizeof(this->round_mode));
	return out.good();
}
bool Citizen::load(istream& in) {
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&districtSN), sizeof(districtSN));
	in.read(rcastc(&birthYear), sizeof(birthYear));
	//read dst??
	name.load(in);
	in.read(rcastc(&votedPartySN), sizeof(votedPartySN));
	in.read(rcastc(&didVote), sizeof(didVote));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	return in.good();
}