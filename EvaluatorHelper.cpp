#include "EvaluatorHelper.h"

// all parentheses values are stored here for reference
const string EvaluatorHelper::parentheses = "(){}[]";
// all digit values are stored here for reference
const string EvaluatorHelper::digits = "0123456789";
// all operators with specified precedencies are stored here for reference
const std::map<string, int> EvaluatorHelper::operators = { {")", 9}, {"!", 8}, {"++", 8}, {"--", 8}, {"^", 7},
									{"*", 6}, {"/", 6}, {"%", 6}, {"+", 5}, {"-", 5},
									{">", 4}, {">=", 4}, {"<", 4}, {"<=", 4},
									{"==", 3}, {"!=", 3}, {"&&", 2}, {"||", 1}, {"(", 0} };

// returns true if the equation contains a boolean operator
bool EvaluatorHelper::isBooleanEquation(string equation) {
	for (int i = 0; i < equation.length() - 1; i++) {
		string check = equation.substr(i, 1);
		if (isBooleanOperator(check)) return true;
	}
	return false;
}

// returns true if the string passed is a math operator
bool EvaluatorHelper::isMathOperator(string str) {
	if (str == "^" || str == "*"
		|| str == "/" || str == "%"
		|| str == "+" || str == "-")
		return true;
	else return false;
}

// returns true if the string passed is a boolean operator
bool EvaluatorHelper::isBooleanOperator(string str) {
	if (str == "!" || str == "!=" || str == "=="
		|| str == "<" || str == "<="
		|| str == ">" || str == ">="
		|| str == "&&" || str == "||")
		return true;
	else return false;
}

// returns true if the string passed is an increment or decrement operator
bool EvaluatorHelper::isIncrementDecrementOperator(string str) {
	if (str == "++" || str == "--") return true;
	else return false;
}

// returns true if the string passed is one of these (){}[]
bool EvaluatorHelper::isParentheses(string str) {
	if (parentheses.find(str) != -1) return true;
	else return false;
}

// returns true if the string passed is an operator
bool EvaluatorHelper::isOperator(string str) {
	std:map<string, int> ops = EvaluatorHelper::operators;
	for (std::map<string, int>::iterator iter = ops.begin(); iter != ops.end(); iter++)
		if (iter->first == str) return true;
	return false;
}

// returns true if the character passed is part of an operator
bool EvaluatorHelper::isPartOfOperator(char ch) {
	if (ch == '!' || ch == '=' || ch == '<' || ch == '>'
		|| ch == '|' || ch == '&' || ch == '+' || ch == '-'
		|| ch == '%' || ch == '*' || ch == '^'
		|| isParentheses(ch + ""))
		return true;
	else return false;
}

// returns true if the character passed is an operator on its own
bool EvaluatorHelper::isOperator(char ch) {
	if (ch == '*' || ch == '^' || ch == '%' || isParentheses(ch + ""))
		return true;
	else return false;
}

// returns true if the character passed is between and including 0 to 9
bool EvaluatorHelper::isDigit(char ch) {
	if (digits.find(ch) != -1) return true;
	else return false;
}

// returns true if the string passed is a number (positive or negative)
bool EvaluatorHelper::isNumber(string str) {
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
		bool shouldStartNewToken = (tokenLen == 2 && isOperator(token))
			|| (tokenLen == 1 && isPartOfOperator(token[0]) && ((isDigit(ch) || ch == '-') && token != "-"))
			|| (isOperator(token) && !isOperator(token + ch));
		bool shouldAddToToken = ((!isDigit(ch) && !isNumber(token))
				|| (isDigit(ch) && (isNumber(token) || token == "-")))
			&& !shouldStartNewToken;
		if (shouldAddToToken) token += ch;
		else {
			istringstream tempstream(token);
			int a = 0;
			tempstream >> a;
			//if (a < 0) {
			//	if(exp.size() > 0 && isNumber())
			//}
			if (a < 0 && (exp.size() > 0 ? isNumber(exp[exp.size() - 1]) : false)) exp.push_back("+");
			exp.push_back(token);
			token = ch;
		}
		/*
		bool a = ((isPartOfOperator(ch) || isOperator(ch)) && ((token.length() == 1 ? isPartOfOperator(token[0]) : isOperator(token)) || token == ""));
		bool b = (token == "-" && isDigit(ch));
		bool c = (isDigit(ch) && isNumber(token));
		bool d = (isDigit(ch) && (isOperator(token) || token == ""));
		bool e = (isPartOfOperator(ch) && isNumber(token));
		// if ch is part of an operator
		// if ch is right after a '-' and ch is a digit
		// if ch is a digit, and the token is currently a number
		if (a || b || c) {
			if (isOperator(token + ch) || isNumber(token + ch)) token += ch;
			else {
				exp.push_back(token);
				token = ch;
			}
		}
		// if ch is a digit and the token is a non '-' token
		// if ch is an operator and the token is a number
		else if (d || e) {
			istringstream tempstream(token);
			int a = 0;
			tempstream >> a;
			if (a < 0 && (exp.size() > 0 ? isNumber(exp[exp.size() - 1]) : false)) exp.push_back("+");
			exp.push_back(token);
			token = ch;
		}
		*/
	}
	// concatentate result;
	if (token != "") exp.push_back(token);
	for (int i = 0; i < exp.size(); i++) {
		if (i > 0 && i < exp.size() - 1) {
			// if previous and next tokens are both math operators
			if ((isMathOperator(exp[i - 1]) || isParentheses(exp[i - 1])) && (isMathOperator(exp[i + 1]) || isParentheses(exp[i + 1]))) {
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
void EvaluatorHelper::throwException(string exception) {
	// TODO: actually throw exception
	cout << "EXCEPTION: " << exception << endl;
}

// returns a string with the value of the first strings numerical value added to the integer passed
string EvaluatorHelper::addStringAndInt(string str, int i) {
	stringstream token(str);
	int a = 0;
	token >> a;
	return std::to_string(a + i);
}
