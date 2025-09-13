#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "tinyexpr-plusplus-1.0.0/tinyexpr.h"

class TinyExprCalculator
{
public:
	TinyExprCalculator();

	bool IsValidEquation(const std::string& equation);
	double CalculateEquation(const std::string& equation);
	double _lstResult;
	std::string _lstEquation;
private:
	te_parser _tinyExpr;
};
