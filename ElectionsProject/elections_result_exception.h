#pragma once
#include <iostream>
using namespace std;
class elections_result_exception :
    public exception
{
private:
	char* msg;
public:
	elections_result_exception () {
		msg = new char[50];
		sprintf(msg, "Unable to calculate results.");
	}
	elections_result_exception(const char* msg) {
		this->msg = new char[100];
		sprintf(this->msg, "Unable to calculate results: ");
		strcat(this->msg, msg);
	}
	~elections_result_exception () { delete[] msg; }
	virtual const char* what()  const throw() { return msg; }
};

