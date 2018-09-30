#pragma once
#include "EvaluatorHelper.h"
#include <string>
#include <vector>
using namespace std;

class Tokenizer {
private:
	vector <string> eqnPieces; // Vector that will store the pieces of the equation
	int currentPosition;
public:
	Tokenizer(string expression); // Constructor that takes in the equation as its only parameter and fills the eqnPieces vector
	string next(); // Function that will return the next item in the vector
	void correctOps(vector<string> & eqn);
};
