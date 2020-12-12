#pragma once
#include "Party.h"
class Party;
class VotersForParty//This is connection diagram #2
{
private:
	int numOfVoters;
	int partySN;
public:
	VotersForParty() :numOfVoters(0), partySN(-1) {}
};

