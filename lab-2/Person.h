#pragma once

#include <string>

namespace Empleyees
{
	class Person {
		protected:
			std::string name;
			int age;
			std::string address;

		public:
			Person(std::string _name, int _age, std::string _addr);
			virtual ~Person();

			virtual void displayInfo() const;
	};
}