#include "Bank.h"
#include <iostream>

namespace Banking {
    void Bank::addClient(std::unique_ptr<Client> client) {
        clients.push_back(std::move(client));
    }

    Client* Bank::findClient(int id) {
        for (auto& c : clients)
            if (c->getId() == id)
                return c.get();
        return nullptr;
    }

    Account* Bank::openAccount(int clientId, AccountType type, Date date) {
        if (!findClient(clientId)) {
            std::cout << "Ошибка: клиент с ID "
                << clientId << " не найден\n";
            return nullptr;
        }

        accounts.emplace_back(clientId, type, date);
        return &accounts.back();
    }

    Account* Bank::findAccount(int number) {
        for (auto& acc : accounts)
            if (acc.getNumber() == number)
                return &acc;
        return nullptr;
    }

    void Bank::transfer(int from, int to, double amount, Date date) {
        Account* a = findAccount(from);
        Account* b = findAccount(to);

        if (!a || !b || !a->withdraw(amount))
            return;

        b->deposit(amount);
        transactions.emplace_back(from, to, amount, "Transfer", date);
    }

    void Bank::printReport() const {
        std::cout << "Клиенты: " << clients.size() << std::endl;
        std::cout << "Счета: " << accounts.size() << std::endl;
        std::cout << "Транзакции: " << transactions.size() << std::endl;
    }

    void Bank::printClients() const {
        for (const auto& c : clients)
            c->printInfo();
    }

    void Bank::printAccounts() const {
        for (const auto& a : accounts)
            std::cout << "Аккаунт #" << a.getNumber()
            << " Баланс: " << a.getBalance() << std::endl;
    }

    void Bank::deposit(int acc, double sum) {
        Account* a = findAccount(acc);
        if (a) a->deposit(sum);
    }

    void Bank::withdraw(int acc, double sum) {
        Account* a = findAccount(acc);
        if (a && !a->withdraw(sum))
            std::cout << "Недостаточно средств\n";
    }
}
