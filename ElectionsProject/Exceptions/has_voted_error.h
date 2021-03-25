#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
class has_voted_error :
	public exception
{
private:
	string msg;
public:
	has_voted_error(const int& id) {
		this->msg += "Citizen with id: " + id;
		this->msg += " has already voted. ";
	}
	~has_voted_error() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};


