#pragma once
#include <iostream>
#include "Citizen.h"
#include "DynamicArray.h"
#include "my_exceptions.h"
using namespace std;

class CitizenList
{
public:
	enum class deleteOption { DELETE_ALL, CANCLE_LIST };
	enum class saveloadOption { SAVE_AND_LOAD, NOT };
private:
	DynamicArray<Citizen*> citArr;

	RoundMode round_mode;
	deleteOption delOpt;
	saveloadOption saveLoadOpt;

public:
	CitizenList(const RoundMode& rm, const deleteOption& dlOpt = deleteOption::CANCLE_LIST, const saveloadOption& slOpt = saveloadOption::NOT);
	CitizenList(const CitizenList& other);
	CitizenList(istream& in) { load(in); }
	~CitizenList();

	void addCitizenToList(Citizen* cit);
	void addCitizenToList(const string& name, const int& id, const int& birthYear, const int& districtSN, District* dst);
	bool checkExistingCitizenInListByID(const int& id)const;
	Citizen* getCitizenByID(const int& id)const;
	const int& getLogSize()const { return citArr.getLogSize(); }
	const RoundMode& getRoundMode()const { return round_mode; }
	void printFirstXReps(const int& amount)const;

	Citizen*& operator[](const int& idx) const { return citArr[idx]; }
	// operator= only copies citizens. Does not copy roundmode etc..
	CitizenList& operator=(const CitizenList& other);
	CitizenList& operator+=(const CitizenList& other);
	friend ostream& operator<<(ostream& out, const CitizenList& citList);

	void save(ostream& out) const;
	void load(istream& in);
};

