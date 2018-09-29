#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#pragma once
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
	// returns true if the character passed is part of an operator
	static bool isPartOfOperator(const char& ch);
	// returns true if the character passed is an operator on it's own
	static bool isOperator(const char& ch);
	// returns true if the character passed is between and including 0 to 9
	static bool isDigit(const char& ch);
	// returns true if the string passed is a number (positive or negative)
	static bool isNumber(const string& str);
	// returns a version of the expression passed with one space between each token
	static string fixSpaces(string expression);
	// use this method to throw an exception
	static void throwException(const string& exception);
	// returns a string with the value of the first strings numerical value added to the integer passed
	static string addStringAndInt(const string& str, const int& i);
	// returns a 0 or 1 based on (left token right)
	static int evalBool(const int& left, const int& right, const string& op);
	// returns result based on the operation on two numbers(num1 and num2)
	static int evalOperation( const string& op, const int& num1, const int& num2);
	// returns true if the precedecne of op1 is greater than the precedence of op2
	static bool isOperatorGreaterThan(string op1, string op2);
};
