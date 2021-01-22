#include "Party.h"
using namespace myStr;
using namespace std;

Party::Party(istream& in) :name(in),drList(in){
	in.read(rcastc(&partySN), sizeof(partySN));
	candidate = nullptr;// see State::connectRepsToCitizens!
	in.read(rcastc(&candidateID), sizeof(candidateID));
	in.read(rcastc(&round_mode), sizeof(round_mode));
}

void Party::addDistrict(const int& dstSN, const int& dstRank) {
	if (round_mode == RoundMode::REGULAR)
		drList.addDistrict(dstSN, dstRank);
	else if (round_mode == RoundMode::SIMPLE) {
		if (drList.getLogSize() == 0) 
			drList.addDistrict(dstSN, dstRank);
		else
			throw exception("Cannot add more districts in simple round.");
	}
	else
		throw adding_error("District", "Party");
}
void Party::addCitizenAsRep(Citizen* rep, const int& dstSN) {
	drList.addCitizenAsRep(rep, dstSN); 
}

void Party::printResults(const int& districtSN, const int& electorsAmount) const{
	cout << "Party Name: " << name << ", Party Serial No.: " << partySN << endl;
	drList.printFirstXReps(districtSN, electorsAmount);
}

Party& Party::operator=(const Party& other) {
	if (this != &other) {
		this->name = other.name;
		this->partySN = other.partySN;
		this->candidate = other.candidate;
		this->candidateID = other.candidateID;
		this->drList = other.drList;
		this->round_mode = other.round_mode;
	}
	return *this;
}

ostream& operator<<(ostream& out, const Party& prty) {
	out << "Party Serial Number: " << prty.partySN<< ", ";
	out << "Name: " << prty.name << endl;
	out << "Candidate: " << *(prty.candidate) << endl;

	if (prty.round_mode == RoundMode::REGULAR)
		out << "Representatives by Districts: " << endl;
	else
		out << "Representatives: " << endl;
	out << "============================" << endl;
	out << prty.drList << endl;
	return out;
}

void Party::save(ostream& out) const {
	name.save(out);
	drList.save(out);
	out.write(rcastcc(&partySN), sizeof(partySN));
	out.write(rcastcc(&candidateID), sizeof(candidateID));// Write only candidate's ID!
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	if (!out.good())
		throw outfile_error("Party");
}
void Party::load(istream& in) {
	Party temp_prt;
	try {
		temp_prt.name.load(in);
		temp_prt.drList.load(in);
		in.read(rcastc(&temp_prt.partySN), sizeof(temp_prt.partySN));
		temp_prt.candidate = nullptr;// see State::connectRepsToCitizens!
		in.read(rcastc(&temp_prt.candidateID), sizeof(temp_prt.candidateID));
		in.read(rcastc(&temp_prt.round_mode), sizeof(temp_prt.round_mode));
	}
	catch (exception& err) {
		cout << "Could not load Party: " << err.what() << endl;
		throw infile_error("Party");
	}
	if (!in.good())
		throw infile_error("Party");
	*this = temp_prt;// If everything is OK - copy temp to this!
}

void Party::connectPartyreps2Citizens(CitizenList& citList) {
	Citizen* cnd = citList.getCitizenByID(this->candidateID);
	if (!cnd)
		throw connection_error("Party Candidate", "Citizen");
	this->candidate = cnd;
	this->drList.connectReps2Citizens(citList);
}