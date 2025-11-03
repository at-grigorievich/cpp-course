#include "academic.h"
#include <iostream>

namespace academics {
	//PERSON IMPLEMENT
	void person::displayInfo() const {
		std::cout << "ФИО: " << name << "; "
			<< "Возраст: " << age << "; "
			<< "Адрес: " << address << "; " << std::endl;
	}

	// STUDENT IMPLEMENT
	void student::displayInfo() const {
		std::cout << "Информация о студенте: " << std::endl;
		person::displayInfo();
		std::cout << "ID студента " << studentId << "; "
			<< "Средняя оценка: " << averageGrade << "; " << std::endl;
	}

	void student::setAverageGrade(double newAvgGrade) {
		averageGrade = newAvgGrade;
		std::cout << "Оценка для студента " << name << " обновлена" << std::endl;
	}

	//PROFESSOR IMPLEMENT
	void professor::displayInfo() const {
		std::cout << "Информация о профессоре: " << std::endl;
		person::displayInfo();
		std::cout << "Департамент: " << department << "; "
			<< "Зарплата: " << salary << "; " 
			<< "Стаж: " << yearsOfExperience << "лет; " << std::endl;
	}

	double professor::calculateExperienceBonus(double expMultiply) const {
		return expMultiply * yearsOfExperience;
	}
}