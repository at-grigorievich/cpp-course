#pragma once
#include <string>

namespace multiple_persons {
    class person {
    protected:
        std::string name;
        int age;

    public:
        person(std::string _name, int _age) : name(_name), age(_age) {}
        virtual ~person() = default;

        virtual void display() const;
    };

    class employee {
    protected:
        std:: string position;
        double salary;

    public:
        employee(std::string _position, double _salary) : position(_position), salary(_salary) {};
        virtual ~employee() = default;

        virtual void work() const;
    };

    class teacher : public person, public employee {
    protected:
        std::string subject;
        int experienceYears;

    public:
        teacher(std::string _name, int _age, std::string _position, double _salary, std::string _subject, int exp) :
            person(_name, _age), employee(_position, _salary), subject(_subject), experienceYears(exp) {}

        void display() const override;
        void work() const override;
        void holdLesson() const;
    };

    class researcher {
    protected:
        std::string researchArea;
        int publicationsCount;

    public:
        researcher(std::string area, int publications) : researchArea(area), publicationsCount(publications) {}
        virtual void conductResearch() const;
        virtual ~researcher() = default;
    };

    class professor : public teacher, public researcher {
    public:
        professor(std::string _name, int _age, std::string _position, double _salary, std::string _subject, int exp,
            std::string area, int publications) :
            teacher(_name, _age, _position, _salary, _subject, exp),
            researcher(area, publications) { }

        void display() const override;
        void work() const override;
        void guideStudents() const;
    };
}
