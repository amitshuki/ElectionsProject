#pragma once
#include <iostream>
using namespace std;
class file_open_exception :
    public exception
{
private:
	char* msg;
public:
	file_open_exception() {
		msg = new char[50];
		sprintf(msg, "File opening error.");
	}
	file_open_exception(const char* name_of_file) {
		this->msg = new char[100];
		sprintf(this->msg, "Failed to open file: ");
		strcat(this->msg, name_of_file);
	}
	~file_open_exception() { delete[] msg; }
	virtual const char* what()  const throw() { return msg; }
};

