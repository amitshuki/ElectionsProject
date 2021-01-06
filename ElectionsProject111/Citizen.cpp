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
Citizen::Citizen(istream& in) :name(in) { 
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&districtSN), sizeof(districtSN));
	in.read(rcastc(&birthYear), sizeof(birthYear));
	dst = nullptr;// The loading state needs to connect between the citizens and Districts.
	in.read(rcastc(&votedPartySN), sizeof(votedPartySN));
	in.read(rcastc(&didVote), sizeof(didVote));
	in.read(rcastc(&round_mode), sizeof(round_mode));
}

void Citizen::vote(const int& partySN) {
	this->votedPartySN = partySN;
	this->didVote = true;
}
Citizen& Citizen::operator=(const Citizen& other) {
	if (this != &other) {
		id = other.id;
		districtSN = other.districtSN;
		birthYear = other.birthYear;
		dst = other.dst;
		name = other.name;
		votedPartySN = other.votedPartySN;
		didVote = other.didVote;
		round_mode = other.round_mode;
	}
	return *this;
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
	name.save(out);
	out.write(rcastcc(&id), sizeof(this->id));
	out.write(rcastcc(&districtSN), sizeof(this->districtSN));
	out.write(rcastcc(&birthYear), sizeof(this->birthYear));
	out.write(rcastcc(&votedPartySN), sizeof(this->votedPartySN));
	out.write(rcastcc(&didVote), sizeof(this->didVote));
	out.write(rcastcc(&round_mode), sizeof(this->round_mode));
	return out.good();
}
bool Citizen::load(istream& in) {
	name.load(in);
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&districtSN), sizeof(districtSN));
	in.read(rcastc(&birthYear), sizeof(birthYear));
	dst = nullptr;// The loading state needs to connect between the citizens and Districts.
	in.read(rcastc(&votedPartySN), sizeof(votedPartySN));
	in.read(rcastc(&didVote), sizeof(didVote));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	return in.good();
}