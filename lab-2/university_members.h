#pragma once
#include <string>
#include <vector>
#include <memory>

namespace university_members_space {
	class university_member {
	protected:
		std::string name;
		std::string id;
		std::string email;
	public:
		university_member(std::string _name, std::string _id, std::string _email);
		virtual ~university_member() = default;

		virtual void displayInfo() const = 0;
		virtual void work() const = 0;
		virtual std::string getRole() const = 0;

		std::string getId() const;
		std::string getName() const;
	};

	class student : public university_member {
	private:
		std::string major;
		int year;
		double gpa;
		std::vector<std::string> courses;

	public:
		student(std::string _name, std::string _id, std::string _email, std::string _major, int _year, double _gpa);

		void enrollCourse(const std::string& course);
		void dropCourse(const std::string& course);
		void calculateGPA();

		void displayInfo() const override;
		void work() const override;
		std::string getRole() const override;
	};

	class professor : public university_member {
	private:
		std::string department;
		std::string office;
		double salary;
		std::vector<std::string> teachingCourses;

	public:
		professor(std::string _name, std::string _id, std::string _email, std::string _department, std::string _office, double _salary);

		void assignCourse(const std::string& course);
		void removeCourse(const std::string& course);
		double calculateSalary() const;

		void displayInfo() const override;
		void work() const override;
		std::string getRole() const override;
	};

	class course {
	private:
		std::string courseCode;
		std::string courseName;
		int credits;
		professor* instructor;
		std::vector<student*> enrolledStudents;

	public:
		course(std::string code, std::string name, int cred);

		void setInstructor(professor* prof);
		void addStudent(student* student);
		void removeStudent(const std::string& studentId);

		void displayCourseInfo() const;

		std::string getCode() const { return courseCode; }
	};

	class university {
	private:
		std::string name;
		std::vector<std::unique_ptr<university_member>> members;
		std::vector<std::unique_ptr<course>> courses;
		static int totalUniversities;

	public:
		university(std::string n);
		~university();

		void addMember(std::unique_ptr<university_member> member);
		void addCourse(std::unique_ptr<course> course);

		university_member* findMemberById(const std::string& id) const;
		course* findCourseByCode(const std::string& code) const;

		void displayAllMembers() const;
		void displayAllCourses() const;

		static int getTotalUniversities();
	};
}
