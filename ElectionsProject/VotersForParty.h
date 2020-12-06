#pragma once
#include "Party.h"
class Party;
class VotersForParty//This is connection diagram #2
{
private:
	int numOfVoters;
	Party* party;
public:
	VotersForParty() :numOfVoters(0), party(nullptr) {}
};

