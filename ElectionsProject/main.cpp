#include <iostream>
#include <fstream>
#include "StateLoader.h"
#include "state.h"
#include "UniformState.h"

#include "DynamicArray.h"

using namespace std;


void run();
void firstMenu(State*& state_ptr_ref);
void secondMenu(State*& state_ptr_ref);

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
int countDigits(int num);


int main() {
	run();
}


void run() {
	State* state = nullptr;
	try {
		firstMenu(state);
	}
	catch (exit_exception& exit) {
		delete state;
		return;
	}
	secondMenu(state);

	// Finished!
	delete state;
}
// ================================
void firstMenu(State*& state_ptr_ref) {
	int input;
	//First Menu:
	while (!state_ptr_ref) {
		cout << endl;
		printMenu1();
		std::cin >> input;
		try {
			if(input < 1 || input>3)
				throw range_error("Incorrect input.");
			state_ptr_ref = handleInput1(input);
		}
		catch (exit_exception& exit) {
			cout << exit.what() << endl;
			throw exit;
		}
		catch (infile_error& in_error) {
			cout << "State loading failed: " << in_error.what() << endl;
			return;
		}
		catch (exception& exp) {
			cout << exp.what() << endl;
			state_ptr_ref = nullptr;
		}
	}
}
void secondMenu(State*& state_ptr_ref) {
	int input;
	// State opened. Second menu:
	while (true) {
		printMenu2();
		cin >> input;
		try {
			if (input < 1 || input>12)
				throw range_error("Incorrect input.");
			handleInput2(input, state_ptr_ref);
		}
		catch (exit_exception& exit) {
			cout << exit.what() << endl;
			return;
		}
		catch (exception& exp) {
			cout << exp.what();
		}
		cout << endl;
	}
}

// ================================

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
// ================================

State* handleInput1(const int& input) {
	cout << endl;
	State* state = nullptr;
	try {
		switch (input) {
		case 1:
			state = createNewState();
			break;
		case 2:
			state = loadFromFile();
			break;
		case 3:
			throw exit_exception();
		default:
			throw range_error("Incorrect input.");
		}
	}
	catch (exit_exception& ext) {
		throw ext;
	}
	catch (range_error& r_err) {
		throw r_err;
	}
	catch (exception& exp) {
		delete state;
		throw exp;
	}
	if (!state)
		throw bad_alloc();
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
			throw exception("There are no districts in a uniform round.");
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
			throw bad_alloc();
		delete state;
		state = temp;
		break;
	case 12:
		throw exit_exception();
	default:
		break;
	}

}

State* createNewState() {
	int choice = 0, rank = 0, day, month, year;
	State* state = nullptr;
	cout << "Enter round type (1 = District Based round\\ 2 = Simple Round): ";
	cin >> choice;
	if (choice < 1 || choice>2)
		throw range_error("Invalid round type.");
	try {
		if (choice == 1)
			state = new DistrictBasedState();
		else {
			cout << "Enter amount of electors: ";
			cin >> rank;
			if (rank < 1)
				throw range_error("Invalid rank");
			state = new UniformState(rank);
		}
		if (!state)
			throw bad_exception();
	}
	catch (exception& exp) {
		cout << "State creation failure: " << exp.what() << endl;
		throw exp;
	}
	cout << "Enter elections date: (day\\month\\year): ";
	cin >> day;
	cin >> month;
	cin >> year;
	state->setDate(day, month, year);// need to verify
	return state;
}

// ================================
void addDistrictToState(DistrictBasedState& state) {
	string dstName;
	int rank, type;
	bool res = false;
	cout << "Add a District: " << endl;
	cout << "============== " << endl;;
	cout << "District name: ";
	cin >> dstName;
	cout << "District's rank (amount of electors): ";
	cin >> rank;
	if (rank <= 0)
		throw range_error("Invalid district rank.");
	else {
		cout << "District's type (1 = Divided , 2 = Uniform): ";
		cin >> type;
		if (type < 1 || type>2)
			throw range_error("Invalid input.");
		else {// type is ok!
			if (type == 1)
				state.addDistrict(dstName, rank, DistrictType::DIVIDED);
			else//if type==2
				dynamic_cast<DistrictBasedState&>(state).addDistrict(dstName, rank, DistrictType::UNIFIED);
		}
	}
}
void addCitizenWithoutDistricts(UniformState& state) {
	string name;
	int id, birthYear;
	bool res = false;
	cout << "Add a Citizen: " << endl;
	cout << "============== " << endl;;

	cout << "Name: ";
	cin >> name;
	cout << "ID: ";
	cin >> id;
	if (id < 1 || countDigits(id) != 9)
		throw range_error("Illigal id.");
	cout << "Year of birth: ";
	cin >> birthYear;
	if (state.getElectionsDate().year - birthYear < 18)
		throw range_error("Invalid birth year, only 18+ can vote.");
	state.addCitizen(name, id, birthYear);
}
void addCitizenWithDistricts(DistrictBasedState& state){
	string name;
	int id, birthYear, dstSN;
	cout << "Add a Citizen: " << endl;
	cout << "============== " << endl;;

	cout << "Name: ";
	cin >> name;
	cout << "ID: ";
	cin >> id;
	if (id < 1 || countDigits(id) != 9)
		throw range_error("Illigal id.");
	cout << "Year of birth: ";
	cin >> birthYear;
	if (state.getElectionsDate().year - birthYear < 18)
		throw range_error("Invalid birth year, only 18+ can vote.");
	cout << "District serial number: ";
	cin >> dstSN;
	state.addCitizen(name, id, birthYear, dstSN);// district SN verification inside.
}
void addParty(State& state) {
	string nameOfParty;
	int candidateID;
	cout << "Add a Party: " << endl;
	cout << "=========== " << endl;;
	cout << "Name: ";
	cin >> nameOfParty;
	cout << "Candidate ID: ";
	cin >> candidateID;
	state.addParty(nameOfParty, candidateID); // varification of candidate id inside.
}
void addCitizenAsPartyRepWithoutDistricts(UniformState& state) {
	int repID, partySN;
	cout << "Add a Citizen as Party Representative: " << endl;
	cout << "=====================================" << endl;;

	cout << "Representative's ID: ";
	cin >> repID;
	cout << "Party Serial Number: ";
	cin >> partySN;
	state.addCitizenAsPartyRep(repID, partySN); // verification inside
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
	state.addCitizenAsPartyRepInDist(repID, partySN, distrSN);// verification inside
}
// ================================

void vote(State& state) {
	int id, partySN;
	cout << "Citizen's ID: ";
	cin >> id;
	cout << "Party Serial Number: ";
	cin >> partySN;
	state.vote(id, partySN);// Verification inside!
}

// ================================
void save2File(State& state) {
	string fname;
	cout << "Enter file name:";
	cin >> fname;
	ofstream outfile(fname, ios::binary | ios::trunc);
	if (!outfile) {
		throw runtime_error("Error opening file");
	}
	StateLoader::save(outfile, state);
	outfile.close();
}
State* loadFromFile() {
	string fname;
	State* state;
	cout << "Enter file name:";
	cin >> fname;
	ifstream infile(fname, ios::binary);
	if (!infile) {
		throw runtime_error("Error opening file");
	}
	state = StateLoader::load(infile);
	infile.close();
	return state;
}
// ================================

int countDigits(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}
