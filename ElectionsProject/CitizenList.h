#pragma once
#include <iostream>
#include "Citizen.h"
using namespace std;
class CitizenList
{
public:
	enum class deleteOption { DELETE_ALL, CANCLE_LIST };
	enum class saveloadOption { SAVE_AND_LOAD, NOT };
private:
	Citizen** citArr;
	int logSize, capacity;

	RoundMode round_mode;
	deleteOption delOpt;
	saveloadOption saveLoadOpt;
	void resizeArr();
	//Quick sort methods:
	void swap(Citizen*& a, Citizen*& b);
	int partition(const int& low, const int& high);
	void quickSort(const int& low, const int& high);

public:
	CitizenList(const RoundMode& rm, const deleteOption& dlOpt = deleteOption::CANCLE_LIST, const saveloadOption& slOpt = saveloadOption::NOT);
	CitizenList(const CitizenList& other);
	~CitizenList();

	bool addCitizenToList(Citizen* const cit);
	bool addCitizenToList(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* dst);
	bool checkExistingCitizenInListByID(const int& id)const;
	Citizen* const getCitizenByID(const int& id)const;
	const int& getLogSize()const { return logSize; }

	void printFirstXReps(const int& amount);

	CitizenList& operator=(const CitizenList& other);
	CitizenList& operator+=(const CitizenList& other);
	friend ostream& operator<<(ostream& out, const CitizenList& citList);

	bool save(ostream& out) const;
	bool load(istream& in);
};

