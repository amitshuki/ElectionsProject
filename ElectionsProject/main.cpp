#include <iostream>
#include "State.h"
#include "myString.h"
using namespace std;
using namespace myStr;

void run(const State& state);
void printMenu();
void addDistrictToState(State& state);
void addCitizen(State& state);
void addParty(State& state);
void addCitizenAsPartyRep(State& state);

void main() {

}

void run(const State& state) {
	int input = 0;
	while (input != 10) {
		printMenu();
		cin >> input;
		while (input < 1 || input>10) {
			cout << "Invalid choice." << endl;
			cin >> input;
			//handleInput(input)
		}

	}

}
void printMenu() {
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
	cout << "10. exit" << endl;
}
void handleInput(const int& input,State& state) {
	cout << endl << endl;
	switch (input) {
	case 1:
		addDistrictToState(state);
		break;
	case 2:
		addCitizen(state);
		break;
	case 3:
		addParty(state);
		break;
	case 4:
		addCitizenAsPartyRep(state);
		break;
	case 5:
		break;

	}
}

void addDistrictToState(State& state) {
	myString dstName;
	int rank;
	cout << "\tDistrict name: ";
	cin >> dstName;
	cout << "\tDistrict's rank (amount of electors): ";
	cin >> rank;
	while (rank <= 0) {
		cout << "\tInvalid amount of electors. Please try again: ";
		cin >> rank;
	}
	state.addDistrict(dstName, rank);
}
void addCitizen(State& state) {
	myString name;
	int id, birthYear, dstSN;
	cout << "\tName: ";
	cin >> name;
	cout << "\tYear of birth: ";
	cin >> birthYear;
	while (birthYear < 1880||birthYear>2020) {
		cout << "\tInvalid birth year. Please try again: ";
		cin >> birthYear;
	}
	cout << "\tDistrict serial number: ";
	cin >> dstSN;
	while (!state.checkExistingDistrictBySN(dstSN)) {
		cout << "\tInvalid district serial number. Please try again: ";
		cin >> dstSN;
	}
	state.addCitizen(name, id, birthYear, dstSN);
}
void addParty(State& state) {
	myString nameOfParty;
	int candidateID;
	cout << "\tName: ";
	cin >> nameOfParty;
	cout << "\tCandidate ID: ";
	cin >> candidateID;
	while (!state.checkExistingCitizenbyID(candidateID)) {
		cout << "\tInvalid candidate ID. Please try again: ";
		cin >> candidateID;
	}
	state.addParty(nameOfParty, candidateID);
}
void addCitizenAsPartyRep(State& state) {
	int repID, partySN, distrSN;
	cout << "\tCandidate's ID: ";
	cin >> repID;
	while (!state.checkExistingCitizenbyID(repID)) {
		cout << "\tInvalid candidate ID. Please try again: ";
		cin >> repID;
	}
	cout << "\tDistrict Serial Number: ";
	cin >> distrSN;
	while (!state.checkExistingDistrictBySN(distrSN)) {
		cout << "\tInvalid district Serial Number. Please try again: ";
		cin >> distrSN;
	}
	cout << "\tParty Serial Number: ";
	cin >> partySN;
	while (!state.checkExistingPartyBySN(partySN)) {
		cout << "\tInvalid party Serial Number. Please try again: ";
		cin >> partySN;
	}
	state.addCitizenAsPartyRepInDist(repID, partySN, distrSN);
}