#pragma once
#include <iostream>
using namespace std;
class id_validation_exeption :
	public exception
{
private:
	char* msg;
public:
	id_validation_exeption() {
		msg = new char[50];
		sprintf(msg, "Invalid ID.");
	}
	id_validation_exeption(const int& id) {
		msg = new char[50];
		sprintf(msg, "Invalid ID: %d", id);
	}
	~id_validation_exeption() { delete[] msg; }
	virtual const char* what()  const throw() { return msg; }
};

