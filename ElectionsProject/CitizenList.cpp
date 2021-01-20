#include "CitizenList.h"
using namespace std;
CitizenList::CitizenList(const RoundMode& rm, const deleteOption& dlOpt, const saveloadOption& slOpt):
	round_mode(rm), delOpt(dlOpt), saveLoadOpt(slOpt) {}
CitizenList::CitizenList(const CitizenList& other) {
	citArr = other.citArr;
	round_mode = other.round_mode;
	this->delOpt = other.delOpt;
	this->saveLoadOpt = other.saveLoadOpt;
}

CitizenList::~CitizenList() {
	if (delOpt == deleteOption::DELETE_ALL) {
		for (auto& i : citArr)
			delete i;
	}
}

bool CitizenList::addCitizenToList(Citizen* cit) {
	
	if (checkExistingCitizenInListByID(cit->id))// No other citizen with same ID
		return false;
	citArr.push_back(cit);
	return true;
}

bool CitizenList::addCitizenToList(const myString& name, const int& id, const int& birthYear, const int& districtSN, District* dst){
	if (checkExistingCitizenInListByID(id))
		return false;
	citArr.push_back(new Citizen(name, id, birthYear, districtSN, dst, this->round_mode));
	return true;
}
bool CitizenList::checkExistingCitizenInListByID(const int& id)const {
	for (auto& i : citArr)
		if (i->id == id)
			return true;
	return false;
}


Citizen* CitizenList::getCitizenByID(const int& id)const {
	for (auto& i : citArr)
		if (i->id == id)
			return i;
	return nullptr;
}

void CitizenList::printFirstXReps(const int& amount)const {
	int count = 0;
	for (auto& i : citArr) {
		cout << ++count << ". " << *i << endl;
		if (count >= amount)
			break;
	}
}

CitizenList& CitizenList::operator=(const CitizenList& other) {
	citArr = other.citArr;
	return *this;
}
CitizenList& CitizenList::operator+=(const CitizenList& other) {
	for (auto& i : other.citArr)
		citArr.push_back(i);
	return *this;
}
ostream& operator<<(ostream& out, const CitizenList& citList) {
	int count = 0;
	for (auto& i : citList.citArr)
		out << ++count << ". " << *i << endl;
	return out;
}

// DO SOMETHING WITH THIS THING - DO I NEED TO SORT?
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
	out.write(rcastcc(&citArr.getLogSize()), sizeof(citArr.getLogSize()));
	out.write(rcastcc(&delOpt), sizeof(delOpt));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	out.write(rcastcc(&saveLoadOpt), sizeof(saveLoadOpt));
	for (auto& i : citArr) {
		if (saveLoadOpt == saveloadOption::SAVE_AND_LOAD)
			i->save(out);
		else
			out.write(rcastcc(&(i->id)), sizeof(i->id));
		if (!out.good())
			break;
	}
	return out.good();
}
bool CitizenList::load(istream& in) {
	int size;
	in.read(rcastc(&size), sizeof(size));
	in.read(rcastc(&delOpt), sizeof(delOpt));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	in.read(rcastc(&saveLoadOpt), sizeof(saveLoadOpt));
	DynamicArray<Citizen*> newArr(size);	
	Citizen* temp;
	for (auto i = 0; i < size; i++) {
		if (!in.good())
			return false;
		if (saveLoadOpt == saveloadOption::SAVE_AND_LOAD)
			newArr.push_back(new Citizen(in));
		else {
			newArr.push_back(new Citizen());
			temp = newArr.back();
			// The following command reads the id of the citizen. class "State" is responsible to connect to actual citizens.
			in.read(rcastc(&temp->id), sizeof(temp->id));// Load id if save and load is false
		}
	}
	citArr = newArr;
	return in.good();
}