#include "SimpleCalculator.h"
#include "cmath"
#include "string"

SimpleCalculator::SimpleCalculator() {

}

float SimpleCalculator::Calculate(float a, float b, std::string operation)
{
	if (operation.length() == 1)
		return Calculate(a, b, operation[0]);

	if (operation == "sin")
	{
		return std::sin(a);
	}
	else if (operation == "cos")
	{
		return std::cos(a);
	}
	else if (operation == "tan")
	{
		return std::tan(a);
	}

	throw std::runtime_error("Неподдерживаемая операция");
}

float SimpleCalculator::Calculate(float a, float b, char operationSymbol)
{
	switch (operationSymbol)
	{
		case '+':
			return Sum(a,b);
		case '-':
			return Remove(a, b);
		case '*':
			return Multiply(a, b);
		case '/':
			return Devide(a, b);
		case '^':
			return std::pow(a, b);
		default:
			throw std::runtime_error("Неподдерживаемая операция");
			break;
	}
}

float SimpleCalculator::Sum(float a, float b)
{
	return a + b;
}

float SimpleCalculator::Remove(float a, float b)
{
	return a - b;
}

float SimpleCalculator::Multiply(float a, float b)
{
	return a * b;
}

float SimpleCalculator::Devide(float a, float b)
{
	if (b == 0) {
		throw std::runtime_error("Деление на ноль!");
	}

	return a / b;
}