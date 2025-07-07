#include "contact.hpp"
#include "phone.hpp"

PhoneBook::PhoneBook()
    : _count(0), _index(0) {};

PhoneBook::~PhoneBook(){};

void PhoneBook::ADD(const Contact &cont){
    contacts[_index] = cont;
    _index = (_index + 1) % len;

    if(_count < len)
        _count++;
}

std::string PhoneBook::rightSize(std::string str){
    if(str.length() > 10)
        return str.substr(0,9) + ".";
    return str;
}

void PhoneBook::SEARCH(){
    if(_count == 0){
        std::cout << "No contacts yet!" << std::endl;
        return;
    }

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "|" << std::setw(10) << "Index" << "|"
        << std::setw(10) << "FirstName" << "|"
        << std::setw(10) << "LastName" << "|"
        << std::setw(10) << "Nickname" << "|" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for (int i = 0; i < _count; i++) {
            std::cout << std::setw(10) << i + 1 << "|"
                      << std::setw(10) << rightSize(contacts[i].getFirstName()) << "|"
                      << std::setw(10) << rightSize(contacts[i].getLastName()) << "|"
                      << std::setw(10) << rightSize(contacts[i].getNickname()) << std::endl;
        }
    
    std::cout << "Enter index to view full info: ";
    std::string idx_str;
    std::getline(std::cin, idx_str);

    int idx = atoi(idx_str.c_str()-1);

    contacts[idx].printFull();

}
