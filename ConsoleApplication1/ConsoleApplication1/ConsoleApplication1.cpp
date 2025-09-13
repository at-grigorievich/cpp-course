#include <iostream>
#include <string>
#include <iomanip>
#include <bitset>

#include "SimpleCalculator.h"
#include "TinyExprCalculator.h"
#include "HelpExtensions.h"

#define EQUATION_COMMAND "-eq"
#define SHOW_LAST_COMMAND "-show"
#define CONVERT_HEX_COMMAND "-hex"

void InvokeSimpleCalculator()
{
    SimpleCalculator calculator;

    float x = 0, y = 0, result = 0;
    std::string operation;
    std::string digitStr;

    while (true)
    {
        try
        {
            requireOperation(operation);
            requireValues(x, y, operation.length() > 0 && operation.length() < 2, digitStr);

            result = calculator.Calculate(x, y, operation);

            std::cout << "Результат " << result;

            std::cout << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }
}

void InvokeTinyExprCalculator()
{
    std::cout << "Список доступных команд:" << std::endl;
    std::cout << "Решить уравнение: " << EQUATION_COMMAND << " [уравнение]" << std::endl;
    std::cout << "Показать последний результат: " << SHOW_LAST_COMMAND << std::endl;
    std::cout << "Перевести в hex: " << CONVERT_HEX_COMMAND << std::endl;

    std::cout << "------------------------------------------------------------------------" << std::endl;

    std::string command;

    TinyExprCalculator exprCalculator;

    while (true)
    {
        std::cout << "Введите команду: ";
        std::getline(std::cin, command);
        
        ParsedCommand parsedCommand = parseCommand(command);

        if (parsedCommand.command == EQUATION_COMMAND)
        {
            if (exprCalculator.IsValidEquation(parsedCommand.equation) == true)
            {
                try
                {
                    double result = exprCalculator.CalculateEquation(parsedCommand.equation);
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                    continue;
                }
                std::cout << "Решение выражения: " << parsedCommand.equation << " = " << exprCalculator.CalculateEquation(parsedCommand.equation) << std::endl;
                continue;
            }
            else
            {
                std::cout << "Проблемы с выражением, повторите заново." << std::endl;
                continue;
            }
        }
        else if (parsedCommand.command == SHOW_LAST_COMMAND)
        {
            std::cout << "Последнее решенное уравнение: " << exprCalculator._lstEquation << "=" << exprCalculator._lstResult << std::endl;
            continue;
        }
        else if (parsedCommand.command == CONVERT_HEX_COMMAND)
        {
            std::cout << "Значение " << exprCalculator._lstResult << " в HEX: ";
            printDoubleHex(exprCalculator._lstResult);
            continue;
        }
        
        std::cout << "Неверная команда, попробуйте еще..." << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    InvokeTinyExprCalculator();

    return 0;
}
