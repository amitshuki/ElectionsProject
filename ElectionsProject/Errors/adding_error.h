#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <string>
//Hello
using namespace std;
class adding_error :
	public exception
{
private:
	string msg;
public:
	adding_error(const char* entity) {
		this->msg += "Could not add ";
		this->msg += entity;
	}
	adding_error(const char* entity1,const char* entity2) {
		this->msg += "Could not add ";
		this->msg += entity1;
		this->msg += " to ";
		this->msg += entity1;

	}
	~adding_error() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};


