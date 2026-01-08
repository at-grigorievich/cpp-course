#include "Transaction.h"
#include <iostream>

namespace Banking {
    int Transaction::transactionCounter = 0;

    Transaction::Transaction(int from, int to, double amt, std::string t, Date d)
        : id(++transactionCounter),
        fromAccount(from),
        toAccount(to),
        amount(amt),
        type(t),
        date(d) {
    }

    void Transaction::print() const {
        std::cout << "Transaction #" << id
            << " [" << type << "] "
            << amount << std::endl;
    }
}
