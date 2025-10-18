#pragma once

#include <string>
#include "Person.h"

namespace Empleyees {
	class Student : public Person {
		private:
			std::string studentId;
			double averageGrade;
		public:
			Student(std::string id, std::string n, int a, std::string addr);
			~Student();
	};
}
