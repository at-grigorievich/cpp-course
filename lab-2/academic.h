#pragma once

#include <string>

namespace academics {
	class person {
	protected:
		std::string name;
		int age;
		std::string address;

	public:
		person(std::string _name, int _age, std::string _addr)
			: name(_name), age(_age), address(_addr) {}

		virtual void displayInfo() const;
		virtual ~person() = default;
	};

	class student : public person {
	private:
		std::string studentId;
		double averageGrade;
	public:
		student(std::string _name, int _age, std::string _addr, std::string _studId, double _avgGrade)
			: person(_name, _age, _addr), studentId(_studId), averageGrade(_avgGrade) {}

		void displayInfo() const override;
		void setAverageGrade(double newAvgGrade);
	};

	class professor : public person {
	private:
		std::string department;
		double salary;
		int yearsOfExperience;
	public:
		professor(std::string _name, int _age, std::string _addr, std::string _department, double _salary, int _yearsOfExp)
			: person(_name, _age, _addr), department(_department), salary(_salary), yearsOfExperience(_yearsOfExp) {}

		void displayInfo() const override;
		double calculateExperienceBonus(double expMultiply) const;
	};

}
