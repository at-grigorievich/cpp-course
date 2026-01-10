#include <iostream>
#include "DatabaseManager.h"

void FirstTaskExecute();

int main()
{
	setlocale(LC_ALL, "Russian");
	FirstTaskExecute();
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
