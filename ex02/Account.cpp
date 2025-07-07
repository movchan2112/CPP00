#include "Account.hpp"
#include <iostream>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account()
	: _accountIndex(_nbAccounts), _amount(0), _nbDeposits(0), _nbWithdrawals(0) {
		_nbAccounts++;

		_displayTimestamp();
		std::cout	<< "index:" << this->_accountIndex
					<< ";amount:" << this->_amount
					<< ";created" << std::endl;
	};

Account::Account( int initial_deposit )
	: _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
		_nbAccounts++;
		_totalAmount += initial_deposit;

		_displayTimestamp();
		std::cout	<< "index:" << this->_accountIndex
					<< ";amount:" << this->_amount
					<< ";created" << std::endl;
	};

Account::~Account(){
		_displayTimestamp();
		std::cout	<< "index:" << this->_accountIndex
					<< ";amount:" << this->_amount
					<< ";closed" << std::endl;
	_nbAccounts--;
	_totalAmount -= _amount;
};


int Account::getNbAccounts(){
	return _nbAccounts;
};

int Account::getTotalAmount(){
	return _totalAmount;
};

int Account::getNbDeposits(){
	return _totalNbDeposits;
};

int Account::getNbWithdrawals(){
	return _totalNbWithdrawals;
};

void Account::makeDeposit(int deposit) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex
              << ";p_amount:" << this->_amount
              << ";deposit:" << deposit;

    this->_amount += deposit;
    this->_nbDeposits++;
    _totalAmount += deposit;
    _totalNbDeposits++;

    std::cout << ";amount:" << this->_amount
              << ";nb_deposits:" << this->_nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
    _displayTimestamp();
    std::cout << "index:" << this->_accountIndex
              << ";p_amount:" << this->_amount
              << ";withdrawal:";

    if (withdrawal > this->_amount) {
        std::cout << "refused" << std::endl;
        return false;
    }

    this->_amount -= withdrawal;
    this->_nbWithdrawals++;
    _totalAmount -= withdrawal;
    _totalNbWithdrawals++;

    std::cout << withdrawal
              << ";amount:" << this->_amount
              << ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    return true;
}

int Account::checkAmount(void) const{
	return this->_amount;
}

void Account::_displayTimestamp( void ) {
	std::time_t result = std::time(nullptr);
	char buffer[20];
	
	// Форматируем время в строку [ГГГГММДД_ЧЧММСС]
	std::strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S]", std::localtime(&result));
	
	std::cout << buffer;
}

// Публичный статический метод для вывода информации о счетах
void Account::displayAccountsInfos( void ) {
	// Сначала выводим временную метку
	_displayTimestamp();
	
	// Затем выводим все статические данные
	std::cout << " accounts:" << getNbAccounts() << ";"
			  << "total:" << getTotalAmount() << ";"
			  << "deposits:" << getNbDeposits() << ";"
			  << "withdrawals:" << getNbWithdrawals() << std::endl;
}

void Account::displayStatus( void ) const {
	_displayTimestamp(); // Используем уже созданную функцию для временной метки
	
	std::cout << " index:" << this->_accountIndex << ";"
			  << "amount:" << this->_amount << ";"
			  << "deposits:" << this->_nbDeposits << ";"
			  << "withdrawals:" << this->_nbWithdrawals << std::endl;
}