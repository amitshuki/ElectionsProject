#pragma once
#include <iostream>
#include "Citizen.h"
using namespace std;
class CitizenList
{
public:
	enum class deleteOption { DELETE_ALL, CANCLE_LIST };
private:
	Citizen** citArr;
	int logSize, capacity;

	deleteOption delOpt;
	RoundMode round_mode;
	void resizeArr();
public:
	CitizenList(const RoundMode& rm);
	CitizenList(const CitizenList& other);
	~CitizenList();

	bool addCitizenToList(Citizen* const cit);
	bool addCitizenToList(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* dst);
	bool checkExistingCitizenInListByID(const int& id)const;
	bool setDeleteOpt(const deleteOption& delOpt);
	
	Citizen* const getCitizenByID(const int& id)const;
	const int& getLogSize()const { return logSize; }

	CitizenList& getSubList(const int& amount)const;


	void printFirstXReps(const int& amount);

	CitizenList& operator=(const CitizenList& other);
	CitizenList& operator+=(const CitizenList& other);
	friend ostream& operator<<(ostream& out, const CitizenList& citList);
};

