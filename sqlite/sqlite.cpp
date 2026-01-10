#include <iostream>
#include "DatabaseManager.h"
#include "StudentRepository.h"

void FirstTaskExecute();
void SecondTaskExecute();

int main()
{
	setlocale(LC_ALL, "Russian");
	//FirstTaskExecute();
	SecondTaskExecute();
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
