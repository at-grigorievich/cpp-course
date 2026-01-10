#include "StudentRepository.h"
#include <iostream>

namespace SecondTask{
	StudentRepository::StudentRepository(SQLite::DatabaseManager& dbManager)
	{
		_db = dbManager.GetConnection();
	}

    bool StudentRepository::addStudent(const std::string& name,
        const std::string& email,
        const std::string& group)
    {
        const char* sql =
            "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";

        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            std::cout << "Ошибка подготовки запроса\n";
            return false;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, group.c_str(), -1, SQLITE_TRANSIENT);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result == SQLITE_CONSTRAINT)
        {
            std::cout << "Email уже существует\n";
            return false;
        }

        return result == SQLITE_DONE;
    }

    std::optional<Student> StudentRepository::getStudent(int id)
    {
        const char* sql =
            "SELECT id, name, email, group_name FROM students WHERE id = ?;";

        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            return std::nullopt;

        sqlite3_bind_int(stmt, 1, id);

        Student student;
        bool found = false;

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            student.id = sqlite3_column_int(stmt, 0);
            student.name = (const char*)sqlite3_column_text(stmt, 1);
            student.email = (const char*)sqlite3_column_text(stmt, 2);
            student.group = (const char*)sqlite3_column_text(stmt, 3);
            found = true;
        }

        sqlite3_finalize(stmt);

        if (!found)
            return std::nullopt;

        return student;
    }

    std::vector<Student> StudentRepository::getAllStudents()
    {
        const char* sql =
            "SELECT id, name, email, group_name FROM students;";

        sqlite3_stmt* stmt = nullptr;
        std::vector<Student> students;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            return students;

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            Student student;
            student.id = sqlite3_column_int(stmt, 0);
            student.name = (const char*)sqlite3_column_text(stmt, 1);
            student.email = (const char*)sqlite3_column_text(stmt, 2);
            student.group = (const char*)sqlite3_column_text(stmt, 3);

            students.push_back(student);
        }

        sqlite3_finalize(stmt);
        return students;
    }

    bool StudentRepository::updateStudent(int id,
        const std::string& name,
        const std::string& email,
        const std::string& group)
    {
        const char* sql =
            "UPDATE students SET name = ?, email = ?, group_name = ? WHERE id = ?;";

        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            return false;

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, group.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, id);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result == SQLITE_CONSTRAINT)
        {
            std::cout << "Email уже используется\n";
            return false;
        }

        return result == SQLITE_DONE;
    }

    bool StudentRepository::deleteStudent(int id)
    {
        const char* sql = "DELETE FROM students WHERE id = ?;";

        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            return false;

        sqlite3_bind_int(stmt, 1, id);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        return result == SQLITE_DONE;
    }
}