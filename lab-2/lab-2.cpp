#include <iostream>
#include "student.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    // Тестирование класса Student
    Student::student student("Иван Иванов", 20);

    // Установка оценок
    student.setGraduate(0, 5);
    student.setGraduate(1, 4);
    student.setGraduate(2, 5);
    student.setGraduate(3, 3);
    student.setGraduate(4, 4);

    student.displayInfo();

    if (student.hasScholarShip()) {
        std::cout << "Студент получает стипендию" << std::endl;
    }
    else {
        std::cout << "Стипендия не назначена" << std::endl;
    }

    return 0;
}
