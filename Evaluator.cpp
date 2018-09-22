#include "Evaluator.h"
#include "EvaluatorHelper.h"
#include <stack>
#include <sstream>

Evaluator::Evaluator()
{
}

int Evaluator::eval(string equation)
{
	equation = EvaluatorHelper::fixSpaces(equation);
	// resulting int to return
	int result = 0;
	// check if the equation passed has any boolean operators
	bool isEquationABooleanEquation = EvaluatorHelper::isBooleanEquation(equation);
	// if the equation passed has boolean operators,
	//   evaluate each math portion and build string for boolean equation
	if (isEquationABooleanEquation) {
		istringstream tokens(equation);
		string token = "";
		string mathEquation = "";
		string booleanEquation = "";
		while (tokens >> token) {
			if (EvaluatorHelper::isBooleanOperator(token)) {
				string booleanEquationPiece = std::to_string(evalPostMath(toPostMath(mathEquation))) + " " + token + " ";
				booleanEquation += booleanEquationPiece;
				mathEquation = "";
			}
			else {
				mathEquation += token + " ";
			}
		}
		booleanEquation += to_string(evalPostMath(toPostMath(mathEquation)));
		return evalPostBool(toPostBool(booleanEquation));
	}
	// if the equation passed does not have boolean operators,
	//   evaluate math result
	else {
		result = evalPostMath(equation);
	}
	// return result
	return result;
}

// Nathan
bool Evaluator::evalPostBool(string equation)
{
	return false;
}

// Angad
int Evaluator::evalPostMath(string equation)
{
	return 5;
}

// Brian
string Evaluator::toPostBool(string equation)
{
	return "5 7 >";
}

// Lee
string Evaluator::toPostMath(string equation)
{
	return "5 7 +";
}
