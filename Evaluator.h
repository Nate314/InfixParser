#pragma once
#include "EvaluatorHelper.h"
#include "Tokenizer.h"
#include <stack>
#include <string>
#include <iostream>
using namespace std;

class Evaluator {
private:
	stack<int> numbers_stack; // stack holding all numbers
	stack<string> operators_stack; // stack holding all operators
	Tokenizer tokenizer = Tokenizer("");
	string token;
	int calc(); // whenever condensing the number_stack
	int calcUnaryOperator(string& op); // call from calc if the top operator is unary
	int calcNonUnaryOperator(string& op); // call from calc if the top operator is non unary
public:
	Evaluator();
	int eval(string equation); // pass an equation as a string and get the integer result back
};
