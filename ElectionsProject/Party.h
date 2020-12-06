#pragma once
#include <string>
#include "DistrictReps.h"
#include "Citizen.h"
using namespace std;
class Party
{
private:
	string name;
	Citizen& stateRepresentative;
	DistrictReps* districtRepsArr;
public:
};

