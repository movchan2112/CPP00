#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

class Contact {
private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickname;
    std::string _phoneNumber;
    std::string _darkestSecret;

public:
    Contact();
    Contact(const std::string& firstName, const std::string& lastName,
            const std::string& nickname, const std::string& phoneNumber,
            const std::string& darkestSecret);
    Contact(const Contact& other);
    Contact& operator=(const Contact& other);
    ~Contact();

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getNickname() const;
    std::string getPhoneNumber() const;
    std::string getDarkestSecret() const;

    void printFull() const;
};

#endif