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
void vote(State& state);


int main() {
	State state;
	state.addDistrict(myString("A"),15);
	state.addDistrict(myString("B"), 10);
	state.addDistrict(myString("C"), 7);
	myString name("citizen");
	int i = 1;
	for (i = 0; i < 100; i++)
		state.addCitizen(name, i, 1994, 1);
	for (i = 100; i < 200; i++)
		state.addCitizen(name, i, 1995, 2);
	for (i = 200; i < 300; i++)
		state.addCitizen(name, i, 1996, 3);

	state.addParty(myString("Dumbo"), 0);
	state.addParty(myString("Ior"), 100);
	for (i = 0; i < 15; i++) {
		state.addCitizenAsPartyRepInDist(i, 1, 1);
		state.addCitizenAsPartyRepInDist(i+15, 1, 2);
		state.addCitizenAsPartyRepInDist(i+30, 1, 3);
		state.addCitizenAsPartyRepInDist(i+45, 2, 1);
		state.addCitizenAsPartyRepInDist(i + 60, 2, 2);
		state.addCitizenAsPartyRepInDist(i + 75, 2, 3);
	}

	for (i = 0; i < 60; i++)
		state.vote(i, 1);
	for (i = 0; i < 40; i++)
		state.vote(i+60, 2);
	for (i = 0; i < 25; i++) {
		state.vote(i+100, 1);
		state.vote(i + 125, 2);
	}
	for (i = 0; i < 40; i++) {
		state.vote(i + 200, 1);
	}
	for (i = 0; i < 50; i++) {
		state.vote(i + 240, 2);
	}

	state.showElectionsResults();
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
		state.showDistrict();
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
	else if (!state.addDistrict(dstName, rank))
			cout << "Could not add district." << endl;
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
			cout << "Could not add district." << endl;

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
