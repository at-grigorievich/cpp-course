#pragma once

#include <string>
#include <vector>

class student {
	private: 
		std::string fullname;
		int age;
		double meanGraduate;
		std::vector<int> graduates;
	public:
		student(std::string _fullname, int _age);
		virtual ~student() = default;

		std::string getFullName() const;
		int getAge() const;
		double getMeanGraduate() const;
		const int* getGraduates() const;

		void setFullname(std::string newFullName);
		void setAge(int newAge);
		void setGraduate(int idx, int graduate);

		double calculateMeanGraduate();
		void displayInfo();
		bool hasScholarShip();
};	