#pragma once
#include <iostream>
#include "State.h"
#include "UniformState.h"
#include "DistrictBasedState.h"
using namespace std;

enum class StateType { DISTRICT_BASED, UNIFORM};

class StateLoader
{
public:
	static void save(ostream& out, const State& rnd);
	static State* load(istream& in);
};

