#include <iostream>
#include <string>
#include <cstring>

#include <iostream>
#include <string>
#include <iostream>
#include <string>

class Contact {
private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickname;
    std::string _phoneNumber;
    std::string _darkestSecret;

public:
    Contact() 
        : _firstName(""), _lastName(""), _nickname(""), _phoneNumber(""), _darkestSecret("") {}

    Contact(const std::string& firstName, const std::string& lastName,
            const std::string& nickname, const std::string& phoneNumber,
            const std::string& darkestSecret)
        : _firstName(firstName), _lastName(lastName), _nickname(nickname),
          _phoneNumber(phoneNumber), _darkestSecret(darkestSecret) {}

    Contact(const Contact& other)
        : _firstName(other._firstName), _lastName(other._lastName),
          _nickname(other._nickname), _phoneNumber(other._phoneNumber),
          _darkestSecret(other._darkestSecret) {}

    Contact& operator=(const Contact& other) {
        if (this != &other) {
            _firstName = other._firstName;
            _lastName = other._lastName;
            _nickname = other._nickname;
            _phoneNumber = other._phoneNumber;
            _darkestSecret = other._darkestSecret;
        }
        return *this;
    }

    // Геттеры для вывода полей
    std::string getFirstName() const { return _firstName; }
    std::string getLastName() const { return _lastName; }
    std::string getNickname() const { return _nickname; }
    std::string getPhoneNumber() const { return _phoneNumber; }
    std::string getDarkestSecret() const { return _darkestSecret; }

    void printFull() const {
        std::cout << "First Name: " << _firstName << std::endl;
        std::cout << "Last Name: " << _lastName << std::endl;
        std::cout << "Nickname: " << _nickname << std::endl;
        std::cout << "Phone Number: " << _phoneNumber << std::endl;
        std::cout << "Darkest Secret: " << _darkestSecret << std::endl;
    }

    ~Contact() {
        // std::string освобождается автоматически
    }
};


#include <iostream>
#include <iomanip> // для setw

class PhoneBook {
private:
    Contact contacts[8];
    int _count;          // Сколько реально добавлено
    int _index;          // Текущий индекс для замены

public:
    PhoneBook() : _count(0), _index(0) {}

    void ADD(const Contact &cont) {
        contacts[_index] = cont;
        _index = (_index + 1) % 8; // кольцевой буфер

        if (_count < 8)
            _count++;
    }

    void SEARCH() {
        if (_count == 0) {
            std::cout << "No contacts yet!" << std::endl;
            return;
        }

        // Заголовок таблицы
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "|" << std::setw(10) << "Index" << "|"
          << std::setw(10) << "FirstName" << "|"
          << std::setw(10) << "LastName" << "|"
          << std::setw(10) << "Nickname" << "|" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;


        for (int i = 0; i < _count; i++) {
            std::cout << std::setw(10) << i + 1 << "|"
                      << std::setw(10) << truncate(contacts[i].getFirstName()) << "|"
                      << std::setw(10) << truncate(contacts[i].getLastName()) << "|"
                      << std::setw(10) << truncate(contacts[i].getNickname()) << std::endl;
        }

        std::cout << "Enter index to view full info: ";
        std::string idx_str;
        std::getline(std::cin, idx_str);

        int idx = std::atoi(idx_str.c_str());

        if (idx < 1 || idx > _count) {
            std::cout << "Invalid index!" << std::endl;
            return;
        }

        contacts[idx - 1].printFull();
    }

    // Функция для обрезки текста до 10 символов с точкой
    std::string truncate(std::string str) {
        if (str.length() > 10)
            return str.substr(0, 9) + ".";
        return str;
    }
};


// 💬 Новый input_handler
std::string input_handler(const std::string& prompt) {
    std::string input;
    std::cout << prompt << ": ";
    std::getline(std::cin, input);
    return input;
}
int add_cmd(PhoneBook *pb) {
    std::string firstName = input_handler("Enter first name");
    std::string lastName = input_handler("Enter last name");
    std::string nickname = input_handler("Enter nickname");
    std::string phoneNumber = input_handler("Enter phone number");
    std::string darkestSecret = input_handler("Enter darkest secret");

    // Проверяем, что все поля не пустые
    if (firstName.empty() || lastName.empty() || nickname.empty() || 
        phoneNumber.empty() || darkestSecret.empty()) {
        std::cout << "All fields must be filled!\n";
        return 1;
    }

    // Проверяем, что телефон состоит только из цифр
    bool valid = true;
    for (size_t i = 0; i < phoneNumber.length(); i++) {
        if (!isdigit(phoneNumber[i])) {
            valid = false;
            break;
        }
    }

    if (!valid) {
        std::cout << "Phone number must contain only digits!\n";
        return 1;
    }

    // Создаем контакт
    Contact ct(firstName, lastName, nickname, phoneNumber, darkestSecret);
    pb->ADD(ct);

    std::cout << "Contact added!\n";
    return 0;
}


int cmd_checker(const std::string& input, PhoneBook *pb) {
    if (input == "add") {
        add_cmd(pb);
        return 1;
    } else if (input == "search") {
        pb->SEARCH();
        return 1;
    }
    else{
        std::cout << "Invalid command" << std::endl;
    }
    return 0;
}

int main() {
    std::string input;
    PhoneBook pb;

    while (true) {
        std::cout << "Enter command (add, search, exit)> ";
        std::getline(std::cin, input);

        if (input == "exit")
            break;

        cmd_checker(input, &pb);
    }

    return 0;
}
