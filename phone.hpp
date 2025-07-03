#ifndef PHONE_HPP
#define PHONE_HPP

#include <iomanip>
#include "contact.hpp"
const int len = 8;

class PhoneBook{
private:
	Contact contacts[len];
	int _count;
	int _index;
public:
	PhoneBook();
	~PhoneBook();

	void ADD(const Contact &count);
	void SEARCH();
	
	std::string rightSize(std::string str);

};


#endif