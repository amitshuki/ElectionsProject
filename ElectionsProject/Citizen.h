#pragma once
class District;

#include "my_exceptions.h"
using namespace std;


#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

enum class RoundMode { REGULAR, SIMPLE };

class Citizen
{
private:
	int id, districtSN, birthYear;
	District* dst;// Reference to district!
	string name;
	int votedPartySN;
	bool didVote;
	RoundMode round_mode;
public:
	Citizen() :id(-1), districtSN(-1), birthYear(-1), name(""), votedPartySN(-1), didVote(false), dst(nullptr), round_mode(RoundMode::REGULAR) {}
	Citizen(const string& name, const int& id, const int& birthYear, const int& districtSN, District* mdst, const RoundMode& rm);
	Citizen(istream& in) { load(in); }
	void vote(const int& partySN);

	void setDistrict(District* dst) { this->dst = dst; }

	const int& getId()const { return id; }
	const string& getName()const { return name; }
	const int& getDistrictSN() const { return districtSN; }
	District* getDistrict()const { return dst; }

	const int& getVotedPartySN() const { return votedPartySN; }
	bool hasVoted()const { return didVote; }
	Citizen& operator=(const Citizen& other);
	friend ostream& operator<<(ostream& out, const Citizen& cit);

	void save(ostream& out) const;
	void load(istream& in);

	friend class CitizenList;
};
