#include "Account.h"

namespace Banking {
    int Account::accountCounter = 1000;

    Account::Account(int owner, AccountType t, Date date)
        : accountNumber(++accountCounter),
        ownerId(owner),
        balance(0.0),
        type(t),
        openDate(date),
        active(true) {
    }

    int Account::getNumber() const { return accountNumber; }
    int Account::getOwnerId() const { return ownerId; }
    double Account::getBalance() const { return balance; }
    bool Account::isActive() const { return active; }

    void Account::deposit(double amount) {
        if (amount > 0)
            balance += amount;
    }

    bool Account::withdraw(double amount) {
        if (amount <= 0 || amount > balance)
            return false;
        balance -= amount;
        return true;
    }

    void Account::close() {
        if (balance == 0)
            active = false;
    }
}