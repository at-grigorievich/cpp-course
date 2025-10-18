#include <stdexcept>
#include "student.h"
#include <iostream>

student::student(std::string _fullname, int _age) {
	fullname = _fullname;
	age = _age;
	meanGraduate = 0;
	graduates.resize(5, 0);
}

std::string student::getFullName() const {
	if (fullname.length() == 0)
		throw std::runtime_error("fullname is empty");
	return fullname;
}

int student::getAge() const {
	if (age <= 0)
		throw std::runtime_error("age is incorrect");
	return age;
}

double student::getMeanGraduate() const {
	if (meanGraduate < 0)
		throw std::runtime_error("mean graduate is incorrect");
	return meanGraduate;
}

const int* student::getGraduates() const {
	if (graduates.empty()) return nullptr;
	return graduates.data();
}

void student::setFullname(std::string newFullname) {
	if (newFullname.length() == 0) return;

	fullname = newFullname;
}

void student::setAge(int newAge) {
	if (newAge <= 0) return;
	age = newAge;
}

void student::setGraduate(int idx, int graduate) {
	if (graduate <= 0 || graduate > 5)
		return;

	if (idx < 0 || idx >= 5)
		return;

	graduates[idx] = graduate;
}

double student::calculateMeanGraduate() {
	int size = 5;
	meanGraduate = 0;
	for (int i = 0; i < 5; i++) {
		meanGraduate += graduates[i];
	}

	meanGraduate /= 5;
	return meanGraduate;
}

void student::displayInfo() {
	std::cout << "ФИО: " << fullname << std::endl;
	std::cout << "Полных лет: " << age << std::endl;

	std::cout << "Оценки: ";
	for (int i = 0; i < 5; i++) {
		std::cout << graduates[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Средний балл: " << calculateMeanGraduate() << std::endl;
	std::cout << "-*************************-" << std::endl;
}

bool student::hasScholarShip() {
	double meanGraduate = calculateMeanGraduate();
	return meanGraduate >= 4.5;
}
