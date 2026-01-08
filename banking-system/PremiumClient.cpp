#include "PremiumClient.h"
#include <iostream>

namespace Banking {
    PremiumClient::PremiumClient(std::string fn, std::string ln, Address addr, Date date, int lvl, double discount)
        : Client(fn, ln, addr, date), level(lvl), discountPercent(discount) {
    }

    double PremiumClient::getDiscount() const {
        return discountPercent;
    }

    void PremiumClient::printInfo() const {
        std::cout << "Премиум клиент #" << id << ": "
            << getFullName()
            << " | Уровень: " << level
            << " | Скидка: " << discountPercent << "%\n";
    }
}
