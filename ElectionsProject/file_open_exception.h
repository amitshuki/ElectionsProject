#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
using namespace std;
class file_open_exception :
    public exception
{
private:
	string msg;
public:
	file_open_exception() {
		this->msg += "File opening error.";
	}
	file_open_exception(const char* name_of_file) {
		this->msg += "Failed to open file: ";
		this->msg.append(name_of_file);
	}
	~file_open_exception() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};

