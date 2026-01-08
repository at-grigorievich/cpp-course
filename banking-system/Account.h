#pragma once
#include "Date.h"

namespace Banking {
    enum class AccountType {
        Checking,
        Savings
    };

    class Account {
        int accountNumber;
        int ownerId;
        double balance;
        AccountType type;
        Date openDate;
        bool active;

        static int accountCounter;

    public:
        Account(int ownerId, AccountType type, Date date);

        int getNumber() const;
        int getOwnerId() const;
        double getBalance() const;
        bool isActive() const;

        void deposit(double amount);
        bool withdraw(double amount);
        void close();
    };
}
