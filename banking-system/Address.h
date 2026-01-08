#pragma once
#include <string>

namespace Banking {
	struct Address {
		std::string street;
		std::string city;
		std::string postalCode;
		std::string country;
	};
}
