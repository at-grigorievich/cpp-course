#include "Client.h"
#include <iostream>

namespace Banking {
    int Client::clientCounter = 0;

    Client::Client() : id(++clientCounter) {}

    Client::Client(std::string fn, std::string ln, Address addr, Date date)
        : id(++clientCounter), firstName(fn), lastName(ln), address(addr), registrationDate(date) {
    }

    Client::~Client() {}

    int Client::getId() const { return id; }

    std::string Client::getFullName() const {
        return firstName + " " + lastName;
    }

    Address Client::getAddress() const { return address; }

    void Client::setAddress(const Address& addr) {
        address = addr;
    }

    int Client::getClientCount() {
        return clientCounter;
    }

    void Client::printInfo() const {
        std::cout << "Клиент #" << id << ": " << getFullName() << std::endl;
    }
}