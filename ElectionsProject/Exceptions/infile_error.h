#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;
class infile_error :
	public exception
{
private:
	string msg;
public:
	infile_error() {
		this->msg.append("Error reading from file.");
	}
	infile_error(const char* entity) {
		this->msg.append("Error reading from file in class ");
		this->msg.append(entity);
		this->msg += ".";
	}
	~infile_error() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};

