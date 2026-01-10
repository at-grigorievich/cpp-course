#pragma once
#include <string>
#include "Grade.h"

namespace SecondTask {
    struct Student
    {
        int id;
        std::string name;
        std::string email;
        std::string group;
    };

    struct StudentWithGrades
    {
        std::string name;
        std::string email;
        std::string group;
        std::vector<ThirdTask::Grade> grades;
    };
}