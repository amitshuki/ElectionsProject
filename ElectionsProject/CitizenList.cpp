#include "CitizenList.h"

CitizenList::CitizenList(const RoundMode& rm, const deleteOption& dlOpt, const saveloadOption& slOpt):
	citArr(nullptr), logSize(0), capacity(0), round_mode(rm), delOpt(dlOpt), saveLoadOpt(slOpt) {}
CitizenList::CitizenList(const CitizenList& other) {
	citArr = new Citizen * [other.capacity];
	for (int i = 0; i < other.logSize; i++)
		citArr[i] = other.citArr[i];
	logSize = other.logSize;
	capacity = other.capacity;
	round_mode = other.round_mode;
	this->delOpt = other.delOpt;
	this->saveLoadOpt = other.saveLoadOpt;
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

bool CitizenList::addCitizenToList(Citizen* const cit) {
	if (logSize == capacity)
		resizeArr();
	if (checkExistingCitizenInListByID(cit->id))// No other citizen with same ID
		return false;
	return citArr[logSize++] = cit;
}

bool CitizenList::addCitizenToList(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* dst){
	if (logSize == capacity)
		resizeArr();
	if (checkExistingCitizenInListByID(id))
		return false;
	return citArr[logSize++] = new Citizen(name, id, birthYear, districtSN, dst, this->round_mode);
}
bool CitizenList::checkExistingCitizenInListByID(const int& id)const {
	int i;
	for (i = 0; i < logSize; i++)
		if (citArr[i]->id == id)
			return true;
	return false;
}


Citizen* const CitizenList::getCitizenByID(const int& id)const {
	for (int i = 0; i < logSize; i++)
		if (citArr[i]->id == id)
			return citArr[i];
	return nullptr;
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

// A utility function to swap two elements  
void CitizenList::swap(Citizen*& a, Citizen*& b)
{
	Citizen* t = a;
	a = b;
	b = t;
}

int CitizenList::partition(const int& low, const int& high)
{
	int pivot = citArr[high]->id; // pivot  
	int i = (low - 1); // Index of smaller element  

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot  
		if (citArr[j]->id < pivot)
		{
			i++; // increment index of smaller element  
			swap(citArr[i], citArr[j]);
		}
	}
	swap(citArr[i + 1], citArr[high]);
	return (i + 1);
}

void CitizenList::quickSort(const int& low, const int& high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(low, high);

		// Separately sort elements before  
		// partition and after partition  
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}


bool CitizenList::save(ostream& out) const {
	out.write(rcastcc(&logSize), sizeof(logSize));
	out.write(rcastcc(&capacity), sizeof(this->capacity));
	out.write(rcastcc(&delOpt), sizeof(delOpt));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	out.write(rcastcc(&saveLoadOpt), sizeof(saveLoadOpt));
	for (auto i = 0; i < logSize && out.good(); i++) {
		if (saveLoadOpt == saveloadOption::SAVE_AND_LOAD)
			citArr[i]->save(out);
		else
			out.write(rcastcc(&citArr[i]->id), sizeof(citArr[i]->id));
	}
	return out.good();
}
bool CitizenList::load(istream& in) {
	int capacityFromFile;
	in.read(rcastc(&logSize), sizeof(logSize));
	in.read(rcastc(&capacityFromFile), sizeof(capacity));
	in.read(rcastc(&delOpt), sizeof(delOpt));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	in.read(rcastc(&saveLoadOpt), sizeof(saveLoadOpt));

	while (capacityFromFile > capacity)
		resizeArr();// Resize until there is enough room for the array

	for (auto i = 0; in.good() && i < logSize; i++) {
		if (!citArr[i])
			citArr[i] = new Citizen();// New allocation for unallocated citizens.
		if (saveLoadOpt == saveloadOption::SAVE_AND_LOAD)
			citArr[i]->load(in);// Load if save and load is true
		else
			in.read(rcastc(&citArr[i]->id), sizeof(citArr[i]->id));// Load id if save and load is false
	}
	// if saveLoadOpt == Ignore need to connect citizens ids to citizens.
	return in.good();
}