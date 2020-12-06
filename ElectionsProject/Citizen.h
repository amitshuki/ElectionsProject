#pragma once
#include <string>
#include "Date.h"
#include "District.h"
using namespace std;
class Citizen
{
private:
	int id;
	string name;
	int districtSN;
	Date dob;
	int votedPartySN;
public:
	Citizen(int id, const string& name, int districtSN , Date& dob);
	void vote(int partySN) { this->votedPartySN = partySN; }
	const int& getId()const { return id; }
	const string& getName()const { return name; }
	const int& getDistrictSN() { return districtSN; }
	const Date& getDOB() { return dob; }
	const int& getVotedPartySN() { return votedPartySN; }
	void setVotedPartySN(int partySN) { votedPartySN = partySN; }
};
