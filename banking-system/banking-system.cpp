#include <iostream>
#include <limits>
#include "Bank.h"
#include "PremiumClient.h"
#include <windows.h>

using namespace Banking;

void clearInput() {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

Address inputAddress() {
    Address addr;
    std::cout << "Улица и дом: ";
    std::getline(std::cin, addr.street);
    std::cout << "Город: ";
    std::getline(std::cin, addr.city);
    std::cout << "Почтовый индекс: ";
    std::getline(std::cin, addr.postalCode);
    std::cout << "Страна: ";
    std::getline(std::cin, addr.country);
    return addr;
}

Date inputDate() {
    Date d;
    std::cout << "День: "; std::cin >> d.day;
    std::cout << "Месяц: "; std::cin >> d.month;
    std::cout << "Год: "; std::cin >> d.year;
    clearInput();
    return d;
}

void clientMenu(Bank& bank) {
    int choice;
    do {
        std::cout << "\n--- Клиенты ---\n"
            << "1. Добавить обычного клиента\n"
            << "2. Добавить премиум-клиента\n"
            << "3. Показать всех клиентов\n"
            << "0. Назад\n"
            << "Выбор: ";
        std::cin >> choice;
        clearInput();

        if (choice == 1 || choice == 2) {
            std::string fn, ln;

            std::cout << "Имя: ";
            std::getline(std::cin, fn);
            std::cout << "Фамилия: ";
            std::getline(std::cin, ln);

            Address addr = inputAddress();
            Date date = inputDate();

            if (choice == 1) {
                bank.addClient(std::make_unique<Client>(fn, ln, addr, date));
            }
            else {
                int level;
                double discount;
                std::cout << "Уровень: ";
                std::cin >> level;
                std::cout << "Скидка (%): ";
                std::cin >> discount;
                clearInput();

                bank.addClient(std::make_unique<PremiumClient>(
                    fn, ln, addr, date, level, discount));
            }
        }
        else if (choice == 3) {
            bank.printClients();
        }
    } while (choice != 0);
}

void accountMenu(Bank& bank) {
    int choice;
    do {
        std::cout << "\n--- Счета ---\n"
            << "1. Открыть счет\n"
            << "2. Показать все счета\n"
            << "0. Назад\n"
            << "Выбор: ";
        std::cin >> choice;
        clearInput();

        if (choice == 1) {
            int clientId, type;
            std::cout << "ID клиента: ";
            std::cin >> clientId;

            if (bank.findClient(clientId) == nullptr)
            {
                std::cout << "Клиент с таким ID не найден\n";
                clearInput();
                return;
            }

            std::cout << "Тип (0 - расчетный, 1 - сберегательный): ";
            std::cin >> type;
            clearInput();

            Date date = inputDate();
            bank.openAccount(clientId,
                type == 0 ? AccountType::Checking : AccountType::Savings,
                date);
        }
        else if (choice == 2) {
            bank.printAccounts();
        }
    } while (choice != 0);
}

void operationMenu(Bank& bank) {
    int choice;
    do {
        std::cout << "\n--- Операции ---\n"
            << "1. Пополнение\n"
            << "2. Снятие\n"
            << "3. Перевод\n"
            << "0. Назад\n"
            << "Выбор: ";
        std::cin >> choice;
        clearInput();

        if (choice == 1) {
            int acc;
            double sum;
            std::cout << "Номер счета: ";
            std::cin >> acc;

            if (bank.findAccount(acc) == nullptr) {
                std::cout << "Счет не найден\n";
                clearInput();
                return;
            }

            std::cout << "Сумма: ";
            std::cin >> sum;
            clearInput();

            bank.deposit(acc, sum);
        }
        else if (choice == 2) {
            int acc;
            double sum;
            std::cout << "Номер счета: ";
            std::cin >> acc;

            if (bank.findAccount(acc) == nullptr) {
                std::cout << "Счет не найден\n";
                clearInput();
                return;
            }

            std::cout << "Сумма: ";
            std::cin >> sum;
            clearInput();

            bank.withdraw(acc, sum);
        }
        else if (choice == 3) {
            int from, to;
            double sum;
            std::cout << "Счет отправителя: ";
            std::cin >> from;

            if (bank.findAccount(from) == nullptr) {
                std::cout << "Счет отправителя не найден\n";
                clearInput();
                return;
            }

            std::cout << "Счет получателя: ";
            std::cin >> to;

            if (bank.findAccount(to) == nullptr) {
                std::cout << "Счет получателя не найден\n";
                clearInput();
                return;
            }

            std::cout << "Сумма: ";
            std::cin >> sum;
            clearInput();

            Date date = inputDate();
            bank.transfer(from, to, sum, date);
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);      
    SetConsoleOutputCP(1251);

    Bank bank;
    int choice;

    do {
        std::cout << "\n=== БАНКОВСКАЯ СИСТЕМА ===\n"
            << "1. Клиенты\n"
            << "2. Счета\n"
            << "3. Операции\n"
            << "4. Отчет\n"
            << "0. Выход\n"
            << "Выбор: ";
        std::cin >> choice;
        clearInput();

        switch (choice) {
        case 1: clientMenu(bank); break;
        case 2: accountMenu(bank); break;
        case 3: operationMenu(bank); break;
        case 4: bank.printReport(); break;
        }
    } while (choice != 0);

    return 0;
}

