#pragma once
#include <vector>
#include <memory>
#include "Client.h"
#include "Account.h"
#include "Transaction.h"

namespace Banking {
    class Bank {
        std::vector<std::unique_ptr<Client>> clients;
        std::vector<Account> accounts;
        std::vector<Transaction> transactions;

    public:
        void addClient(std::unique_ptr<Client> client);
        Client* findClient(int id);

        Account* openAccount(int clientId, AccountType type, Date date);
        Account* findAccount(int number);

        void transfer(int from, int to, double amount, Date date);
        void printReport() const;

        void printClients() const;
        void printAccounts() const;
        void deposit(int acc, double sum);
        void withdraw(int acc, double sum);
    };
}