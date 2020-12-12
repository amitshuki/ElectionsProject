#include "Round.h"


void Round::MainPrint()
{
	int input;

	while (true) {
		cout << "Round Main Menu: " << endl;
		cout << "1. Add District" << endl;
		cout << "2. Add Citizen" << endl;
		cout << "3. Add Party" << endl;
		cout << "4. Make Citizen a Representative" << endl;
		cout << "5. Print Citizen's List" << endl;
		cout << "6. Print Party's List" << endl;
		cout << "7. Print District's List" << endl;
		cout << "8. Vote " << endl;
		cout << "9. View election results " << endl;
		cout << "0. Exit" << endl;

		cin >> input;

		if (input == 1) {
			DistirctMenu();
		}
		else if (input == 2) {
			CitizenMenu();
		}
		else if (input == 3) {
			PartyMenu();
		}
		else if (input == 4) {
			MakeRepMenu();
		}
		else if (input == 5) {
			printDistricts();
		}
		else if (input == 6) {
			printCtzs();
		}
		else if (input == 7) {
			printpartys();
		}
		else if (input == 8) {
			addVote();
		}
		else if (input == 9) {
			printVotingRes();
		}
		else if (input == 10) {
			break;
		}

	}
}

void Round::addRrp(void)
{
	int ID;

	while (true) {
		cout << "Please Enter ID of The new candidate:" << endl;
		cout << "0. Exit;" << endl;

		cin >> ID;

		if (ID == 0)
			break;

		if (cList->findCitizenByID(tempID) != 0) {
			Citizen& c1 = cList->getCitizenByID(tempID);

			if (c1.getRepPointer() == nullptr) {
				cout << "Make " << c1.getName() << " Representative " << endl;
				int temParty;
				cout << "Please Enter party id :" << endl;
				cin >> temParty;

				if (pList->findPartyByID(temParty)) {
					c1.setRepresentative(temParty);
					pList->getPartyByID(temParty).addCitizen(c1);
					dList->getDistrictByID(c1.getDistric()).removeCitizen(c1);
					cout << c1.getName() << " Set Successfully as a Rep;" << endl;
				}
				else {
					cout << "Party not found;" << endl;
				}
			}
			else {
				cout << c1.getName() << " is already a Representative in party: " << c1.getRepPointer()->getPartyID() << endl;
			}
		}
		else {
			cout << "Cannot find ID " << tempID << endl;
		}
	}

}