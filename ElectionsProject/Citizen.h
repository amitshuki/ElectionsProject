#pragma once
#include "myString.h"

using namespace std;
using namespace myStr;
class Citizen
{
private:
	int id, districtSN, birthYear;
	myString name;
	int votedPartySN;
	bool didVote;
public:
	Citizen() :id(-1), districtSN(-1), birthYear(-1), name(""), votedPartySN(-1), didVote(false) {}
	Citizen(const myString& name, const int& id, const int& birthYear, const int& districtSN) {
		this->name = name;
		this->id = id;
		this->birthYear = birthYear;
		this->districtSN = districtSN;
		this->votedPartySN = -1;
		this->didVote = false;
	}
	//~Citizen(); ---> defualt dtor.

	void vote(const int& partySN) { 
		this->votedPartySN = partySN; 
		this->didVote = true;
	}

	const int& getId()const { return id; }
	const myString& getName()const { return name; }
	const int& getDistrictSN() const { return districtSN; }
	const int& getVotedPartySN() const { return votedPartySN; }
	bool hasVoted()const { return didVote; }
	friend ostream& operator<<(ostream& out, const Citizen& cit) {
		out << "Name: " << cit.name << ", ";
		out << "ID: " << cit.id << ", ";
		out << "Birth year: " << cit.birthYear << ", ";
		out << "District serial no.: " << cit.districtSN;
		return out;
	}
};
