#include "EvaluatorHelper.h"

// all parentheses values are stored here for reference
const string EvaluatorHelper::parentheses = "()";
// all digit values are stored here for reference
const string EvaluatorHelper::digits = "0123456789";
// all operators with specified precedencies are stored here for reference
const std::map<string, int> EvaluatorHelper::operators = { {")", 9}, {"!", 8}, {"++", 8}, {"--", 8}, {"^", 7},
									{"*", 6}, {"/", 6}, {"%", 6}, {"+", 5}, {"-", 5},
									{">", 4}, {">=", 4}, {"<", 4}, {"<=", 4},
									{"==", 3}, {"!=", 3}, {"&&", 2}, {"||", 1}, {"(", 0} };

// returns true if the equation contains a boolean operator
bool EvaluatorHelper::isBooleanEquation(const string& equation) {
	istringstream tokens(equation);
	string token = "";
	bool inParentheses = false;
	int parenthesesCount = 0;
	while (tokens >> token) {
		if (parentheses.find(token) != -1) {
			if (parentheses.find(token) % 2 == 0)
				parenthesesCount++;
			else parenthesesCount--;
		}
		if (parenthesesCount == 0 && isBooleanOperator(token)) return true;
	}
	return false;
}

// returns true if the equation contains a math operator outside of parentheses
bool EvaluatorHelper::isMathEquation(const string& equation) {
	istringstream tokens(equation);
	string token = "";
	bool inParentheses = false;
	int parenthesesCount = 0;
	while (tokens >> token) {
		if (parentheses.find(token) != -1) {
			if (parentheses.find(token) % 2 == 0)
				parenthesesCount++;
			else parenthesesCount--;
		}
		if (parenthesesCount == 0 && isMathOperator(token)) return true;
	}
	return false;
}

// returns true if the string passed is a math operator
bool EvaluatorHelper::isMathOperator(const string& str) {
	string mathOperators = "-+*/%^";
	if (mathOperators.find(str) != -1)
		return true;
	else return false;
}

// returns true if the string passed is a boolean operator
bool EvaluatorHelper::isBooleanOperator(const string& str) {
	if (str == "!" || str == "!=" || str == "=="
		|| str == "<" || str == "<="
		|| str == ">" || str == ">="
		|| str == "&&" || str == "||")
		return true;
	else return false;
}

// returns true if the string passed is one of these (){}[]
bool EvaluatorHelper::isParentheses(const string& str) {
	if (parentheses.find(str) != -1) return true;
	else return false;
}

// returns true if the string passed is an operator
bool EvaluatorHelper::isOperator(const string& str) {
	std:map<string, int> ops = EvaluatorHelper::operators;
	for (std::map<string, int>::iterator iter = ops.begin(); iter != ops.end(); iter++)
		if (iter->first == str) return true;
	return false;
}

// returns true if the string passed is a unary operator (!, --, or ++)
bool EvaluatorHelper::isUnaryOperator(const string& str) {
	if (str == "!" || str == "++" || str == "--") return true;
	else return false;
}

// returns true if the character passed is an operator on its own
bool EvaluatorHelper::isOperator(const char& ch) {
	string singleCharOperators("*^%/");
	if (singleCharOperators.find(ch) != -1 || isParentheses(ch + ""))
		return true;
	else return false;
}

// returns true if the character passed is between and including 0 to 9
bool EvaluatorHelper::isDigit(const char& ch) {
	if (digits.find(ch) != -1) return true;
	else return false;
}

// returns true if the string passed is a number (positive or negative)
bool EvaluatorHelper::isNumber(const string& str) {
	if (str.length() == 0) return true;
	else if (str.length() == 1) return isDigit(str[0]);
	else {
		if (!isDigit(str[0]) && str[0] != '-') return false;
		else for (int i = 1; i < str.length(); i++)
			if (!isDigit(str[i])) return false;
		return true;
	}
}

// use this method to throw exceptions
void EvaluatorHelper::throwException(const string& exception) {
	throw exception;
}

// returns a string with the value of the first strings numerical value added to the integer passed
string EvaluatorHelper::addStringAndInt(const string& str, const int& i) {
	stringstream token(str);
	int a = 0;
	token >> a;
	return std::to_string(a + i);
}

// returns result based on the operation on two numbers(num1 and num2)
//   if a unary operator is passed, the operator will only be applied to the lhs
int EvaluatorHelper::evalOperation(const string& op, const int& lhs, const int& rhs) {
	// I am using the find function to convert so I can switch
	//   over the index of the operator in the following
	//   string   01234567890123
	string ops = "+-*/%^++--!>>=<<==!=&&||";
	int opID = ops.find(op);
	if ((opID == 3 || opID == 4) && rhs == 0) throwException("Cannot divide by zero."); // cannot divide by zero
	switch (opID) {
		case 0: return lhs + rhs; break;	 // +
		case 1: return lhs - rhs; break;	 // -
		case 2: return lhs * rhs; break;	 // *
		case 3: return lhs / rhs; break;	 // /
		case 4: return lhs % rhs; break;	 // %
		case 5: return pow(lhs, rhs); break; // ^
		case 6: return lhs + 1; break;		 // ++
		case 8: return lhs - 1; break;		 // --
		case 10: return !lhs; break;		 // !
		case 11: return lhs > rhs; break;	 // >
		case 12: return lhs >= rhs; break;   // >=
		case 14: return lhs < rhs; break;	 // <
		case 15: return lhs <= rhs; break;   // <=
		case 16: return lhs == rhs; break;	 // ==
		case 18: return lhs != rhs; break;	 // !=
		case 20: return lhs && rhs; break;	 // &&
		case 22: return lhs || rhs; break;	 // ||
		default: throwException("'" + op + "' is not a valid operator"); break; // anything else
	}
}

// returns true if the precedecne of op1 is greater than the precedence of op2
bool  EvaluatorHelper::isOperatorGreaterThan(const string& op1, const string& op2) {
	int op1Precedence;
	int op2Precedence;
	bool result = true;
	map<string, int> ops = EvaluatorHelper::operators;
	for (map<string, int>::iterator iter = ops.begin(); iter != ops.end(); iter++) {
		if (iter->first == op1) op1Precedence = iter->second;
		if (iter->first == op2) op2Precedence = iter->second;
	}
	return op1Precedence >= op2Precedence;
}

// returns the integer value of the passed string
int EvaluatorHelper::strToInt(const string& str) {
	stringstream stream(str);  // stream used to convert str to int
	int result = 0;
	stream >> result;  // reading the token as an integer
	return result;
}
