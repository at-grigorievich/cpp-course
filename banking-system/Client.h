#pragma once
#include <string>
#include "Address.h"
#include "Date.h"

namespace Banking {
	class Client {
	protected:
		int id;
		std::string firstName;
		std::string lastName;
		Address address;
		Date registrationDate;

		static int clientCounter;

	public:
		Client();
		Client(std::string fn, std::string ln, Address addr, Date date);
		virtual ~Client();

		int getId() const;
		std::string getFullName() const;
		Address getAddress() const;

		void setAddress(const Address& addr);

		static int getClientCount();

		virtual void printInfo() const;
	};
}