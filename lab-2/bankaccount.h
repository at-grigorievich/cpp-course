#pragma once
#include <string>

namespace staticbank {
	class bankaccount {
	private:
		std::string accountNumber;
		std::string ownerName;
		double balance;
		const double MIN_BALANCE = 10.0;

		static int totalAccounts;
		static int totalBankBalance;
	public:
		bankaccount(std::string _accountNumber, std::string _ownerName, double initialBalance);
		~bankaccount();

		void deposit(double amount);
		bool withdraw(double amount);
		void displayAccountInfo() const;

		static int getTotalAccounts();
		static double getTotalBankBalance();
		static double getAverageBalance();
	};
}
