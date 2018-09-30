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
	stack<string> operators; // stack holding all operators
	int calc(Tokenizer& tokens, string& token); // whenever condensing the number_stack
	int calcUnaryOperator(Tokenizer& tokens, string& token, string& op); // call from calc if the top operator is unary
	int calcNonUnaryOperator(Tokenizer& tokens, string& token, string& op); // call from calc if the top operator is non unary
public:
	int eval(string equation); // pass an equation as a string and get the integer result back
};
