#include "Evaluator.h"
#include <stack>

Evaluator::Evaluator()
{
}

bool Evaluator::isBooleanEquation(string equation) {
	for (std::map<string, int>::iterator iter = booleanOperators.begin(); iter != booleanOperators.end(); iter++)
		if (equation.find(iter->first) != -1) return true;
	return false;
}

int Evaluator::eval(string equation)
{
	// resulting int to return
	int result = 0;
	// check if the equation passed has any boolean operators
	bool isEquationABooleanEquation = isBooleanEquation(equation);
	// if the equation passed has boolean operators,
	//   evaluate each math portion and build string for boolean equation
	if (isEquationABooleanEquation) {
		// boolean equation that will be built
		string booleanEquation = "";
		bool hasBooleanOperators = true;
		// while the equation contains boolean operators
		while (hasBooleanOperators) {
			bool foundBooleanOperator = false;
			// search for a boolean operator
			for (std::map<string, int>::iterator iter = booleanOperators.begin(); iter != booleanOperators.end(); iter++) {
				// if this is the first boolean operator found
				if (!foundBooleanOperator && equation.find(iter->first) != -1) {
					foundBooleanOperator = true;
					// add math portion before the boolean operator to the booleanEquation string
					booleanEquation += evalPostMath(equation.substr(0, equation.find(iter->first)));
					// remove the evaluated portion from the equation
					equation = equation.substr(equation.find(iter->first) + iter->first.length, equation.length - 1);
					// add the boolean operator to the booleanEquation string
					booleanEquation += equation.substr(0, iter->first.length);
					// remove the boolean operator from the equation
					equation = equation.substr(iter->first.length, equation.length - 1);
				}
			}
			// re-evaluate if the expression still has a boolean operator
			hasBooleanOperators = isBooleanEquation(equation);
		}
		// evaluate the final part of the equation and add it to the booleanEquation string
		booleanEquation += evalPostMath(equation);
		// return the result of the boolean equation
		return evalPostBool(booleanEquation);
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
	return 0;
}

// Brian
string Evaluator::toPostBool(string equation)
{
	return string();
}

// Lee
string Evaluator::toPostMath(string equation)
{
	return string();
}
