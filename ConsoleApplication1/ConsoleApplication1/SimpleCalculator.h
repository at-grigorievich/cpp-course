#pragma once

#include <iostream>
#include <string>

class SimpleCalculator
{
public:
	SimpleCalculator();
	
	float Calculate(float a, float b, std::string operation);
	float Calculate(float a, float b, char operationSymbol);
private:
	float Sum(float a, float b);
	float Remove(float a, float b);
	float Multiply(float a, float b);
	float Devide(float a, float b);
};
