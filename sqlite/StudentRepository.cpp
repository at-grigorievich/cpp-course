#include "StudentRepository.h"
#include <iostream>

namespace SecondTask{
	StudentRepository::StudentRepository(SQLite::DatabaseManager& dbManager)
	{
		_db = dbManager.GetConnection();
	}

    bool StudentRepository::addStudent(const std::string& name, const std::string& email, const std::string& group)
    {
        validateStudentData(name, email, group);

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

    bool StudentRepository::updateStudent(int id,const std::string& name, const std::string& email, const std::string& group)
    {
        validateStudentData(name, email, group);

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

    bool StudentRepository::addStudentWithGrades(const std::string& name, const std::string& email, const std::string& group,
        const std::vector<ThirdTask::Grade>& grades)
    {
        validateStudentData(name, email, group, grades);

        if (sqlite3_exec(_db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) != SQLITE_OK)
            return false;

        const char* studentSql =
            "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";

        sqlite3_stmt* studentStmt = nullptr;
        if (sqlite3_prepare_v2(_db, studentSql, -1, &studentStmt, nullptr) != SQLITE_OK)
        {
            sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return false;
        }

        sqlite3_bind_text(studentStmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(studentStmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(studentStmt, 3, group.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(studentStmt) != SQLITE_DONE)
        {
            sqlite3_finalize(studentStmt);
            sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return false;
        }

        sqlite3_finalize(studentStmt);

        int studentId = static_cast<int>(sqlite3_last_insert_rowid(_db));

        const char* gradeSql =
            "INSERT INTO grades (student_id, subject, grade) VALUES (?, ?, ?);";

        sqlite3_stmt* gradeStmt = nullptr;
        if (sqlite3_prepare_v2(_db, gradeSql, -1, &gradeStmt, nullptr) != SQLITE_OK)
        {
            sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return false;
        }

        for (const auto& g : grades)
        {
            sqlite3_bind_int(gradeStmt, 1, studentId);
            sqlite3_bind_text(gradeStmt, 2, g.subject.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(gradeStmt, 3, g.grade);

            if (sqlite3_step(gradeStmt) != SQLITE_DONE)
            {
                sqlite3_finalize(gradeStmt);
                sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
                return false;
            }

            sqlite3_reset(gradeStmt);
            sqlite3_clear_bindings(gradeStmt);
        }

        sqlite3_finalize(gradeStmt);

        if (sqlite3_exec(_db, "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK)
        {
            sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return false;
        }

        return true;
    }

    std::vector<Student> StudentRepository::getStudentsByGroup(const std::string& group)
    {
        const char* sql =
            "SELECT id, name, email, group_name "
            "FROM students WHERE group_name = ?;";

        sqlite3_stmt* stmt = nullptr;
        std::vector<Student> result;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            return result;

        sqlite3_bind_text(stmt, 1, group.c_str(), -1, SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            Student s;
            s.id = sqlite3_column_int(stmt, 0);
            s.name = (const char*)sqlite3_column_text(stmt, 1);
            s.email = (const char*)sqlite3_column_text(stmt, 2);
            s.group = (const char*)sqlite3_column_text(stmt, 3);
            result.push_back(s);
        }

        sqlite3_finalize(stmt);
        return result;
    }

    double StudentRepository::getAverageGradeBySubject(const std::string& subject)
    {
        const char* sql =
            "SELECT AVG(grade) FROM grades WHERE subject = ?;";

        sqlite3_stmt* stmt = nullptr;
        double avg = 0.0;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            return avg;

        sqlite3_bind_text(stmt, 1, subject.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            avg = sqlite3_column_double(stmt, 0);
        }

        sqlite3_finalize(stmt);
        return avg;
    }

    std::vector<ThirdTask::StudentStats> StudentRepository::getTopStudents(int limit)
    {
        const char* sql =
            "SELECT s.id, s.name, AVG(g.grade) as avg_grade "
            "FROM students s "
            "JOIN grades g ON s.id = g.student_id "
            "GROUP BY s.id "
            "ORDER BY avg_grade DESC "
            "LIMIT ?;";

        sqlite3_stmt* stmt = nullptr;
        std::vector<ThirdTask::StudentStats> result;

        if (sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
            return result;

        sqlite3_bind_int(stmt, 1, limit);

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            ThirdTask::StudentStats stats;
            stats.id = sqlite3_column_int(stmt, 0);
            stats.name = (const char*)sqlite3_column_text(stmt, 1);
            stats.averageGrade = sqlite3_column_double(stmt, 2);
            result.push_back(stats);
        }

        sqlite3_finalize(stmt);
        return result;
    }

    bool StudentRepository::batchInsertStudents(const std::vector<StudentWithGrades>& students)
    {
        if (sqlite3_exec(_db, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) != SQLITE_OK)
            return false;

        const char* studentSql = "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";
        const char* gradeSql = "INSERT INTO grades (student_id, subject, grade) VALUES (?, ?, ?);";

        sqlite3_stmt* studentStmt = nullptr;
        sqlite3_stmt* gradeStmt = nullptr;

        if (sqlite3_prepare_v2(_db, studentSql, -1, &studentStmt, nullptr) != SQLITE_OK ||
            sqlite3_prepare_v2(_db, gradeSql, -1, &gradeStmt, nullptr) != SQLITE_OK)
        {
            sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return false;
        }

        try
        {
            for (const StudentWithGrades s : students)
            {
                validateStudentData(s.name, s.email, s.group, s.grades);

                sqlite3_bind_text(studentStmt, 1, s.name.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(studentStmt, 2, s.email.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(studentStmt, 3, s.group.c_str(), -1, SQLITE_TRANSIENT);

                if (sqlite3_step(studentStmt) != SQLITE_DONE)
                    throw std::runtime_error("Ошибка при вставке студента");

                int studentId = static_cast<int>(sqlite3_last_insert_rowid(_db));
                sqlite3_reset(studentStmt);
                sqlite3_clear_bindings(studentStmt);

                for (const auto& g : s.grades)
                {
                    sqlite3_bind_int(gradeStmt, 1, studentId);
                    sqlite3_bind_text(gradeStmt, 2, g.subject.c_str(), -1, SQLITE_TRANSIENT);
                    sqlite3_bind_int(gradeStmt, 3, g.grade);

                    if (sqlite3_step(gradeStmt) != SQLITE_DONE)
                        throw std::runtime_error("Ошибка при вставке оценки");

                    sqlite3_reset(gradeStmt);
                    sqlite3_clear_bindings(gradeStmt);
                }
            }

            sqlite3_finalize(studentStmt);
            sqlite3_finalize(gradeStmt);

            if (sqlite3_exec(_db, "COMMIT;", nullptr, nullptr, nullptr) != SQLITE_OK)
            {
                sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
                return false;
            }

            return true;
        }
        catch (...)
        {
            sqlite3_finalize(studentStmt);
            sqlite3_finalize(gradeStmt);
            sqlite3_exec(_db, "ROLLBACK;", nullptr, nullptr, nullptr);
            return false;
        }
    }

    void StudentRepository::validateStudentData(const std::string& name, const std::string& email, const std::string& group,
        const std::vector<ThirdTask::Grade>& grades)
    {
        if (!_validator.isValidLength(name, 50))
            throw std::invalid_argument("Имя слишком длинное (макс. 50 символов)");

        if (!_validator.isValidLength(email, 50))
            throw std::invalid_argument("Email слишком длинный (макс. 50 символов)");

        if (!_validator.isValidLength(group, 20))
            throw std::invalid_argument("Название группы слишком длинное (макс. 20 символов)");

        if (!_validator.isValidEmail(email))
            throw std::invalid_argument("Некорректный формат email");

        if (!_validator.isSafeInput(name)) {
            throw std::invalid_argument("Обнаружена потенциальная SQL-инъекция в имени");
        }

        if (!_validator.isSafeInput(email)) {
            throw std::invalid_argument("Обнаружена потенциальная SQL-инъекция в Email");
        }

        if (!_validator.isSafeInput(group)) {
            throw std::invalid_argument("Обнаружена потенциальная SQL-инъекция в названии группы");
        }

        for (const ThirdTask::Grade g : grades)
        {
            if (!_validator.isValidLength(g.subject, 30))
                throw std::invalid_argument("Название предмета слишком длинное (макс. 30 символов)");

            if (!_validator.isValidGrade(g.grade))
                throw std::invalid_argument("Оценка должна быть в диапазоне 0–100");

            if (!_validator.isSafeInput(g.subject))
                throw std::invalid_argument("Обнаружена потенциальная SQL-инъекция в названии предмета");
        }

		std::cout << "Валидация данных студента пройдена успешно\n";
    }
}