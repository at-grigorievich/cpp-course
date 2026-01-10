#include "InputValidator.h"
#include <regex>

namespace FourthTask
{
    bool InputValidator::isValidEmail(const std::string& email) const
    {
        const std::regex pattern(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)");
        return std::regex_match(email, pattern);
    }

    bool InputValidator::isSafeInput(const std::string& input) const
    {
        for (char c : input)
        {
            if (c == ';' || c == '\'' || c == '\"' || c == '-' || c == '=')
                return false;
        }
        return true;
    }

    bool InputValidator::isValidLength(const std::string& input, size_t maxLength) const
    {
        return input.size() <= maxLength;
    }

    bool InputValidator::isValidGrade(int grade) const
    {
        return grade >= 0 && grade <= 100;
    }
}