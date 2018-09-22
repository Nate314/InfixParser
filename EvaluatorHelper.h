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
	// returns true if the equation contains a boolean operator
	static bool isBooleanEquation(string equation);
	// returns true if the string passed is a math operator
	static bool isMathOperator(string str);
	// returns true if the string passed is a boolean operator
	static bool isBooleanOperator(string str);
	// returns true if the string passed is an increment or decrement operator
	static bool isIncrementDecrementOperator(string str);
	// returns true if the string passed is one of these (){}[]
	static bool isParentheses(string str);
	// returns true if the string passed is an operator
	static bool isOperator(string str);
	// returns true if the character passed is part of an operator
	static bool isPartOfOperator(char ch);
	// returns true if the character passed is an operator on it's own
	static bool isOperator(char ch);
	// returns true if the character passed is between and including 0 to 9
	static bool isDigit(char ch);
	// returns true if the string passed is a number (positive or negative)
	static bool isNumber(string str);
	// returns a version of the expression passed with one space between each token
	static string fixSpaces(string expression);
	// use this method to throw an exception
	static void throwException(string exception);
	// returns a string with the value of the first strings numerical value added to the integer passed
	static string addStringAndInt(string str, int i);
};
