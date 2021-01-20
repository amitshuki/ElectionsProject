#pragma once
#include <iostream>
#include "Citizen.h"
#include "DynamicArray.h"
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
	//Quick sort methods:
	void swap(Citizen*& a, Citizen*& b);
	int partition(const int& low, const int& high);
	void quickSort(const int& low, const int& high);

public:
	CitizenList(const RoundMode& rm, const deleteOption& dlOpt = deleteOption::CANCLE_LIST, const saveloadOption& slOpt = saveloadOption::NOT);
	CitizenList(const CitizenList& other);
	CitizenList(istream& in) { load(in); }
	~CitizenList();

	bool addCitizenToList(Citizen* cit);
	bool addCitizenToList(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* dst);
	bool checkExistingCitizenInListByID(const int& id)const;
	Citizen* getCitizenByID(const int& id)const;
	const int& getLogSize()const { return citArr.getLogSize(); }

	void printFirstXReps(const int& amount)const;

	Citizen* operator[](const int& idx)const{ return citArr[idx]; }
	// operator= only copies citizens. Does not copy roundmode etc..
	CitizenList& operator=(const CitizenList& other);
	CitizenList& operator+=(const CitizenList& other);
	friend ostream& operator<<(ostream& out, const CitizenList& citList);

	bool save(ostream& out) const;
	bool load(istream& in);
};

