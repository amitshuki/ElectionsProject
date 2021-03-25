#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;
class id_validation_exeption :
	public exception
{
private:
	string msg;
public:
	id_validation_exeption() {
		this->msg.append("Invalid ID.");
	}
	id_validation_exeption(const int& id) {
		this->msg.append("Invalid ID." + id);
	}
	~id_validation_exeption() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};

