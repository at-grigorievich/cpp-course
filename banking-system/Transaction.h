#pragma once
#include <string>
#include "Date.h"

namespace Banking {
    class Transaction {
        int id;
        int fromAccount;
        int toAccount;
        double amount;
        std::string type;
        Date date;

        static int transactionCounter;

    public:
        Transaction(int from, int to, double amount, std::string type, Date date);
        void print() const;
    };
}
