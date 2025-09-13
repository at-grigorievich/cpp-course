#include "TinyExprCalculator.h"
#include "HelpExtensions.h"

TinyExprCalculator::TinyExprCalculator() 
{
	_lstEquation = "";
	_lstResult = 0.0;
}

bool TinyExprCalculator::IsValidEquation(const std::string& equation)
{
	if (equation.length() == 0)
		return false;

	return _tinyExpr.compile(equation);
}

double TinyExprCalculator::CalculateEquation(const std::string& equation)
{
	if (equation == _lstEquation) return _lstResult;

	_lstResult = _tinyExpr.evaluate(equation);

	if (_tinyExpr.success() == true)
	{
		_lstEquation = equation;
		return _lstResult;
	}
	
	_lstEquation = "";
	_lstResult = 0.0;
	throw std::runtime_error("Ошибка вычисления");
}

