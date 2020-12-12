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

	void operator=(const CitizenList& other) {

		for(int i = 0;i<)
	}
	friend ostream& operator<<(ostream& out, const CitizenList& citList) {
		int i;
		for (i = 0; i < citList.logSize; i++)
			out << *(citList.citArr[i]) << endl;
		return out;
	}
};

