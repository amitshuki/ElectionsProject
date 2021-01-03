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

	void resizeArr() {
		int i;
		if (capacity == 0)
			capacity++;
		Citizen** newCitArr = new Citizen * [capacity * 2];
		for (i = 0; i < capacity * 2; i++)
			if (i < logSize)
				newCitArr[i] = citArr[i];
			else
				newCitArr[i] = nullptr;
		delete[] citArr;
		citArr = newCitArr;
		capacity *= 2;
	}
public:
	CitizenList() :citArr(nullptr), logSize(0), capacity(0),delOpt(deleteOption::CANCLE_LIST) {}
	CitizenList(const CitizenList& other) {
		citArr = new Citizen * [other.capacity];
		for (int i = 0; i < other.logSize; i++)
			citArr[i] = other.citArr[i];
		logSize = other.logSize;
		capacity = other.capacity;
		this->delOpt = other.delOpt;
	}
	~CitizenList(){
		int i;
		if (delOpt == deleteOption::DELETE_ALL) {
			for (i = 0; i < logSize; i++)
				delete citArr[i];
		}
		delete[] citArr;
	}

	bool addCitizenToList(Citizen* cit){
		if (logSize == capacity)
			resizeArr();
		if (checkExistingCitizenInListByID(cit->getId()))
			return false;
		return citArr[logSize++] = cit;
	}
	bool checkExistingCitizenInListByID(const int& id)const {
		int i;
		for (i = 0; i < logSize; i++)
			if (citArr[i]->getId() == id)
				return true;
		return false;
	}
	bool setDeleteOpt(const deleteOption& delOpt) { 
		this->delOpt = delOpt;
		return this->delOpt == delOpt; 
	}
	
	Citizen* const getCitizenByID(const int& id)const {
		for (int i = 0; i < logSize; i++)
			if (citArr[i]->getId() == id)
				return citArr[i];
		return nullptr;
	}
	const int& getLogSize()const { return logSize; }

	CitizenList& getSubList(const int& amount)const {
		CitizenList* newCitList = new CitizenList;
		for (int i = 0; i < amount && i < logSize; i++)
			newCitList->addCitizenToList(citArr[i]);
		return *newCitList;
	}

	CitizenList& operator=(const CitizenList& other) {
		Citizen** newCitArr = new Citizen * [other.capacity];
		for (int i = 0; i < other.logSize; i++)
			newCitArr[i] = other.citArr[i];
		delete[] citArr;
		citArr = newCitArr;
		logSize = other.logSize;
		capacity = other.capacity;
		return *this;
	}
	CitizenList& operator+=(const CitizenList& other) {
		while (logSize + other.logSize > capacity)// Resize until there is enough room for everybody
			resizeArr();
		for (int i = 0; i < other.logSize; i++)
			citArr[i + logSize] = other.citArr[i];
		return *this;
	}
	friend ostream& operator<<(ostream& out, const CitizenList& citList) {
		int i;
		for (i = 0; i < citList.logSize; i++)
			out << i + 1 << ". " << *(citList.citArr[i]) << endl;
		return out;
	}
};

