#include "university_members.h"
#include <iostream>
#include <algorithm>

namespace university_members_space {
    // UNIVERSITY MEMBER IMPLEMENT
    university_member::university_member(std::string _name, std::string _id, std::string _email)
        : name(std::move(_name)), id(std::move(_id)), email(std::move(_email)) {}

    std::string university_member::getName() const {
        return name;
    }

    std::string university_member::getId() const {
        return id;
    }

    // STUDENT IMPLEMENT
    student::student(std::string _name, std::string _id, std::string _email, std::string _major, int _year, double _gpa)
        : university_member(_name, _id, _email), major(_major), year(_year), gpa(_gpa) {}

    void student::enrollCourse(const std::string& course) {
        courses.push_back(course);
    }

    void student::dropCourse(const std::string& course) {
        courses.erase(std::remove(courses.begin(), courses.end(), course), courses.end());
    }

    void student::calculateGPA() {
        gpa = 4.0 - (courses.size() * 0.1);
        if (gpa < 0) gpa = 0;
    }

    void student::displayInfo() const {
        std::cout << "Студент: " << name << " (" << id << "), email: " << email << "\n";
        std::cout << "Специальность: " << major << ", Курс: " << year << ", GPA: " << gpa << "\n";
        std::cout << "Курсы: ";

        for (int i = 0; i < courses.size(); i++){
   
            std::cout << courses[i] << " ";
            std::cout << "\n";
        }
    }

    void student::work() const {
        std::cout << name << " учится и выполняет домашние задания.\n";
    }

    std::string student::getRole() const {
        return "Student";
    }

    //PROFESSOR IMPLEMENT

    professor::professor(std::string _name, std::string _id, std::string _email, std::string _department, std::string _office, double _salary)
        : university_member(_name, _id, _email), department(_department), office(_office), salary(_salary) {}

    void professor::assignCourse(const std::string& course) {
        teachingCourses.push_back(course);
    }

    void professor::removeCourse(const std::string& course) {
        teachingCourses.erase(std::remove(teachingCourses.begin(), teachingCourses.end(), course), teachingCourses.end());
    }

    double professor::calculateSalary() const {
        return salary + teachingCourses.size() * 1000;
    }

    void professor::displayInfo() const {
        std::cout << "Профессор: " << name << " (" << id << "), email: " << email << "\n";
        std::cout << "Кафедра: " << department << ", Кабинет: " << office
            << ", Зарплата: " << calculateSalary() << "\n";
        std::cout << "Преподает: ";


        for (int i = 0; i < teachingCourses.size(); i++) {

            std::cout << teachingCourses[i] << " ";
            std::cout << "\n";
        }
    }

    void professor::work() const {
        std::cout << name << " проводит лекции и научные исследования.\n";
    }

    std::string professor::getRole() const {
        return "Professor";
    }

    // COURCE IMPLEMENT

    course::course(std::string code, std::string name, int cred)
        : courseCode(code), courseName(name), credits(cred), instructor(nullptr) {}

    void course::setInstructor(professor* prof) {
        instructor = prof;
        if (prof) prof->assignCourse(courseCode);
    }

    void course::addStudent(student* student) {
        enrolledStudents.push_back(student);
        student->enrollCourse(courseCode);
    }

    void course::removeStudent(const std::string& studentId) {
        enrolledStudents.erase(std::remove_if(enrolledStudents.begin(), enrolledStudents.end(),
            [&](student* s) { return s->getId() == studentId; }), enrolledStudents.end());
    }

    void course::displayCourseInfo() const {
        std::cout << "Курс: " << courseName << " (" << courseCode << "), кредиты: " << credits << "\n";
        if (instructor) std::cout << "Преподаватель: " << instructor->getName() << "\n";
        std::cout << "Студенты: ";

        for (int i = 0; i < enrolledStudents.size(); i++) {

            std::cout << enrolledStudents[i]->getName() << " ";
            std::cout << "\n";
        }
    }

    // UNIVERSITY IMPLEMENT

    int university::totalUniversities = 0;

    university::university(std::string n) : name(n) {
        totalUniversities++;
    }

    university::~university() {
        totalUniversities--;
    }

    void university::addMember(std::unique_ptr<university_member> member) {
        members.push_back(std::move(member));
    }

    void university::addCourse(std::unique_ptr<course> course) {
        courses.push_back(std::move(course));
    }

    university_member* university::findMemberById(const std::string& id) const {
        for (int i = 0; i < members.size(); i++) {
            if (members[i]->getId() == id)
                return members[i].get();
        }
        return nullptr;
    }

    course* university::findCourseByCode(const std::string& code) const {
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i]->getCode() == code)
                return courses[i].get();
        }
        return nullptr;
    }

    void university::displayAllMembers() const {
        std::cout << "Члены университета " << name << "\n";
        for (int i = 0; i < members.size(); i++) {
            members[i]->displayInfo();
            std::cout << "\n";
        }
    }

    void university::displayAllCourses() const {
        std::cout << "Курсы университета " << name << "\n";

        for (int i = 0; i < courses.size(); i++) {
            courses[i]->displayCourseInfo();
            std::cout << "\n";
        }
    }

    int university::getTotalUniversities() {
        return totalUniversities;
    }

}