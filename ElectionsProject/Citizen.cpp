#include "Citizen.h"
#include "Date.h"
#include <string>
using namespace std;

Citizen::Citizen(int id, const string& name, int districtSN, Date& dob) {
	checkInputValidity("ID", id, 1, 0);
	this->name = name;
	this->districtSN = districtSN;
	this->dob = dob;
}

