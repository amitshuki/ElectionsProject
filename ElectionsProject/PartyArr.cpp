#include "PartyArr.h"
using namespace std;

PartyArr::PartyArr() {
	partyArr =nullptr;
	size = 0;
	
}
PartyArr::~PartyArr() {
	if (partyArr!=nullptr)
	delete[] partyArr;
}

bool PartyArr::addParty(const Party& _party) {

	if (size == 0) {
		partyArr = new Party[1];
		partyArr[0] = _party;
		size++;
		return true;
	}
	else if (size>0)
	{
		Party* temp = new Party[size + 1];
		for (int i = 0; i < size; i++) {
			temp[i] = this->partyArr[i];
		}
		temp[size] = _party;
		size++;
		return true;
	}
	else
		return false;


}
//int findPartyByID(int id) const;
//Party& getPartyByID(int id) const; not sure what type is the the id
void PartyArr::printList(void) const {
	for (int i = 0; i < size; i++) {
		partyArr[i].printParty();

	}


}
