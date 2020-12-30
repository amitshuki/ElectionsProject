#pragma once
class District;
#include "myString.h"
using namespace std;
using namespace myStr;


#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

enum class RoundMode { REGULAR, SIMPLE };

class Citizen
{
public:
private:
	int id, districtSN, birthYear;
	District* dst;
	myString name;
	int votedPartySN;
	bool didVote;
	RoundMode round_mode;
public:
	Citizen() :id(-1), districtSN(-1), birthYear(-1), name(""), votedPartySN(-1), didVote(false), dst(nullptr), round_mode(RoundMode::REGULAR){}
	Citizen(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* mdst, const RoundMode& rm);
	
	void vote(const int& partySN);

	const int& getId()const { return id; }
	const myString& getName()const { return name; }

	const int& getDistrictSN() const { 
		return districtSN; // Need to change according to roundmode?
	}
	District* getDistrict()const { 
		return dst; // Need to change according to roundmode?
	}

	const int& getVotedPartySN() const { return votedPartySN; }
	bool hasVoted()const { return didVote; }
	friend ostream& operator<<(ostream& out, const Citizen& cit);
	bool save(ostream& out) const;
	bool load(istream& in);

	friend class CitizenList;
};
