#include "Evaluator.h"
#include "EvaluatorHelper.h"
#include <stack>
#include <sstream>

Evaluator::Evaluator() {
	// nothing needed in constructor
}

int Evaluator::eval(string equation) {
	stack<int> numbers_stack; //stack holding all numbers
	stack<string> operators; //stack holding all operators
	istringstream tokens(equation); //process each token
	string token;

	while (tokens >> token) {
		if (EvaluatorHelper::isNumber(token)) { // if the token in the string is a Number push it to the stack
			stringstream temp(token);  //temp token to store the token read
			int number;
			temp >> number;  //reading the token as an integer
			numbers_stack.push(number); //push the integer to the number stack
		}
		else if (EvaluatorHelper::isMathOperator(token) || EvaluatorHelper::isParentheses(token)) { //if the token is a operator or a paranthesis
			 if (token == "(") { //check if token is a left paranthsies then push to operator stack
				operators.push(token);
			}

			else if (token == ")") //if token is a right paranthsies(matching paranthesis)
			{
				while (!operators.empty() && operators.top() != "(") //making sure top of stack is a closing paranthesis
				{
					//pop the top two numbers from stack
					int number2 = numbers_stack.top(); 
					numbers_stack.pop();
					int number1 = numbers_stack.top();
					numbers_stack.pop();
					string operator_str = operators.top(); //pop the top operator to perfrom operation(closing paranthesis)
					operators.pop();
					//evaluate the result of the numbers in paranthesis and push result to stack
					int result = EvaluatorHelper::evalOperation(operator_str, number1, number2);
					numbers_stack.push(result); 
				}
				operators.pop(); // pop opening paranthesis as we are done evalauting operation
			}
			else
			{
				//while the operator on top of stack has a precedence greater than or same as the current token(operator)
				while (!operators.empty() && EvaluatorHelper::isOperatorGreaterThan(operators.top(),token)) {
					//pop the top two numbers from stack and apply the operator on top of the stack to the numbers 
					int number2 = numbers_stack.top();
					numbers_stack.pop();
					int number1 = numbers_stack.top();
					numbers_stack.pop();
					string operator_str = operators.top(); //pop the top operator to perfrom operation
					operators.pop();
					//evaluate the result of the numbers and push result to numbers stack
					int result = (EvaluatorHelper::evalOperation(operator_str, number1, number2));
					numbers_stack.push(result);
				}
				// After evaluating push current token to operator stack 
				operators.push(token);
			}
		}
	}
	//This is for rest of the cases when all values have been evaluated in paranthesis 
	//evaluate the remaining operations left in the stack
		while (!operators.empty()) {
			int number2 = numbers_stack.top();
			numbers_stack.pop();
			int number1 = numbers_stack.top();
			numbers_stack.pop();
			string operators_str = operators.top();  //pop the top operator to perfrom operation
			operators.pop();
			//evaluate the result and push it to the numbers stack
			int result = EvaluatorHelper::evalOperation(operators_str, number1, number2);
			numbers_stack.push(result);
		}
		if (!numbers_stack.empty()) { //checking if stack is not empty
			int result = numbers_stack.top(); //final result will be on top of stack, pop the top elemnent
			numbers_stack.pop();
			if (numbers_stack.empty()) {  //if stack is empty after popping result, return the final result
				return result;
			}
			else  EvaluatorHelper::throwException("Stack is not empty");  //exception, if stack is not empty
		}
}

