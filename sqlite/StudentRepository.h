#pragma once
#include <vector>
#include <optional>
#include "DatabaseManager.h"
#include "Student.h"

namespace SecondTask {
    class StudentRepository
    {
    public:
        StudentRepository(SQLite::DatabaseManager& dbManager);

        bool addStudent(const std::string& name,
            const std::string& email,
            const std::string& group);

        std::optional<Student> getStudent(int id);
        std::vector<Student> getAllStudents();

        bool updateStudent(int id,
            const std::string& name,
            const std::string& email,
            const std::string& group);

        bool deleteStudent(int id);

    private:
        sqlite3* _db;
    };
}