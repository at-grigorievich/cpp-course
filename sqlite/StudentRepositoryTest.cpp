#include <gtest/gtest.h>
#include "DatabaseManager.h"
#include "StudentRepository.h"

using namespace SQLite;
using namespace SecondTask;


// Для удобства, все тесты используют ":memory:" базу SQLite
class StudentRepositoryTest : public ::testing::Test {
protected:
    SQLite::DatabaseManager db;
    StudentRepository* repo;

    StudentRepositoryTest() : db(":memory:") {} // in-memory БД для тестов

    void SetUp() override {
        ASSERT_TRUE(db.Open());
        ASSERT_TRUE(db.InitializeTables());
        repo = new StudentRepository(db);
    }

    void TearDown() override {
        delete repo;
        db.Close();
    }
};

// CRUD тесты
TEST_F(StudentRepositoryTest, AddStudentValidData) {
    EXPECT_TRUE(repo->addStudent("Иван Иванов", "ivan@uni.ru", "CS101"));
    auto student = repo->getStudent(1);
    ASSERT_TRUE(student.has_value());
    EXPECT_EQ(student->name, "Иван Иванов");
    EXPECT_EQ(student->email, "ivan@uni.ru");
    EXPECT_EQ(student->group, "CS101");
}

TEST_F(StudentRepositoryTest, UpdateStudentData) {
    repo->addStudent("Иван Иванов", "ivan@unis.ru", "CS101");
    EXPECT_TRUE(repo->updateStudent(1, "Иван Петров", "ivan.petrov@uni.ru", "CS102"));
    auto student = repo->getStudent(1);
    ASSERT_TRUE(student.has_value());
    EXPECT_EQ(student->name, "Иван Петров");
    EXPECT_EQ(student->email, "ivan.petrov@uni.ru");
    EXPECT_EQ(student->group, "CS102");
}

TEST_F(StudentRepositoryTest, DeleteStudent) {
    repo->addStudent("Иван Иванов", "ivan@uni.ru", "CS101");
    EXPECT_TRUE(repo->deleteStudent(1));
    auto student = repo->getStudent(1);
    EXPECT_FALSE(student.has_value());
}

// Тест с оценками
TEST_F(StudentRepositoryTest, AddStudentWithGrades) {
    std::vector<ThirdTask::Grade> grades = { {"Math", 90}, {"Physics", 85} };
    EXPECT_TRUE(repo->addStudentWithGrades("Петр Петров", "petr@uni.ru", "CS101", grades));

    auto student = repo->getStudent(1);
    ASSERT_TRUE(student.has_value());
    EXPECT_EQ(student->name, "Петр Петров");

    double avgMath = repo->getAverageGradeBySubject("Math");
    double avgPhysics = repo->getAverageGradeBySubject("Physics");
    EXPECT_EQ(avgMath, 90);
    EXPECT_EQ(avgPhysics, 85);
}

//Тест выборки
TEST_F(StudentRepositoryTest, GetStudentsByGroup) {
    repo->addStudent("Alice", "alice@test.com", "CS101");
    repo->addStudent("Bob", "bob@test.com", "CS101");
    repo->addStudent("Charlie", "charlie@test.com", "CS102");

    auto cs101 = repo->getStudentsByGroup("CS-101");
    EXPECT_EQ(cs101.size(), 2);
    EXPECT_EQ(cs101[0].group, "CS101");
}

//Топ студенты
TEST_F(StudentRepositoryTest, GetTopStudents) {
    repo->addStudentWithGrades("Студент1", "s1@uni.ru", "CS101", { {"Math", 80} });
    repo->addStudentWithGrades("Студент2", "s2@uni.ru", "CS101", { {"Math", 95} });
    repo->addStudentWithGrades("Студент3", "s3@uni.ru", "CS102", { {"Math", 70} });

    auto top = repo->getTopStudents(2);
    EXPECT_EQ(top.size(), 2);
    EXPECT_EQ(top[0].name, "Студент2");
    EXPECT_EQ(top[1].name, "Студент1");
}

// Пакетная вставка
TEST_F(StudentRepositoryTest, BatchInsertStudentsWorks) {
    std::vector<StudentWithGrades> students = {
        { "СтудентA", "a@uni.ru", "CS101", { {"Math", 90}, {"Physics", 85} } },
        { "СтудентB", "b@uni.ru", "CS101", { {"Math", 80}, {"Physics", 75} } },
        { "СтудентC", "c@uni.ru", "CS102", { {"Math", 70}, {"Physics", 65} } }
    };

    EXPECT_TRUE(repo->batchInsertStudents(students));

    auto allStudents = repo->getAllStudents();
    EXPECT_EQ(allStudents.size(), 3);

    double avgMathCS101 = repo->getAverageGradeBySubject("Math");
    EXPECT_NEAR(avgMathCS101, (90 + 80 + 70) / 3.0, 1e-5);
}
