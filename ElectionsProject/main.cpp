#include <iostream>
#include "RegularRound.h"
#include "SimpleRound.h"
#include "myString.h"
using namespace std;
using namespace myStr;

void run(RegularRound& RegularRound);
void printMenu();
void handleInput(const int& input, RegularRound& RegularRound);
void addDistrictToRegularRound(RegularRound& RegularRound);
void addCitizen(RegularRound& RegularRound);
void addParty(RegularRound& RegularRound);
void addCitizenAsPartyRep(RegularRound& RegularRound);
void vote(RegularRound& RegularRound);
class A
{
public:
	A() { cout << "ctor A" << endl; }
	~A() { cout << "dtor A" << endl; };

private:

};
class B:A
{
public:
	B() { cout << "ctor B" << endl; };
	~B() { cout << "dtor B" << endl; };

private:

};
//int main() {
//	SimpleRound simpleRound(30);
//	myString name("citizen");
//	int i = 1;
//	for (i = 0; i < 1000; i++)
//		simpleRound.addCitizen(name, i, 1994);
//	simpleRound.addParty("Dumbo", 0);
//	simpleRound.addParty("Ior", 100);
//
//	for (i = 0; i < 30; i++) {
//		simpleRound.addCitizenAsPartyRep(i, 1);
//		simpleRound.addCitizenAsPartyRep(i+30, 2);
//	}
//
//	for (i = 0; i < 300; i++)
//		simpleRound.vote(i, 1);
//	for (i = 0; i < 300; i++)
//		simpleRound.vote(i + 500, 2);
//	simpleRound.showElectionsResults();
//	
//}

int i;
int main() {
	//B b;
	RegularRound RegularRound;
	RegularRound.addDistrict(myString("A"), 15, DistrictType::DIVIDED);
	RegularRound.addDistrict(myString("B"), 10, DistrictType::DIVIDED);
	RegularRound.addDistrict(myString("C"), 7, DistrictType::DIVIDED);
	myString name("citizen");
	int i = 1;
	for (i = 0; i < 100; i++)
		RegularRound.addCitizen(name, i, 1994, 1);
	for (i = 100; i < 200; i++)
		RegularRound.addCitizen(name, i, 1995, 2);
	for (i = 200; i < 300; i++)
		RegularRound.addCitizen(name, i, 1996, 3);

	RegularRound.addParty(myString("Dumbo"), 0);
	RegularRound.addParty(myString("Ior"), 100);
	for (i = 0; i < 15; i++) {
		RegularRound.addCitizenAsPartyRepInDist(i, 1, 1);
		RegularRound.addCitizenAsPartyRepInDist(i+15, 1, 2);
		RegularRound.addCitizenAsPartyRepInDist(i+30, 1, 3);
		RegularRound.addCitizenAsPartyRepInDist(i+45, 2, 1);
		RegularRound.addCitizenAsPartyRepInDist(i + 60, 2, 2);
		RegularRound.addCitizenAsPartyRepInDist(i + 75, 2, 3);
	}

	for (i = 0; i < 60; i++)
		RegularRound.vote(i, 1);
	for (i = 0; i < 40; i++)
		RegularRound.vote(i+60, 2);
	for (i = 0; i < 25; i++) {
		RegularRound.vote(i+100, 1);
		RegularRound.vote(i + 125, 2);
	}
	for (i = 0; i < 40; i++) {
		RegularRound.vote(i + 200, 1);
	}
	for (i = 0; i < 50; i++) {
		RegularRound.vote(i + 240, 2);
	}

	RegularRound.showElectionsResults();
}

void run(RegularRound& RegularRound) {
	int input = 0;
	while (input != 10) {
		printMenu();
		cin >> input;
		while (input < 1 || input>10) {
			cout << "Invalid choice. Try Again: ";
			cin >> input;
		}
		handleInput(input, RegularRound);
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
void handleInput(const int& input,RegularRound& RegularRound) {
	cout << endl;
	switch (input) {
	case 1:
		addDistrictToRegularRound(RegularRound);
		break;
	case 2:
		addCitizen(RegularRound);
		break;
	case 3:
		addParty(RegularRound);
		break;
	case 4:
		addCitizenAsPartyRep(RegularRound);
		break;
	case 5:
		RegularRound.showDistrict();
		break;
	case 6:
		RegularRound.showVotersBook();
		break;
	case 7:
		RegularRound.showParties();
		break;
	
	}
}

void addDistrictToRegularRound(RegularRound& RegularRound) {
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
	else if (!RegularRound.addDistrict(dstName, rank,DistrictType::DIVIDED))//Need to change district Type!!
			cout << "Could not add district." << endl;
}
void addCitizen(RegularRound& RegularRound) {
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
	else if (!RegularRound.checkExistingDistrictBySN(dstSN))
		cout << "Invalid district serial number." << endl;
	else if(!RegularRound.addCitizen(name, id, birthYear, dstSN))
			cout << "Could not add citizen." << endl;
}
void addParty(RegularRound& RegularRound) {
	myString nameOfParty;
	int candidateID;
	cout << "Add a Party: " << endl;
	cout << "=========== " << endl;;
	cout << "Name: ";
	cin >> nameOfParty;
	cout << "Candidate ID: ";
	cin >> candidateID;
	if (!RegularRound.checkExistingCitizenbyID(candidateID))
		cout << "Invalid candidate ID." << endl;
	else if(!RegularRound.addParty(nameOfParty, candidateID))
			cout << "Could not add district." << endl;

}
void addCitizenAsPartyRep(RegularRound& RegularRound) {
	int repID, partySN, distrSN;
	cout << "Add a Citizen as Party Representative: " << endl;
	cout << "=====================================" << endl;;

	cout << "Representative's ID: ";
	cin >> repID;
	cout << "District Serial Number: ";
	cin >> distrSN;
	cout << "Party Serial Number: ";
	cin >> partySN;
	if(!RegularRound.checkExistingCitizenbyID(repID)) 
		cout << "Invalid candidate ID. " << endl;
	else if(!RegularRound.checkExistingDistrictBySN(distrSN)) 
		cout << "Invalid district Serial Number. "<<endl;
	else if (!RegularRound.checkExistingPartyBySN(partySN))
		cout << "Invalid party Serial Number. " << endl;
	else
		if(!RegularRound.addCitizenAsPartyRepInDist(repID, partySN, distrSN))
			cout << "Could not add representative." << endl;

}
void vote(RegularRound& RegularRound) {
	int id, partySN;
	cout << "Citizen's ID: ";
	cin >> id;
	cout << "Party Serial Number: ";
	cin >> partySN;
	if (!RegularRound.checkExistingCitizenbyID(id))
		cout << "Invalid candidate ID. " << endl;
	else if (!RegularRound.checkExistingPartyBySN(partySN))
		cout << "Invalid party Serial Number. " << endl;
	else if (!RegularRound.vote(id, partySN))
		cout << "This citizen has already voted." << endl;
}
