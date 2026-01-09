#include <iostream>
#include <sqlite3.h>

int main()
{
	setlocale(LC_ALL, "ru");

	sqlite3* db;
	sqlite3_open(":memory:", &db);

	std::cout << "Database opened successfully." << std::endl;

	sqlite3_close(db);

}
