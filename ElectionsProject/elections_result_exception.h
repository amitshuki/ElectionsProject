#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;
class elections_result_exception :
    public exception
{
private:
	string msg;
public:
	elections_result_exception () {
		this->msg.append("Unable to calculate results.");
	}
	elections_result_exception(const char* msg) {
		this->msg.append("Unable to calculate results: ");
		this->msg.append(msg);
	}
	~elections_result_exception() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};

