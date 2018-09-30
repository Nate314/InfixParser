#include "Evaluator.h"

// pass an equation as a string and get the integer result back
int Evaluator::eval(string equation) {
	try {
		while (!operators.empty()) operators.pop();
		while (!numbers_stack.empty()) numbers_stack.pop();
		Tokenizer tokenizer(equation); // process each token
		string token;

		while (true) {
			token = tokenizer.next();
			if (token == "") break;
			if (EvaluatorHelper::isNumber(token)) // if the token in the string is a Number push it to the stack
				numbers_stack.push(EvaluatorHelper::strToInt(token)); // push the integer to the number stack
			else if (EvaluatorHelper::isMathOperator(token)
				|| EvaluatorHelper::isBooleanOperator(token)
				|| EvaluatorHelper::isUnaryOperator(token)
				|| EvaluatorHelper::isParentheses(token)) { // if the token is a operator or a paranthesis
				if (token == "(") // check if token is a left paranthsies then push to operator stack
					operators.push(token);
				else if (token == ")") { // if token is a right paranthsies(matching paranthesis)
					while (!operators.empty() && operators.top() != "(") // making sure top of stack is a closing paranthesis
						numbers_stack.push(calc(tokenizer, token));
					operators.pop(); // pop opening paranthesis as we are done evalauting operation
				}
				else {
					// while the operator on top of stack has a precedence greater than or same as the current token(operator)
					while (!operators.empty() && EvaluatorHelper::isOperatorGreaterThan(operators.top(), token))
						numbers_stack.push(calc(tokenizer, token));
					// After evaluating push current token to operator stack 
					if (EvaluatorHelper::isOperator(token)) operators.push(token);
				}
			}
		}
		// This is for rest of the cases when all values have been evaluated in paranthesis 
		//   evaluate the remaining operations left in the stack
		while (!operators.empty())
			numbers_stack.push(calc(tokenizer, token));
		if (!numbers_stack.empty()) { // checking if stack is not empty
			int result = numbers_stack.top(); // final result will be on top of stack, pop the top elemnent
			numbers_stack.pop();
			if (numbers_stack.empty()) // if stack is empty after popping result, return the final result
				return result;
			else  EvaluatorHelper::throwException("Syntax error");  // exception, if stack is not empty
		}
	}
	// catch all exceptions and print to console
	catch (string e) {
		cout << e << endl;
	}
}

// whenever condensing the number_stack
int Evaluator::calc(Tokenizer& tokenizer, string& token) {
	// pop the top operator
	string op = operators.top(); 
	operators.pop();
	// call appropriate function based on the type of op
	if (EvaluatorHelper::isUnaryOperator(op)) return calcUnaryOperator(tokenizer, token, op);
	else return calcNonUnaryOperator(tokenizer, token, op);
}

// call from calc if the top operator is non unary
int Evaluator::calcNonUnaryOperator(Tokenizer& tokenizer, string& token, string& op) {
	if (numbers_stack.size() >= 2) {
		// pop the top two numbers from stack
		int number2 = numbers_stack.top();
		numbers_stack.pop();
		int number1 = numbers_stack.top();
		numbers_stack.pop();
		// evaluate the result
		return EvaluatorHelper::evalOperation(op, number1, number2);
	}
	else EvaluatorHelper::throwException("Mismatching operators");
}
// call from calc if the top operator is unary
int Evaluator::calcUnaryOperator(Tokenizer& tokenizer, string& token, string& op) {
	int result;
	// initialize unary_operators with the operator passed
	stack<string> unary_operators;
	unary_operators.push(op);
	if (EvaluatorHelper::isUnaryOperator(token)) {
		// add all unary operators after current unary operator
		while (EvaluatorHelper::isUnaryOperator(token)) {
			unary_operators.push(token);
			token = tokenizer.next();
		}
		// push the token to number_stack if it is a number
		if (EvaluatorHelper::isNumber(token)) numbers_stack.push(EvaluatorHelper::strToInt(token));
		else EvaluatorHelper::throwException("Mismatching operators");
	}
	// initialize result as the top number in the number stack
	if (numbers_stack.size() != 0) {
		result = numbers_stack.top();
		numbers_stack.pop();
	}
	else EvaluatorHelper::throwException("Mismatching operators");
	// perform all unary operators in a row
	while (!unary_operators.empty()) {
		result = EvaluatorHelper::evalOperation(unary_operators.top(), result, 0);
		unary_operators.pop();
	}
	// return result
	return result;
}
