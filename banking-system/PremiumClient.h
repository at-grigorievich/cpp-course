#pragma once
#include "Client.h"

namespace Banking {
    class PremiumClient : public Client {
        int level;
        double discountPercent;

    public:
        PremiumClient(std::string fn, std::string ln, Address addr, Date date,
            int level, double discount);

        void printInfo() const override;
        double getDiscount() const;
    };
}