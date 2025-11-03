#include <iostream>
#include "student.h"
#include "academic.h"
#include "shape.h"
#include "vehicle.h"
#include "library.h"
#include "bankaccount.h"

void showFirstTask();
void showSecondTask();
void showThirdTask();
void showFourthTask();
void showFifthTask();
void showSixthTask();

int main()
{
    setlocale(LC_ALL, "Russian");

    //showFirstTask();
    //showSecondTask();
    //showThirdTask();
    //showFourthTask();
    //showFifthTask();
    showSixthTask();

    return 0;
}

void showFirstTask() {
    // Тестирование класса Student
    students::student student("Иван Иванов Иванович", 20);

    // Установка оценок
    student.setGraduate(0, 5);
    student.setGraduate(1, 4);
    student.setGraduate(2, 5);
    student.setGraduate(3, 5);
    student.setGraduate(4, 4);

    student.displayInfo();

    if (student.hasScholarShip()) {
        std::cout << "Студент получает стипендию" << std::endl;
    }
    else {
        std::cout << "Стипендия не назначена" << std::endl;
    }
}

void showSecondTask() {
    // Тестирование иерархии классов
    academics::student student("Петр Петров", 20, "ул. Студенческая, 15", "S12345", 4.3);
    academics::professor prof("Доктор Иванов", 45, "ул. Академическая, 10", "Компьютерные науки", 50000, 15);

    student.displayInfo();
    prof.displayInfo();
}

void showThirdTask() {
    std::vector<shapes::shape*> shapes;
    shapes.push_back(new shapes::circle("Красный", 5.0));
    shapes.push_back(new shapes::rectangle("Синий", 4.0, 6.0));
    shapes.push_back(new shapes::triangle("Зеленый", 3.0, 4.0, 5.0));

    for (shapes::shape* shape : shapes) {
        shape->displayInfo();
        shape->draw();
        std::cout << std::endl;
    }

    for (auto shape : shapes) {
        delete shape;
    }
}

void showFourthTask() {
    std::vector<vehicles::vehicle*> vehicles;

    vehicles.push_back(new vehicles::car("Chipovanaya", "Devyatka", 12412124, 4, "HZ"));
    vehicles.push_back(new vehicles::motorcycle("Ява", "228", 2022, true));

    for (auto v : vehicles) {
        v->displayInfo();
        v->startEngine();
        v->refuel(10);
        v->stopEngine();
        std::cout << std::endl;
    }

    dynamic_cast<vehicles::motorcycle*>(vehicles[1])->wheelie(); // даункаст чтобы вызвать метод мотоцикла

    for (auto v : vehicles) delete v;
}

void showFifthTask() {
    librarybooks::library lib("Городская библиотека", "ул. Ленина, 10");

    librarybooks::book b1("1984", "Джордж Оруэлл", "1234567890", 1949);
    librarybooks::book b2("Мастер и Маргарита", "Михаил Булгаков", "0987654321", 1967);
    librarybooks::book b3("Преступление и наказание", "Фёдор Достоевский", "1122334455", 1866);

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addBook(b3);

    lib.displayAllBooks();
    std::cout << std::endl;

    std::cout << "Попытка взять книгу '1984': "
        << (lib.borrowBook("1234567890") ? "успешно" : "не удалось") << std::endl;

    lib.displayAvailableBooks();
    std::cout << std::endl;


    std::cout << "Возвращаем книгу '1984': " << std::endl;
    lib.returnBook("1234567890");

    lib.displayAvailableBooks();
}

void showSixthTask() {
    staticbank::bankaccount acc1("1", "Иван Иванов", 500.0);
    staticbank::bankaccount acc2("2", "Петр Петров", 1000.0);
    staticbank::bankaccount acc3("3", "Мария Сидорова", 50.0);

    acc1.displayAccountInfo();
    acc2.displayAccountInfo();
    acc3.displayAccountInfo();

    std::cout << "Общее количество счетов: " << staticbank::bankaccount::getTotalAccounts() << std::endl;
    std::cout << "Общий баланс банка: " << staticbank::bankaccount::getTotalBankBalance() << std::endl;
    std::cout << "Средний баланс: " << staticbank::bankaccount::getAverageBalance() << std::endl;

    std::cout << "Пополнение и снятие средств:" << std::endl;
    acc1.deposit(200);
    acc3.withdraw(45);
    acc3.withdraw(30);

    acc1.displayAccountInfo();
    acc2.displayAccountInfo();
    acc3.displayAccountInfo();


    std::cout << "Общий баланс банка после операций: " << staticbank::bankaccount::getTotalBankBalance() << std::endl;
    std::cout << "Средний баланс после операций: " << staticbank::bankaccount::getAverageBalance() << std::endl;
}