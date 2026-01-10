#include <iostream>
#include "DatabaseManager.h"
#include "StudentRepository.h"

void FirstTaskExecute();
void SecondTaskExecute();
void ThirdTaskExecute();
void FourthTaskExecute();

int main()
{
	setlocale(LC_ALL, "Russian");
	//FirstTaskExecute();
	//SecondTaskExecute();
	//ThirdTaskExecute();
	FourthTaskExecute();
}

void FirstTaskExecute()
{
    using namespace SQLite;

    DatabaseManager db("students.db");

    if (!db.Open())
    {
        std::cout << "Не удалось подключиться к базе данных\n";
        return;
    }

    if (!db.InitializeTables())
    {
        std::cout << "Ошибка при создании таблиц\n";
		return;
    }

    std::cout << "База данных успешно инициализирована\n";
}
void SecondTaskExecute() {
	using namespace SQLite;
    using namespace SecondTask;

    DatabaseManager db("students.db");
    db.Open();
    db.InitializeTables();

    StudentRepository repo(db);

    repo.addStudent("Иван Иванов", "ivan@pfur.ru", "CS-101");

    auto student = repo.getStudent(1);
    if (student)
    {
        std::cout << student->name << std::endl;
    }
}
void ThirdTaskExecute() {
    using namespace SQLite;
    using namespace SecondTask;
	using namespace ThirdTask;

    DatabaseManager db("students.db");
    db.Open();
    db.InitializeTables();

    StudentRepository repo(db);

    std::vector<Grade> grades = {
        {"Математика", 85},
        {"Физика", 90}
    };

    bool success = repo.addStudentWithGrades(
        "Артем Петров",
        "passf@university.ru",
        "CS-101",
        grades
    );

    if (success)
    {
        std::cout << "Студент и оценки успешно добавлены (транзакция)\n";
    }
    else
    {
        std::cout << "Ошибка при добавлении студента и оценок\n";
        return;
    }

    auto topStudents = repo.getTopStudents(5);

    std::cout << "Топ студентов:\n";
    for (const auto& s : topStudents)
    {
        std::cout << "ID: " << s.id
            << ", Имя: " << s.name
            << ", Средний балл: " << s.averageGrade
            << std::endl;
    }
}
void FourthTaskExecute() {
    using namespace SQLite;
    using namespace SecondTask;
    using namespace ThirdTask;
    using namespace FourthTask;

    DatabaseManager db("students.db");
    db.Open();
    db.InitializeTables();

    StudentRepository repo(db);

    std::vector<Grade> grades = {
        {"Математика", 85},
        {"Физика", 90}
    };
    try
    {
        bool success = repo.addStudentWithGrades(
            "BFDFDF Петров",
            "passf@univeasfity.ru",
            "CS101",
            grades
        );

        if (success)
        {
            std::cout << "Студент и оценки успешно добавлены (транзакция)\n";
        }
        else
        {
            std::cout << "Ошибка при добавлении студента и оценок\n";
            return;
        }

        auto topStudents = repo.getTopStudents(5);

        std::cout << "Топ студентов:\n";
        for (const auto& s : topStudents)
        {
            std::cout << "ID: " << s.id
                << ", Имя: " << s.name
                << ", Средний балл: " << s.averageGrade
                << std::endl;
        }

        std::cout << "\nПопытка добавить студента с невалидным email:\n";
        repo.addStudent("Иван Иванов", "ivan@@university", "CS-101");
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << "Ошибка валидации: " << ex.what() << std::endl;
    }
}