#include <iostream>
#include "State.h"
#include "myString.h"
using namespace std;
using namespace myStr;

void run(State& state);
void printMenu();
void handleInput(const int& input, State& state);
void addDistrictToState(State& state);
void addCitizen(State& state);
void addParty(State& state);
void addCitizenAsPartyRep(State& state);

int main() {
	State state;
	run(state);
	int i = 1;

}

void run(State& state) {
	int input = 0;
	while (input != 10) {
		printMenu();
		cin >> input;
		while (input < 1 || input>10) {
			cout << "Invalid choice. Try Again: ";
			cin >> input;
		}
		handleInput(input, state);
		cout << endl;
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
	cout << endl;
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
		state.showDistricts();
		break;
	case 6:
		state.showVotersBook();
		break;
	case 7:
		state.showParties();
		break;

	}
}

void addDistrictToState(State& state) {
	myString dstName;
	int rank;
	cout << "Add a District: " << endl;
	cout << "============== " << endl;;

	cout << "District name: ";
	cin >> dstName;
	cout << "District's rank (amount of electors): ";
	cin >> rank;
	if (rank <= 0)
		cout << "Invalid amount of electors.";
	else
		state.addDistrict(dstName, rank);
}
void addCitizen(State& state) {
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
	else
		state.addCitizen(name, id, birthYear, dstSN);
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
	else
		state.addParty(nameOfParty, candidateID);
}
void addCitizenAsPartyRep(State& state) {
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
	if(!state.checkExistingDistrictBySN(distrSN)) 
		cout << "Invalid district Serial Number. "<<endl;
	if (!state.checkExistingPartyBySN(partySN))
		cout << "Invalid party Serial Number. " << endl;
	else
		state.addCitizenAsPartyRepInDist(repID, partySN, distrSN);
}