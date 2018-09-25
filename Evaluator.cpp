#include "Evaluator.h"
#include "EvaluatorHelper.h"
#include <stack>
#include <sstream>

Evaluator::Evaluator() {
	// nothing needed in constructor
}

int Evaluator::eval(string equation) {
	try {
		equation = EvaluatorHelper::fixSpaces(equation);
		// resulting int to return
		int result = 0;
		// check if the equation passed has any boolean operators
		bool isEquationABooleanEquation = EvaluatorHelper::isBooleanEquation(equation);
		// if the equation passed has boolean operators,
		//   evaluate each math portion and build string for boolean equation
		// stream of tokens in the equation
		istringstream tokens(equation);
		// current token being iterated over
		string token = "";
		// math equation will include numbers and operators like +, -, *, /, ^, and %
		string mathEquation = "";
		// boolean equation will include numbers and operators like <, >, ==, !, !=, <=, >=, &&, and ||
		string booleanEquation = "";
		// the next three variables are used for keeping track of parentheses in the equation
		string parenthesesEquation = "";
		int isParenthesesCount = 0;
		bool isParentheses = false;
		// loop through each token in the equation
		while (tokens >> token) {
			// if the token is a parentheses
			if (EvaluatorHelper::parentheses.find(token) != -1) {
				bool isOpen = EvaluatorHelper::parentheses.find(token) % 2 == 0;
				// if the token is an open parentheses
				if (isOpen) {
					isParentheses = true;
					isParenthesesCount++;
					continue;
				}
				// if the token is a closing parentheses
				else {
					isParenthesesCount--;
					// if this closing parentheses cancels out all opening parentheses
					if (isParenthesesCount == 0) {
						isParentheses = false;
						// make recursive call
						string parenthesesEquationResult = to_string(eval(parenthesesEquation));
						if (isEquationABooleanEquation) booleanEquation += parenthesesEquationResult + " ";
						else mathEquation += parenthesesEquationResult + " ";
						parenthesesEquation = "";
						continue;
					}
					else if(isParenthesesCount < 0)
						EvaluatorHelper::throwException("mismatched parentheses");
				}
			}
			// if this token is between parentheses
			if (isParenthesesCount > 0) {
				parenthesesEquation += token + " ";
			}
			// if this token is not between parentheses
			else {
				if (isEquationABooleanEquation) {
					if (EvaluatorHelper::isBooleanOperator(token)) {
						string booleanEquationPiece = std::to_string(evalPostMath(toPostMath(mathEquation))) + " " + token + " ";
						booleanEquation += booleanEquationPiece;
						mathEquation = "";
					}
					else
						mathEquation += token + " ";
				}
				else
					mathEquation += token + " ";
			}
		}
		if (parenthesesEquation != "")
			EvaluatorHelper::throwException("mismatched parentheses");
		else {
			if (isEquationABooleanEquation) {
				if (mathEquation != "") booleanEquation += to_string(evalPostMath(toPostMath(mathEquation)));
				return evalPostBool(toPostBool(booleanEquation));
			}
			else {
				return evalPostMath(toPostMath(mathEquation));
			}
		}
	}
	catch (string e) {
		cerr << e << endl;
	}
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
	stack<int>numbers_stack; //create a new stack which will contain only numbers

	istringstream tokens(equation); //process each token from the postfix expression
	string token; 
	while (tokens >> token) {
		if (EvaluatorHelper::isNumber(token)) { // if the token in the string is a Number push it to the stack
			stringstream temp(token);  //temp token to store the token read
			int number;
			temp >> number;  //reading the token as an integer
			numbers_stack.push(number); //push the integer to the number stack
		}
		else if (EvaluatorHelper::isMathOperator(token)) { //else if token is an operator pop the top two numbers from stack
			int number2 = numbers_stack.top(); numbers_stack.pop(); 
			int number1 = numbers_stack.top(); numbers_stack.pop();
			int result = EvaluatorHelper::evalOperation(token, number1, number2);  //evaluate the operation on two numbers
			numbers_stack.push(result);  //push the result to the stack
		}
		else {
			EvaluatorHelper::throwException("Invalid character!"); //exception, if invalid character is found
		}
	}
	if (!numbers_stack.empty()) { //checking if stack is not empty
		int result = numbers_stack.top(); //final result will be on top of stack, pop the top elemnent
		numbers_stack.pop();  
		if (numbers_stack.empty()) {  //if stack is empty after popping result, return the final result
			return result;
		}
		else  EvaluatorHelper::throwException("Stack is not empty");  //exception, if stack is not empty
	}
	// if stack of operands is empty, something went wrong
	else EvaluatorHelper::throwException("No operands were found in evalPostMath()");
}

// Brian
string Evaluator::toPostBool(string equation) {
	if (equation == "") { // May remove later. This is to account for when equation is empty. This can be checked for earlier.
		cout << "Equation to be acted on cannot be empty." << endl;
		return equation;
	}

	// string testEquation = "442 <= 3 ! 17"; //		TESTING PURPOSES

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
    if(equation == ""){
        cout << "Equation to be acted on cannot be empty." << endl;
        return equation;
    }
    
    stack<string> operators;
    istringstream tokens(equation);
    string currentChar = "";
    string postfixEquation = "";
    
    while(tokens >> currentChar){
        if(EvaluatorHelper::isNumber(currentChar)){
            postfixEquation.append(currentChar);
            postfixEquation.append(" ");
        }
        else{
            if(operators.size() == 0){
                operators.push(currentChar);
                continue;
            }
            auto currentCharPrec = EvaluatorHelper::operators.find(currentChar);
            auto topPrec = EvaluatorHelper::operators.find(operators.top());
            while(operators.size() != 0 && currentCharPrec->second <= topPrec->second){
                postfixEquation.append(operators.top());
                postfixEquation.append(" ");
                operators.pop();
            }
            operators.push(currentChar);
        }
    }
    while(operators.size() != 0){
        postfixEquation.append(operators.top());
        postfixEquation.append(" ");
        operators.pop();
    }
    return postfixEquation;
}
