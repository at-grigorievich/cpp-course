#include "persons.h"
#include <iostream>

namespace multiple_persons {
	//PERSON IMPLEMENT
	void person::display() const {
		std::cout << "Имя: " << name << ", Возраст: " << age << std::endl;
	}

	//EMPLOYEE IMPLEMENT
	void employee::work() const {
		std::cout << "Выполняет работу как сотрудник" << std::endl;
	}

	//TEACHER IMPLEMENT
	void teacher::display() const {
		std::cout << "Учитель: " << name
			<< ", Возраст: " << age
			<< ", Должность: " << position
			<< ", Зарплата: " << salary
			<< ", Предмет: " << subject
			<< ", Опыт: " << experienceYears << " лет" << std::endl;
	}

	void teacher::work() const {
		std::cout << name << " преподает предмет: " << subject << std::endl;
	}

	void teacher::holdLesson() const {
		std::cout << name << " проводит урок по предмету " << subject << std::endl;
	}
	
	//RESEARCHER IMPLEMENT
	void researcher::conductResearch() const {
		std::cout << "Проводит исследования в области: " << researchArea
			<< ", количество публикаций: " << publicationsCount << std::endl;
	}

	//PROFESSOR IMPLEMENT
	void professor::display() const {
		std::cout << "Профессор: " << name
			<< ", Возраст: " << age
			<< ", Предмет: " << subject
			<< ", Область исследований: " << researchArea
			<< ", Публикаций: " << publicationsCount << std::endl;
	}

	void professor::work() const {
		std::cout << name << " преподает и проводит научные исследования" << std::endl;
	}

	void professor::guideStudents() const {
		std::cout << name << " руководит студентами в области " << researchArea << std::endl;
	}
}