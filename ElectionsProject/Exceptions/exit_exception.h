#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;
class exit_exception:
	public exception
{
private:
	string msg;
public:
	exit_exception() {
		this->msg.append("Goodbye.");
	}
	~exit_exception() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};

