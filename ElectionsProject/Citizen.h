#pragma once
class District;
#include "myString.h"
using namespace std;
using namespace myStr;
class Citizen
{
private:
	int id, districtSN, birthYear;
	District* dst;
	myString name;
	int votedPartySN;
	bool didVote;
public:
	Citizen();
	Citizen(const myString& name, const int& id, const int& birthYear, const int& districtSN);
	Citizen(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* mdst);

	

	void vote(const int& partySN);

	const int& getId()const { return id; }
	const myString& getName()const { return name; }
	const int& getDistrictSN() const { return districtSN; }
	District* getDistrict()const { return dst; }
	const int& getVotedPartySN() const { return votedPartySN; }
	bool hasVoted()const { return didVote; }
	friend ostream& operator<<(ostream& out, const Citizen& cit);
};
