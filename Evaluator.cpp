#include "Evaluator.h"
#include "EvaluatorHelper.h"
#include <stack>
#include <sstream>

Evaluator::Evaluator() {
	// nothing needed in constructor
}

int Evaluator::eval(string equation) {
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
		result = evalPostMath(toPostMath(equation));
	}
	// return result
	return result;
}

// Nathan
bool Evaluator::evalPostBool(string equation) {
	// stack of operands to be populated and processed
	stack<int> operands;
	// Process each token
	istringstream tokens(equation);
	string token;
	while (tokens >> token) {
		// if the token is a number, add to the stack of operands
		if (EvaluatorHelper::isNumber(token)) {
			stringstream temp_stream(token);
			int value;
			temp_stream >> value;
			operands.push(value);
		}
		// if the token is an operator, evaluate the top two elements
		//   of the operand stack with respect to the token
		//   and replace those two elements of the stack with the result
		else if (EvaluatorHelper::isOperator(token)) {
			int right = -1;
			if (token != "!") {
				right = operands.top();
				operands.pop();
			}
			int left = operands.top();
			operands.pop();
			int result = EvaluatorHelper::evalBool(left, right, token);
			operands.push(result);
		}
		// invalid character found, throw error
		else EvaluatorHelper::throwException("Character '" + token + "' is not a valid character");
	}
	// if stack of operands is not empty
	if (!operands.empty()) {
		int result = operands.top();
		operands.pop();
		// return top item of stack
		if (operands.empty()) return result;
		// if there are more items in the stack, then something went wrong
		else EvaluatorHelper::throwException("Stack should be empty");
	}
	// if stack of operands is empty, something went wrong
	else EvaluatorHelper::throwException("No operands were found in evalPostBool()");
}

// Angad
int Evaluator::evalPostMath(string equation) {
	return 5;
}

// Brian
string Evaluator::toPostBool(string equation) {
	if (equation == "") { // May remove later. This is to account for when equation is empty. This can be checked for earlier.
		cout << "Equation to be acted on cannot be empty." << endl;
		return equation;
	}

	string testEquation = "442 <= 3 ! 17"; //		TESTING PURPOSES

	stack <string> operators; // Create a stack to hold the operators in the equation
	istringstream tokens(equation); // This will grab all characters up until a space and store them into tokens
	string currentChar = ""; // Variable to hold current character of the equation
	string postfixEquation = ""; // Variable that will be the postfix version of the equation

	while (tokens >> currentChar) { // As long as the end of the equation has not been reached, continue executing

		if (EvaluatorHelper::isNumber(currentChar)) { // If currentChar is a number, append it directly to postfixEquation
			postfixEquation.append(currentChar);
			postfixEquation.append(" "); // Add back the space
		}

		else { // If currentChar is not a number, it is an operator

			if (operators.size() == 0) { // If the operator stack is empty, just add the operator to the stack and then go to the next loop iteration
				operators.push(currentChar);
				continue;
			}

			auto currentCharPrec = EvaluatorHelper::operators.find(currentChar); // This will be used to hold the precedence value of the currentChar
			auto topPrec = EvaluatorHelper::operators.find(operators.top()); // This will hold the precendence value of the item at the top of the stack

			while ((operators.size()) != 0 && (currentCharPrec->second <= topPrec->second)) { // If the stack is not empty, and the precedence of currentChar is smaller or equal to the top of the stack,
				postfixEquation.append(operators.top()); // Then append all operators to postfixEquation until the stack is empty or a smaller precedence is found
				postfixEquation.append(" "); // Add back the space
				operators.pop(); // Pop the top item after it has been appended to postFixEquation
			}

			operators.push(currentChar); // Push the current char on the stack now that the operators with higher precendence have been removed
		}
	}

	while (operators.size() != 0) { // Add in the remaining operators to postfixEquation
		postfixEquation.append(operators.top());
		postfixEquation.append(" "); // Add back the space
		operators.pop();
	}

	/*
	cout << equation << endl;
	cout << postfixEquation << endl;			TESTING PURPOSES
	system("pause");
	*/

	return postfixEquation; // Return the postfixEquation to be used in other functions
}

// Lee
string Evaluator::toPostMath(string equation) {
	return "5 7 +";
}
