#include "contact.hpp"
#include "phone.hpp"
#include <iomanip> // для setw


std::string input_handler(const std::string& prompt) {
	std::string input;
	std::cout << prompt << ": ";
	std::getline(std::cin, input);

	if (std::cin.eof()){
		std::cout << "You pressed Ctrl-D" << std::endl;
		exit(0);
	}
	return input;
}

std::string number_checker(){
	std::string phoneNumber = "";
	while (true)
	{
		phoneNumber = input_handler("Enter phone number");
		bool valid = true;
		for (size_t i = 0; i < phoneNumber.length(); i++) {
			if (!isdigit(phoneNumber[i])) {
				valid = false;
				break;
			}
		}

		if (!valid) {
			std::cout << "Phone number must contain only digits!\n";
		}
		else
			break;
	}
	return phoneNumber;
}

int add_cmd(PhoneBook *pb) {
	std::string firstName = input_handler("Enter first name");
	std::string lastName = input_handler("Enter last name");
	std::string nickname = input_handler("Enter nickname");
	std::string phoneNumber = number_checker();
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


void cmd_checker(const std::string& input, PhoneBook *pb) {
	if (input == "ADD")
		add_cmd(pb);
	else if (input == "SEARCH")
		pb->SEARCH();
	else
		std::cout << "Invalid command" << std::endl;
}

int main() {
	std::string input;
	PhoneBook pb;

	while (true) {
		std::cout << "Enter command (add, search, exit)> ";
		std::getline(std::cin, input);

		if (std::cin.eof()){
			std::cout << "You presed Ctrl-D" << std::endl;
			exit(0);
		}
		if (input == "EXIT")
			break;

		cmd_checker(input, &pb);
	}

	return 0;
}