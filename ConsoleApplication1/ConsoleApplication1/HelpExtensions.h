#pragma once
#include <string>
#include <iostream>

struct ParsedCommand
{
    std::string command;
    std::string equation;
};

inline ParsedCommand parseCommand(const std::string& input) {
    ParsedCommand result;
    std::size_t pos = input.find(' ');

    if (pos == std::string::npos) {
        result.command = input;
        result.equation = "";
    }
    else {
        result.command = input.substr(0, pos);
        result.equation = input.substr(pos + 1);
    }

    return result;
}

inline float getFloat(std::string& input) {
    float result = std::stof(input);
    return result;
}

inline float readFloat(std::string comment, std::string& digitStr)
{
    std::cout << comment;
    std::cin >> digitStr;

    return getFloat(digitStr);
}

inline void requireEquation(std::string& result)
{
    std::cout << "¬ведите уравнение: ";
    std::cin >> result;
}

inline void requireOperation(std::string& result)
{
    std::cout << "¬ведите операцию (+, -, *, /, ^, sin, cos, tan): ";
    std::cin >> result;
}

inline void requireValues(float& x, float& y, const bool& readOnlyOneValue, std::string& digitStr)
{
    x = readFloat("¬ведите 1 значение: ", digitStr);

    if (readOnlyOneValue == false) return;

    y = readFloat("¬ведите 2 значение: ", digitStr);
}

inline void printDoubleHex(double x) {
    uint64_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    std::cout << "0x"
        << std::hex << std::setw(16) << std::setfill('0')
        << bits << std::dec << "\n";
}