#include "Citizen.h"
using namespace std;

Citizen::Citizen(const string& name, const int& id, const int& birthYear, const int& districtSN, District* mdst, const RoundMode& rm) {
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

void Citizen::save(ostream& out) const {
	size_t size = name.size();
	out.write(rcastcc(&size), sizeof(size));
	out.write(rcastcc(&name[0]), size);
	out.write(rcastcc(&id), sizeof(this->id));
	out.write(rcastcc(&districtSN), sizeof(this->districtSN));
	out.write(rcastcc(&birthYear), sizeof(this->birthYear));
	out.write(rcastcc(&votedPartySN), sizeof(this->votedPartySN));
	out.write(rcastcc(&didVote), sizeof(this->didVote));
	out.write(rcastcc(&round_mode), sizeof(this->round_mode));
	if (!out.good())
		throw outfile_error("Citizen");
}
void Citizen::load(istream& in) {
	Citizen cit;
	size_t size;
	in.read(rcastc(&size), sizeof(size));
	cit.name.resize(size);
	in.read(rcastc(&cit.name[0]), size);
	in.read(rcastc(&cit.id), sizeof(id));
	in.read(rcastc(&cit.districtSN), sizeof(cit.districtSN));
	in.read(rcastc(&cit.birthYear), sizeof(cit.birthYear));
	cit.dst = nullptr;// The loading state needs to connect between the citizens and Districts.
	in.read(rcastc(&cit.votedPartySN), sizeof(cit.votedPartySN));
	in.read(rcastc(&cit.didVote), sizeof(cit.didVote));
	in.read(rcastc(&cit.round_mode), sizeof(cit.round_mode));
	if (!in.good())
		throw infile_error("Citizen");
	*this = cit;
}