#pragma once
#include <iostream>
using namespace std;
class no_entity_error:
	public exception
{
private:
	string msg;
public:
	no_entity_error() {
		msg += "Enitity does not exist.";
	}
	no_entity_error(const char* entity_type) {
		msg += entity_type;
		msg += " does not exist.";
	}
	no_entity_error(const char* entity_type, const char* in_what_class) {
		msg += entity_type;
		msg += " does not exist in ";
		msg += in_what_class;
	}
	~no_entity_error() = default;
	virtual const char* what()  const throw() { return this->msg.data(); }
};
