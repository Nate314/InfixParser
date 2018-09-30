#include "Evaluator.h"
#include "EvaluatorHelper.h"
#include "Tokenizer.h"

Tokenizer::Tokenizer(string expression) {
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
		bool shouldStartNewToken = (EvaluatorHelper::isOperator(token) && !EvaluatorHelper::isOperator(token + ch))
			|| (EvaluatorHelper::isNumber(token) && !EvaluatorHelper::isNumber(token + ch));
		bool isNegativeNumber = (token == "-" && EvaluatorHelper::isDigit(ch));
		if (!shouldStartNewToken || isNegativeNumber) token += ch;
		else {
			istringstream tempstream(token);
			int a = 0;
			tempstream >> a;
			if (a < 0 && (exp.size() > 0 && (exp[exp.size() - 1] == ")" || EvaluatorHelper::isNumber(exp[exp.size() - 1])))) exp.push_back("+");
			if (EvaluatorHelper::isNumber(token) || EvaluatorHelper::isOperator(token) || token == "") {
				if (token != "") exp.push_back(token);
			}
			else EvaluatorHelper::throwException(token + " is an invalid character/operator");
			token = ch;
		}
	}
	// concatentate result;
	if (token != "" && (EvaluatorHelper::isNumber(token) || EvaluatorHelper::isOperator(token))) {
		istringstream tempstream(token);
		int a = 0;
		tempstream >> a;
		if (a < 0 && (exp.size() > 0 && (exp[exp.size() - 1] == ")" || EvaluatorHelper::isNumber(exp[exp.size() - 1])))) exp.push_back("+");
		if (EvaluatorHelper::isNumber(token) || EvaluatorHelper::isOperator(token) || token == "") {
			if (token != "") exp.push_back(token);
		}
		else EvaluatorHelper::throwException(token + " is an invalid character/operator");
		token = ch;
	}
	else EvaluatorHelper::throwException(token + " is an invalid character/operator");
	for (int i = 0; i < exp.size(); i++) {
		if (i > 0 && i < exp.size() - 1) {
			// if previous and next tokens are both math operators
			//if ((isMathOperator(exp[i - 1]) || isParentheses(exp[i - 1])) && (isMathOperator(exp[i + 1]) || isParentheses(exp[i + 1]))) {
			if (EvaluatorHelper::isMathOperator(exp[i - 1]) && EvaluatorHelper::isMathOperator(exp[i + 1])) {
				if (exp[i] == "--" || exp[i] == "++")
					EvaluatorHelper::throwException("input cannot have three mathematical operators in a row.");
				else result += exp[i] + " ";
			}
			// if previous token is a math operator and the next token is a number
			else if ((EvaluatorHelper::isMathOperator(exp[i - 1]) || EvaluatorHelper::isParentheses(exp[i - 1])) && EvaluatorHelper::isNumber(exp[i + 1])) {
				if (exp[i] == "--") {
					result += EvaluatorHelper::addStringAndInt(exp[i + 1], -1) + " ";
					i++;
				}
				else if (exp[i] == "++") {
					result += EvaluatorHelper::addStringAndInt(exp[i + 1], 1) + " ";
					i++;
				}
				else result += exp[i] + " ";
			}
			// if previous token is a number and the next token is a math operator
			else if (EvaluatorHelper::isNumber(exp[i - 1]) && (EvaluatorHelper::isMathOperator(exp[i + 1]) || EvaluatorHelper::isParentheses(exp[i + 1]))) {
				if (exp[i] == "--" || exp[i] == "++")
					EvaluatorHelper::throwException("input cannot have '--' or '++' right before a math operator.");
				else result += exp[i] + " ";
			}
			// if previous and next tokens are both math operators
			else if (EvaluatorHelper::isNumber(exp[i - 1]) && EvaluatorHelper::isNumber(exp[i + 1])) {
				if (exp[i] == "--" || exp[i] == "++")
					EvaluatorHelper::throwException("input cannot have '--' or '++' between two numbers.");
				else result += exp[i] + " ";
			}
			// all other cases
			else {
				if (exp[i] == "--") {
					result += EvaluatorHelper::addStringAndInt(exp[i + 1], -1) + " ";
					i++;
				}
				else if (exp[i] == "++") {
					result += EvaluatorHelper::addStringAndInt(exp[i + 1], 1) + " ";
					i++;
				}
				else result += exp[i] + " ";
			}
		}
		else if (i == 0) {
			if (exp[i] == "--") {
				result += EvaluatorHelper::addStringAndInt(exp[i + 1], -1) + " ";
				i++;
			}
			else if (exp[i] == "++") {
				result += EvaluatorHelper::addStringAndInt(exp[i + 1], 1) + " ";
				i++;
			}
			else result += exp[i] + " ";
		}
		else if (i == exp.size() - 1) {
			if (exp[i] == "--" || exp[i] == "++") EvaluatorHelper::throwException("input cannot end with a '--' or a '++'.");
			else result += exp[i];
		}
	}

	istringstream toVector (result); // String stream that will insert the now spaced-out equation into the eqpPieces vector
	string currentPiece = ""; // This variable will hold the current chunk of the equation to be inserted into the vector

	while (toVector >> currentPiece) // Keep executing as long as there are tokens left in toVector
		Tokenizer::eqnPieces.push_back(currentPiece); // Add the current piece of the equation to the eqnPieces vector

	currentPosition = 0; // Initialize currentPosition to 0
}

string Tokenizer::next() {
	if (eqnPieces.size() == 0) // If the vector of items is empty, return nothing, because there is nothing to be returned
		return "";

	else {
		if ((currentPosition + 1) == eqnPieces.size()) // If we are at the end of the vector, return nothing
			return "";

		currentPosition++; // Increment currentPosition for the next use
		return eqnPieces[currentPosition - 1]; // Return the item in the [currentPosition - 1] spot so the correct item is returned
	}
}