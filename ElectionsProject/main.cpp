#include <iostream>
#include <fstream>
#include "StateLoader.h"
#include "state.h"
#include "UniformState.h"
#include "myString.h"
using namespace std;
using namespace myStr;

void run();
void printMenu1();
void printMenu2();
State* handleInput1(const int& input);
State* createNewState();
void handleInput2(const int& input, State*& state);
void addDistrictToState(DistrictBasedState& state);
void addCitizenWithDistricts(DistrictBasedState& state);
void addCitizenWithoutDistricts(UniformState& state);
void addParty(State& state);
void addCitizenAsPartyRepWithDistricts(DistrictBasedState& state);
void addCitizenAsPartyRepWithoutDistricts(UniformState& state);
void vote(State& state);
void save2File(State& state);
State* loadFromFile();

	
int main() {
	run();
}
void run() {	
	int input = 0;
	State* state = nullptr;
	printMenu1();
	cin >> input;
	while (input < 1 || input>3) {
		cout << "Invalid choice. Try Again: ";
		cin >> input;
	}
	state = handleInput1(input);
	if (!state)
		return;
	cout << endl;
	while (input != 12) {
		printMenu2();
		cin >> input;
		while (input < 1 || input>12) {
			cout << "Invalid choice. Try Again: ";
			cin >> input;
		}
		handleInput2(input, state);
		cout << endl;
	}
}
void printMenu1() {
	cout << "Initialization Menu:" << endl << "================" << endl;
	cout << "1. Create new elections round." << endl;
	cout << "2. Load elections round from file" << endl;
	cout << "3. exit" << endl;
}
void printMenu2() {
	cout << "Main Menu:" << endl << "==========" << endl;
	cout << "1. Add District" << endl;
	cout << "2. Add Citizen" << endl;
	cout << "3. Add Party" << endl;
	cout << "4. Add Citizen as Party representative" << endl;
	cout << "5. Show Districts" << endl;
	cout << "6. Show Citizens" << endl;
	cout << "7. Show Parties" << endl;
	cout << "8. Vote" << endl;
	cout << "9. Show voting results" << endl;
	cout << "10. Save Round to file" << endl;
	cout << "11. Load Round from file" << endl;
	cout << "12. exit" << endl;
}
State* handleInput1(const int& input) {
	cout << endl;
	State* state = nullptr;
	switch (input) {
	case 1:
		state = createNewState();
		break;
	case 2:
		state = loadFromFile();
		break;
	case 3:
		return nullptr;
	}
	return state;
}
State* createNewState() {
	int choice = 0, rank = 0, day, month, year;
	State* state = nullptr;
	cout << "Enter round type (1 = District Based round\\ 2 = Simple Round): ";
	cin >> choice;
	while (choice < 1 || choice>2) {
		cout << "Invalid choice. Try Again: ";
		cin >> choice;
	}
	if (choice == 1)
		state = new DistrictBasedState();
	else {
		cout << "Enter amount of electors: ";
		cin >> rank;
		while (rank < 1) {
			cout << "Invalid rank. Try Again: ";
			cin >> rank;
		}
		state = new UniformState(rank);
	}
	cout << "Enter elections date: (day\\month\\year): ";
	cin >> day;
	cin >> month;
	cin >> year;
	state->setDate(day, month, year);
	return state;
}

void handleInput2(const int& input,State*& state) {
	State* temp;
	cout << endl;
	switch (input) {
	case 1:
		if (typeid(*state) == typeid(UniformState))
			cout << "Cannot add districts in a simple round." << endl;
		else
			addDistrictToState(dynamic_cast<DistrictBasedState&>(*state));
		break;
	case 2:
		if (typeid(*state) == typeid(UniformState))
			addCitizenWithoutDistricts(dynamic_cast<UniformState&>(*state));
		else// if state = districtbasedState
			addCitizenWithDistricts(dynamic_cast<DistrictBasedState&>(*state));
		break;
	case 3:
		addParty(*state);
		break;
	case 4:
		if (typeid(*state) == typeid(UniformState))
			addCitizenAsPartyRepWithoutDistricts(dynamic_cast<UniformState&>(*state));
		else// if state = districtbasedState
			addCitizenAsPartyRepWithDistricts(dynamic_cast<DistrictBasedState&>(*state));
		break;
	case 5:
		if (typeid(*state) == typeid(DistrictBasedState))
			dynamic_cast<DistrictBasedState&>(*state).showDistrict();
		else
			cout << "There are no districts in a uniform round." << endl;
		break;
	case 6:
		state->showVotersBook();
		break;
	case 7:
		state->showParties();
		break;
	case 8:
		vote(*state);
		break;
	case 9:
		state->showElectionsResults();
		break;
	case 10:
		save2File(*state);
		break;
	case 11:
		temp = loadFromFile();
		if (!temp)
			cout << "Could not load state." << endl;
		else {
			delete state;
			state = temp;
		}
		break;
	case 12:
		break;
	}
}

void addDistrictToState(DistrictBasedState& state) {
	myString dstName;
	int rank, type;
	bool res = false;
	cout << "Add a District: " << endl;
	cout << "============== " << endl;;
	cout << "District name: ";
	cin >> dstName;
	cout << "District's rank (amount of electors): ";
	cin >> rank;
	if (rank <= 0)
		cout << "Invalid amount of electors.";
	else {
		cout << "District's type (1 = Divided , 2 = Uniform): ";
		cin >> type;
		if (type < 1 || type>2)
			cout << "Invalid type.";
		else {// type is ok!
			if (type == 1)
				res = state.addDistrict(dstName, rank, DistrictType::DIVIDED);
			else//if type==2
				res = dynamic_cast<DistrictBasedState&>(state).addDistrict(dstName, rank, DistrictType::UNIFIED);
			if (!res)
				cout << "Could not add district." << endl;
		}
	}
}

void addCitizenWithoutDistricts(UniformState& state) {
	myString name;
	int id, birthYear, dstSN;
	bool res = false;
	cout << "Add a Citizen: " << endl;
	cout << "============== " << endl;;

	cout << "Name: ";
	cin >> name;
	cout << "ID: ";
	cin >> id;
	cout << "Year of birth: ";
	cin >> birthYear;
	if (id < 1)
		cout << "Invalid ID." << endl;
	else if (birthYear < 1880 || birthYear>2021)
		cout << "Invalid birth year. " << endl;
	res = state.addCitizen(name, id, birthYear);
	if (!res)
		cout << "Could not add citizen." << endl;
}
void addCitizenWithDistricts(DistrictBasedState& state){
	myString name;
	int id, birthYear, dstSN;
	cout << "Add a Citizen: " << endl;
	cout << "============== " << endl;;

	cout << "Name: ";
	cin >> name;
	cout << "ID: ";
	cin >> id;
	cout << "Year of birth: ";
	cin >> birthYear;
	cout << "District serial number: ";
	cin >> dstSN;
	if (id < 1)
		cout << "Invalid ID." << endl;
	else if (birthYear < 1880 || birthYear>2020)
		cout << "Invalid birth year. " << endl;
	else if (!state.checkExistingDistrictBySN(dstSN))
		cout << "Invalid district serial number." << endl;
	else if(!state.addCitizen(name, id, birthYear, dstSN))
			cout << "Could not add citizen." << endl;
}
void addParty(State& state) {
	myString nameOfParty;
	int candidateID;
	cout << "Add a Party: " << endl;
	cout << "=========== " << endl;;
	cout << "Name: ";
	cin >> nameOfParty;
	cout << "Candidate ID: ";
	cin >> candidateID;
	if (!state.checkExistingCitizenbyID(candidateID))
		cout << "Invalid candidate ID." << endl;
	else if(!state.addParty(nameOfParty, candidateID))
			cout << "Could not add party." << endl;

}
void addCitizenAsPartyRepWithoutDistricts(UniformState& state) {
	int repID, partySN, distrSN;
	cout << "Add a Citizen as Party Representative: " << endl;
	cout << "=====================================" << endl;;

	cout << "Representative's ID: ";
	cin >> repID;
	cout << "Party Serial Number: ";
	cin >> partySN;
	if (!state.checkExistingCitizenbyID(repID))
		cout << "Invalid candidate ID. " << endl;
	else if (!state.checkExistingPartyBySN(partySN))
		cout << "Invalid party Serial Number. " << endl;
	else if (!state.addCitizenAsPartyRep(repID, partySN))
			cout << "Could not add representative." << endl;

}
void addCitizenAsPartyRepWithDistricts(DistrictBasedState& state) {
	int repID, partySN, distrSN;
	cout << "Add a Citizen as Party Representative: " << endl;
	cout << "=====================================" << endl;;

	cout << "Representative's ID: ";
	cin >> repID;
	cout << "District Serial Number: ";
	cin >> distrSN;
	cout << "Party Serial Number: ";
	cin >> partySN;
	if(!state.checkExistingCitizenbyID(repID)) 
		cout << "Invalid candidate ID. " << endl;
	else if(!state.checkExistingDistrictBySN(distrSN)) 
		cout << "Invalid district Serial Number. "<<endl;
	else if (!state.checkExistingPartyBySN(partySN))
		cout << "Invalid party Serial Number. " << endl;
	else
		if(!state.addCitizenAsPartyRepInDist(repID, partySN, distrSN))
			cout << "Could not add representative." << endl;

}
void vote(State& state) {
	int id, partySN;
	cout << "Citizen's ID: ";
	cin >> id;
	cout << "Party Serial Number: ";
	cin >> partySN;
	if (!state.checkExistingCitizenbyID(id))
		cout << "Invalid candidate ID. " << endl;
	else if (!state.checkExistingPartyBySN(partySN))
		cout << "Invalid party Serial Number. " << endl;
	else if (!state.vote(id, partySN))
		cout << "This citizen has already voted." << endl;
}
void save2File(State& state) {
	string fname;
	cout << "Enter file name:";
	cin >> fname;
	ofstream outfile(fname, ios::binary | ios::trunc);
	if (!outfile) {
		cout << "Error opening file." << endl;
		return;
	}
	StateLoader::save(outfile, state);
	outfile.close();
}
State* loadFromFile() {
	string fname;
	State* state;
	cout << "Enter file name:";
	cin >> fname;
	ifstream infile("test.bin", ios::binary);
	if (!infile) {
		cout << "Error opening file." << endl;
		exit(-1);
	}
	state = (StateLoader::load(infile));
	infile.close();
	return state;
}