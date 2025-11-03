#include "bankaccount.h"
#include <iostream>

namespace staticbank {
	int bankaccount::totalAccounts = 0;
	int bankaccount::totalBankBalance = 0.0;

	bankaccount::bankaccount(std::string _accountNumber, std::string _ownerName, double initialBalance) :
		accountNumber(_accountNumber), ownerName(_ownerName), balance(initialBalance) 
	{
		totalAccounts++;
		totalBankBalance += balance;
	}

	bankaccount::~bankaccount() {
		totalAccounts--;
		totalBankBalance -= balance;
	}

	void bankaccount::deposit(double amount) {
		if (amount > 0) {
			balance += amount;
			totalBankBalance += amount;
		}
	}

	bool bankaccount::withdraw(double amount) {
		if (amount > 0 && balance - amount >= MIN_BALANCE) {
			balance -= amount;
			totalBankBalance -= amount;
			return true;
		}
		else {
			std::cout << "Недостаточно средств для снятия (минимальный баланс "
				<< MIN_BALANCE << ")" << std::endl;
			return false;
		}
	}

	void bankaccount::displayAccountInfo() const {
		std::cout << "Счет: " << accountNumber << ", Владелец: " << ownerName
			<< ", Баланс: " << balance << std::endl;
	}

	int bankaccount::getTotalAccounts() {
		return totalAccounts;
	}

	double bankaccount::getTotalBankBalance() {
		return totalBankBalance;
	}

	double bankaccount::getAverageBalance() {
		if (totalAccounts == 0) return 0.0;
		return totalBankBalance / totalAccounts;
	}
}