#pragma once
#include <iostream>
using namespace std;
class connection_error :
	public exception
{
private:
	string msg;
public:
	connection_error(const char* entity1, const char* entity2) {
		this->msg += "Could not connect ";
		this->msg.append(entity1);
		this->msg += " to ";
		this->msg.append(entity2);
	}
	~connection_error() = default;
	virtual const char* what()  const throw() { return msg.data(); }
};


