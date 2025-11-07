#include <iostream>
#include "student.h"
#include "academic.h"
#include "shape.h"
#include "vehicle.h"
#include "library.h"
#include "bankaccount.h"
#include "complex.h"
#include "persons.h"
#include "data_structures.h"
#include "university_members.h"

void showFirstTask();
void showSecondTask();
void showThirdTask();
void showFourthTask();
void showFifthTask();
void showSixthTask();
void showSeventhTask();
void showEigthTask();
void showNinthTask();
void showTenTask();

int main()
{
    setlocale(LC_ALL, "Russian");

    //showFirstTask();
    //showSecondTask();
    //showThirdTask();
    //showFourthTask();
    //showFifthTask();
    //showSixthTask();
    //showSeventhTask();
    //showEigthTask();
    //showNinthTask();
    showTenTask();

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

void showSeventhTask() {
    friendly_complex::complex a(3, 4);
    friendly_complex::complex b(1, 2);

    friendly_complex::complex sum = a + b;
    friendly_complex::complex diff = a - b;
    friendly_complex::complex prod = a * b;

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a - b = " << diff << std::endl;
    std::cout << "a * b = " << prod << std::endl;

    if (a == b)
        std::cout << "a и b равны" << std::endl;
    else
        std::cout << "a и b не равны" << std::endl;

    friendly_complex::complex c;
    std::cin >> c;
    std::cout << "Вы ввели: " << c << std::endl;
}

void showEigthTask() {
    multiple_persons::teacher t("Иванов", 35, "Учитель", 60000, "Математика", 10);
    multiple_persons::professor p("Петров", 50, "Профессор", 120000, "Физика", 25, "Квантовая механика", 40);

    std::cout << "--- Учитель ---" << std::endl;
    t.display();
    t.work();
    t.holdLesson();

    std::cout << "\n--- Professor ---" << std::endl;
    p.display();
    p.work();
    p.conductResearch();
    p.guideStudents();
}

void showNinthTask() {
    try {
        std::cout << "--- Stack<int> ---" << std::endl;
        generic_structures::stack<int> intStack(5);
        intStack.push(10);
        intStack.push(20);
        intStack.push(30);
        intStack.display();
        std::cout << "Верхний элемент: " << intStack.top() << std::endl;
        intStack.pop();
        intStack.display();

        std::cout << "\n--- Stack<string> ---" << std::endl;
        generic_structures::stack<std::string> strStack(3);
        strStack.push("Hello");
        strStack.push("World");
        strStack.display();
        std::cout << "Верхний элемент: " << strStack.top() << std::endl;

        std::cout << "\n--- Queue<double> ---" << std::endl;
        generic_structures::queue<double> dblQueue(4);
        dblQueue.enqueue(1.1);
        dblQueue.enqueue(2.2);
        dblQueue.enqueue(3.3);
        dblQueue.display();
        std::cout << "Первый элемент: " << dblQueue.front() << std::endl;
        dblQueue.dequeue();
        dblQueue.display();

        std::cout << "\n--- Queue<int> ---" << std::endl;
        generic_structures::queue<int> intQueue(3);
        intQueue.enqueue(100);
        intQueue.enqueue(200);
        intQueue.enqueue(300);
        intQueue.display();
        intQueue.dequeue();
        intQueue.display();
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }
}

void showTenTask() {
    using namespace university_members_space;

    university uni("Tech University");

    std::unique_ptr<professor> prof1 = std::make_unique<professor>(
        "Иванов", "P001", "ivanov@uni.edu", "Физика", "B12", 4000
    );
    std::unique_ptr<professor> prof2 = std::make_unique<professor>(
        "Петрова", "P002", "petrova@uni.edu", "Информатика", "C21", 4200
    );

    std::unique_ptr<student> stud1 = std::make_unique<student>(
        "Алексей", "S001", "alex@uni.edu", "Информатика", 2, 3.8
    );
    std::unique_ptr<student> stud2 = std::make_unique<student>(
        "Мария", "S002", "maria@uni.edu", "Физика", 1, 3.9
    );

    std::unique_ptr<course> course1 = std::make_unique<course>(
        "CS101", "Программирование", 5
    );
    std::unique_ptr<course> course2 = std::make_unique<course>(
        "PH201", "Механика", 4
    );

    course1->setInstructor(prof2.get());
    course2->setInstructor(prof1.get());

    course1->addStudent(stud1.get());
    course2->addStudent(stud1.get());
    course2->addStudent(stud2.get());

    uni.addMember(std::move(prof1));
    uni.addMember(std::move(prof2));
    uni.addMember(std::move(stud1));
    uni.addMember(std::move(stud2));

    uni.addCourse(std::move(course1));
    uni.addCourse(std::move(course2));

    uni.displayAllMembers();
    uni.displayAllCourses();

    std::cout << "Всего университетов: " << university::getTotalUniversities() << "\n";
}