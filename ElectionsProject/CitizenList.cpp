#include "CitizenList.h"

CitizenList::CitizenList() :citArr(nullptr), logSize(0), capacity(0), delOpt(deleteOption::CANCLE_LIST) {}
CitizenList::CitizenList(const CitizenList& other) {
	citArr = new Citizen * [other.capacity];
	for (int i = 0; i < other.logSize; i++)
		citArr[i] = other.citArr[i];
	logSize = other.logSize;
	capacity = other.capacity;
	this->delOpt = other.delOpt;
}
CitizenList::~CitizenList() {
	int i;
	if (delOpt == deleteOption::DELETE_ALL) {
		for (i = 0; i < logSize; i++)
			delete citArr[i];
	}
	delete[] citArr;
}

void CitizenList::resizeArr() {
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


bool CitizenList::addCitizenToList(Citizen* cit) {
	if (logSize == capacity)
		resizeArr();
	if (checkExistingCitizenInListByID(cit->getId()))
		return false;
	return citArr[logSize++] = cit;
}
bool CitizenList::checkExistingCitizenInListByID(const int& id)const {
	int i;
	for (i = 0; i < logSize; i++)
		if (citArr[i]->getId() == id)
			return true;
	return false;
}
bool CitizenList::setDeleteOpt(const deleteOption& delOpt) {
	this->delOpt = delOpt;
	return this->delOpt == delOpt;
}

Citizen* const CitizenList::getCitizenByID(const int& id)const {
	for (int i = 0; i < logSize; i++)
		if (citArr[i]->getId() == id)
			return citArr[i];
	return nullptr;
}

CitizenList& CitizenList::getSubList(const int& amount)const {
	CitizenList* newCitList = new CitizenList;
	for (int i = 0; i < amount && i < logSize; i++)
		newCitList->addCitizenToList(citArr[i]);
	return *newCitList;
}

void CitizenList::printFirstXReps(const int& amount) {
	for (int i = 0; i < amount && i < logSize; i++)
		cout << i + 1 << ". " << *(citArr[i]) << endl;
}

CitizenList& CitizenList::operator=(const CitizenList& other) {
	Citizen** newCitArr = new Citizen * [other.capacity];
	for (int i = 0; i < other.logSize; i++)
		newCitArr[i] = other.citArr[i];
	delete[] citArr;
	citArr = newCitArr;
	logSize = other.logSize;
	capacity = other.capacity;
	return *this;
}
CitizenList& CitizenList::operator+=(const CitizenList& other) {
	while (logSize + other.logSize > capacity)// Resize until there is enough room for everybody
		resizeArr();
	for (int i = 0; i < other.logSize; i++)
		citArr[i + logSize] = other.citArr[i];
	return *this;
}
ostream& operator<<(ostream& out, const CitizenList& citList) {
	int i;
	for (i = 0; i < citList.logSize; i++)
		out << i + 1 << ". " << *(citList.citArr[i]) << endl;
	return out;
}