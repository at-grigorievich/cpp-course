#pragma once
#include <vector>
#include <optional>
#include "DatabaseManager.h"
#include "Student.h"
#include "Grade.h"
#include "StudentStats.h"
#include "InputValidator.h"

namespace SecondTask {
    class StudentRepository
    {
    public:
        StudentRepository(SQLite::DatabaseManager& dbManager);

        bool addStudent(const std::string& name, const std::string& email, const std::string& group);

        std::optional<Student> getStudent(int id);
        std::vector<Student> getAllStudents();

        bool updateStudent(int id, const std::string& name, const std::string& email, const std::string& group);

        bool deleteStudent(int id);

        bool addStudentWithGrades(const std::string& name, const std::string& email, const std::string& group,
            const std::vector<ThirdTask::Grade>& grades);

        std::vector<Student> getStudentsByGroup(const std::string& group);
        double getAverageGradeBySubject(const std::string& subject);
        std::vector<ThirdTask::StudentStats> getTopStudents(int limit);

    private:
        sqlite3* _db;
        FourthTask::InputValidator _validator;

        void validateStudentData(const std::string& name, const std::string& email, const std::string& group,
            const std::vector<ThirdTask::Grade>& grades = {});
    };
}