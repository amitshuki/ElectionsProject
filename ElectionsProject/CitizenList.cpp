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

void CitizenList::addCitizenToList(Citizen* cit) {
	
	if (checkExistingCitizenInListByID(cit->id))// No other citizen with same ID
		throw adding_error("Citizen");
	citArr.push_back(cit);
}

void CitizenList::addCitizenToList(const string& name, const int& id, const int& birthYear, const int& districtSN, District* dst){
	Citizen* cit = new Citizen(name, id, birthYear, districtSN, dst, this->round_mode);
	if (!cit)
		throw bad_alloc();
	addCitizenToList(cit);
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
	if (this != &other)
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

void CitizenList::save(ostream& out) const {
	out.write(rcastcc(&citArr.getLogSize()), sizeof(citArr.getLogSize()));
	out.write(rcastcc(&delOpt), sizeof(delOpt));
	out.write(rcastcc(&round_mode), sizeof(round_mode));
	out.write(rcastcc(&saveLoadOpt), sizeof(saveLoadOpt));
	if (!out.good())
		throw outfile_error();
	for (auto& i : citArr) {
		if (saveLoadOpt == saveloadOption::SAVE_AND_LOAD)
			i->save(out);
		else
			out.write(rcastcc(&(i->id)), sizeof(i->id));
		if (!out.good()) 
			throw outfile_error();
	}
}
void CitizenList::load(istream& in) {
	int size;
	in.read(rcastc(&size), sizeof(size));
	in.read(rcastc(&delOpt), sizeof(delOpt));
	in.read(rcastc(&round_mode), sizeof(round_mode));
	in.read(rcastc(&saveLoadOpt), sizeof(saveLoadOpt));
	DynamicArray<Citizen*> newArr(size);	
	Citizen* temp;
	for (auto i = 0; in.good() && i < size; i++) {
		switch (saveLoadOpt) {
		case saveloadOption::SAVE_AND_LOAD:
			temp = new Citizen(in);
			break;
		case saveloadOption::NOT:
			temp = new Citizen();
			if (!temp)
				break;
			// The following command reads the id of the citizen. class "State" is responsible to connect to actual citizens.
			in.read(rcastc(&temp->id), sizeof(temp->id));// Load id if save and load is false
			break;
		default:
			throw undefined_option("saveLoadOption");
		}
		if (!temp) {
			for (auto& j : newArr)
				delete j;
			throw bad_alloc();
		}
		newArr.push_back(temp);
	}
	if (!in.good())
		throw infile_error("CitizenList");
	citArr = newArr;
}