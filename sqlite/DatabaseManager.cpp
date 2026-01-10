#include "DatabaseManager.h"
#include <iostream>

namespace SQLite {
    DatabaseManager::DatabaseManager(const std::string& dbPath)
        : _dbPath(dbPath), _db(nullptr)
    {
    }

    DatabaseManager::~DatabaseManager()
    {
        Close();
    }

    bool DatabaseManager::Open()
    {
        int result = sqlite3_open(_dbPath.c_str(), &_db);

        if (result != SQLITE_OK)
        {
            std::cerr << "Ошибка открытия БД: " << sqlite3_errmsg(_db) << std::endl;
            return false;
        }

        return true;
    }

    void DatabaseManager::Close()
    {
        if (_db)
        {
            sqlite3_close(_db);
            _db = nullptr;
        }
    }

    bool DatabaseManager::Execute(const std::string& sql)
    {
        char* errorMessage = nullptr;

        int result = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errorMessage);

        if (result != SQLITE_OK)
        {
            std::cerr << "SQL ошибка: " << errorMessage << std::endl;
            sqlite3_free(errorMessage);
            return false;
        }

        return true;
    }

    bool DatabaseManager::InitializeTables()
    {
        Execute("PRAGMA foreign_keys = ON;");
        Execute("PRAGMA journal_mode = WAL;");
        Execute("PRAGMA synchronous = NORMAL;");

        std::string studentsTable = R"(
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            email TEXT UNIQUE,
            group_name TEXT
        );
    )";

        std::string gradesTable = R"(
        CREATE TABLE IF NOT EXISTS grades (
            id INTEGER PRIMARY KEY,
            student_id INTEGER,
            subject TEXT,
            grade INTEGER,
            FOREIGN KEY(student_id) REFERENCES students(id) ON DELETE CASCADE
        );
    )";

		bool studentsCreated = Execute(studentsTable);
		bool gradesCreated = Execute(gradesTable);

        if (studentsCreated && gradesCreated) {
            sqlite3_exec(_db, "CREATE UNIQUE INDEX IF NOT EXISTS idx_students_email ON students(email);", nullptr, nullptr, nullptr);
            sqlite3_exec(_db, "CREATE INDEX IF NOT EXISTS idx_students_group ON students(group_name);", nullptr, nullptr, nullptr);
            sqlite3_exec(_db, "CREATE INDEX IF NOT EXISTS idx_grades_subject ON grades(subject);", nullptr, nullptr, nullptr);
            std::cout << "Таблицы успешно созданы или уже существуют." << std::endl;

			return true;
        }

        return false;
    }

    sqlite3* DatabaseManager::GetConnection() const
    {
        return _db;
    }
}
