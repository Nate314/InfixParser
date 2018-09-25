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

// returns true if the string passed is an increment or decrement operator
bool EvaluatorHelper::isIncrementDecrementOperator(const string& str) {
	if (str == "++" || str == "--") return true;
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

// returns true if the character passed is part of an operator
bool EvaluatorHelper::isPartOfOperator(const char& ch) {
	string operatorParts = "!=<>|&+-%*/^";
	if (operatorParts.find(ch) != -1 || isParentheses(ch + ""))
		return true;
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

// returns a version of the expression passed with one space between each token
string EvaluatorHelper::fixSpaces(string expression) {
	string result = "";
	string temp = "";
	// remove spaces
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] != ' ') temp += expression[i];
	}
	expression = temp;
	char ch = ' ';
	string token = "";
	istringstream tokens(expression);
	vector<string> exp;
	// iterate through each character and add each token to the vector exp
	while (tokens >> ch) {
		int tokenLen = token.length();
		bool shouldStartNewToken = (isOperator(token) && !isOperator(token + ch))
			|| (isNumber(token) && !isNumber(token + ch));
		bool isNegativeNumber = (token == "-" && isDigit(ch));
		if (!shouldStartNewToken || isNegativeNumber) token += ch;
		else {
			istringstream tempstream(token);
			int a = 0;
			tempstream >> a;
			if (a < 0 && (exp.size() > 0 && (exp[exp.size() - 1] == ")" || isNumber(exp[exp.size() - 1])))) exp.push_back("+");
			if (isNumber(token) || isOperator(token) || token == "") {
				if (token != "") exp.push_back(token);
			}
			else throwException(token + " is an invalid character/operator");
			token = ch;
		}
	}
	// concatentate result;
	if (token != "" && (isNumber(token) || isOperator(token))) {
		istringstream tempstream(token);
		int a = 0;
		tempstream >> a;
		if (a < 0 && (exp.size() > 0 && (exp[exp.size() - 1] == ")" || isNumber(exp[exp.size() - 1])))) exp.push_back("+");
		if (isNumber(token) || isOperator(token) || token == "") {
			if (token != "") exp.push_back(token);
		}
		else throwException(token + " is an invalid character/operator");
		token = ch;
	}
	else throwException(token + " is an invalid character/operator");
	for (int i = 0; i < exp.size(); i++) {
		if (i > 0 && i < exp.size() - 1) {
			// if previous and next tokens are both math operators
			//if ((isMathOperator(exp[i - 1]) || isParentheses(exp[i - 1])) && (isMathOperator(exp[i + 1]) || isParentheses(exp[i + 1]))) {
			if (isMathOperator(exp[i - 1]) && isMathOperator(exp[i + 1])) {
				if (exp[i] == "--" || exp[i] == "++")
					throwException("input cannot have three mathematical operators in a row.");
				else result += exp[i] + " ";
			}
			// if previous token is a math operator and the next token is a number
			else if ((isMathOperator(exp[i - 1]) || isParentheses(exp[i - 1])) && isNumber(exp[i + 1])) {
				if (exp[i] == "--") {
					result += addStringAndInt(exp[i + 1], -1) + " ";
					i++;
				}
				else if (exp[i] == "++") {
					result += addStringAndInt(exp[i + 1], 1) + " ";
					i++;
				}
				else result += exp[i] + " ";
			}
			// if previous token is a number and the next token is a math operator
			else if (isNumber(exp[i - 1]) && (isMathOperator(exp[i + 1]) || isParentheses(exp[i + 1]))) {
				if (exp[i] == "--" || exp[i] == "++")
					throwException("input cannot have '--' or '++' right before a math operator.");
				else result += exp[i] + " ";
			}
			// if previous and next tokens are both math operators
			else if (isNumber(exp[i - 1]) && isNumber(exp[i + 1])) {
				if (exp[i] == "--" || exp[i] == "++")
					throwException("input cannot have '--' or '++' between two numbers.");
				else result += exp[i] + " ";
			}
			// all other cases
			else {
				if (exp[i] == "--") {
					result += addStringAndInt(exp[i + 1], -1) + " ";
					i++;
				}
				else if (exp[i] == "++") {
					result += addStringAndInt(exp[i + 1], 1) + " ";
					i++;
				}
				else result += exp[i] + " ";
			}
		}
		else if (i == 0) {
			if (exp[i] == "--") {
				result += addStringAndInt(exp[i + 1], -1) + " ";
				i++;
			}
			else if (exp[i] == "++") {
				result += addStringAndInt(exp[i + 1], 1) + " ";
				i++;
			}
			else result += exp[i] + " ";
		}
		else if (i == exp.size() - 1) {
			if (exp[i] == "--" || exp[i] == "++") throwException("input cannot end with a '--' or a '++'.");
			else result += exp[i];
		}
	}
	// return result
	return result;
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

// returns a 0 or 1 based on (left token right)
int EvaluatorHelper::evalBool(const int& left, const int& right, const string& op) {
	// I am using the find function to convert so I can switch
	//   over the index of the operator in the following
	//   string   01234567890123
	string ops = "!>>=<<==!=&&||";
	int opID = ops.find(op);
	switch (opID) {
		case 0: return !left; break; // !
		case 1: return left > right; break; // >
		case 2: return left >= right; break; // >=
		case 4: return left < right; break; // <
		case 5: return left <= right; break; // <=
		case 6: return left == right; break; // ==
		case 8: return left != right; break; // !=
		case 10: return left && right; break; // &&
		case 12: return left || right; break; // ||
		default: throwException("'" + op + "' is not a valid boolean operator"); break; // anything else
	}
}

// returns result based on the operation on two numbers(num1 and num2)
int EvaluatorHelper::evalOperation(const string& op, const int& num1, const int& num2) {
	if (op == "+")
		return (num1 + num2);
	else if (op == "*")
		return (num1 * num2);
	else if (op == "-")
		return (num1 - num2);
	else if (op == "/") {
		if (num2 == 0) throwException("cannot divide by zero");
		else return (num1 / num2);
	}
	else if (op == "%")
		return (num1 % num2);
	else if (op == "^")
		return pow(num1, num2);
	return -1;
}