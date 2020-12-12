#pragma once
#include "Party.h"
class PartyArr
{
private:
	
	Party* partyArr;
	int size = 0;



public:
	PartyArr();
	~PartyArr();

	int getSize(void) const { return size; }

	bool addParty(const Party&);
	int findPartyByID(int id) const;
	Party& getPartyByID(int id) const;
	void printList(void) const;
};

