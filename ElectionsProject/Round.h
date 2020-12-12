#pragma once
#include "Date.h"
#include "State.h"
class Round
{
private:
	Citizen* citArr;
	District* distArr;
	Party* partyArr;


public:
	Round();
	~Round();

	void MainPrint(void);
	void CitizenMenu(void);
	void DistirctMenu(void);
	void PartyMenu(void);
	void addRrp(void);

};

