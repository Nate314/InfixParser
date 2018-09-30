#pragma once
#include <sstream>
#include <string>
#include <map>
using namespace std;

class EvaluatorHelper {
public:
	// all parentheses values are stored here for reference
	static const string parentheses;
	// all digit values are stored here for reference
	static const string digits;
	// all operators with specified precedencies are stored here for reference
	static const map<string, int> operators;
	// returns true if the equation contains a boolean operator outside of parentheses
	static bool isBooleanEquation(const string& equation);
	// returns true if the equation contains a math operator outside of parentheses
	static bool isMathEquation(const string& equation);
	// returns true if the string passed is a math operator
	static bool isMathOperator(const string& str);
	// returns true if the string passed is a boolean operator
	static bool isBooleanOperator(const string& str);
	// returns true if the string passed is an increment or decrement operator
	static bool isIncrementDecrementOperator(const string& str);
	// returns true if the string passed is one of these (){}[]
	static bool isParentheses(const string& str);
	// returns true if the string passed is an operator
	static bool isOperator(const string& str);
	// returns true if the string passed is a unary operator (!, --, or ++)
	static bool isUnaryOperator(const string& str);
	// returns true if the character passed is part of an operator
	static bool isPartOfOperator(const char& ch);
	// returns true if the character passed is an operator on it's own
	static bool isOperator(const char& ch);
	// returns true if the character passed is between and including 0 to 9
	static bool isDigit(const char& ch);
	// returns true if the string passed is a number (positive or negative)
	static bool isNumber(const string& str);
	// use this method to throw an exception
	static void throwException(const string& exception);
	// returns a string with the value of the first strings numerical value added to the integer passed
	static string addStringAndInt(const string& str, const int& i);
	// returns result based on the operation on two numbers(num1 and num2)
	//   if a unary operator is passed, the operator will only be applied to the lhs
	static int evalOperation(const string& op, const int& lhs, const int& rhs);
	// returns true if the precedecne of op1 is greater than the precedence of op2
	static bool isOperatorGreaterThan(const string& op1, const string& op2);
	// returns the integer value of the passed string
	static int strToInt(const string& str);
};
