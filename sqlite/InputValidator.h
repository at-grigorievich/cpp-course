#pragma once
#include <string>

namespace FourthTask {
    class InputValidator
    {
    public:
        bool isValidEmail(const std::string& email) const;
        bool isSafeInput(const std::string& input) const;
        bool isValidLength(const std::string& input, size_t maxLength) const;
        bool isValidGrade(int grade) const;
    };
}