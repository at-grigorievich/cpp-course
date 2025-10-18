#include "Person.h"
#include <iostream>

namespace Empleyees {
	Person::Person(std::string _name, int _age, std::string _addr) : name(_name), age(_age), address(_addr) {}
	Person::~Person() {}

	void Person::displayInfo() const {
		std::cout << "Имя: " << name << ", Возраст: " << age << ", Адрес: " << address << std::endl;
	}
}