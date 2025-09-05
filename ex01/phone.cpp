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

void PhoneBook::SEARCH() {
    if (_count == 0) {
        std::cout << "No contacts yet!" << std::endl;
        return;
    }

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "|" << std::setw(10) << "Index"     << "|"
              << std::setw(10) << "FirstName" << "|"
              << std::setw(10) << "LastName"  << "|"
              << std::setw(10) << "Nickname"  << "|" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for (int i = 0; i < _count; ++i) {
        std::cout << "|" << std::setw(10) << (i + 1) << "|"
                  << std::setw(10) << rightSize(contacts[i].getFirstName()) << "|"
                  << std::setw(10) << rightSize(contacts[i].getLastName())  << "|"
                  << std::setw(10) << rightSize(contacts[i].getNickname())  << "|" 
                  << std::endl;
    }

    std::cout << "Enter index to view full info: ";
    std::string idx_str;
    if (!std::getline(std::cin, idx_str)) {
        std::cout << "Input error." << std::endl;
        return;
    }

    // убираем пробелы в начале и в конце
    size_t l = idx_str.find_first_not_of(" \t");
    size_t r = idx_str.find_last_not_of(" \t");
    if (l == std::string::npos) {
        std::cout << "Invalid index." << std::endl;
        return;
    }
    idx_str = idx_str.substr(l, r - l + 1);

    // проверяем, что строка состоит только из цифр
    for (size_t i = 0; i < idx_str.length(); i++) {
        if (!isdigit(idx_str[i])) {
            std::cout << "Index must be a number." << std::endl;
            return;
        }
    }

    int idx = atoi(idx_str.c_str()) - 1; // приводим к int и делаем 0-based
    if (idx < 0 || idx >= _count) {
        std::cout << "Index out of range (1.." << _count << ")." << std::endl;
        return;
    }

    contacts[idx].printFull();
}
