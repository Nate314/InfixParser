#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Tokenizer {
private:
	vector <string> eqnPieces; // Vector that will store the pieces of the equation
	int currentPosition;
	bool empty(); // Returns true if the eqnPieces vector is empty and false otherwise


public:
	Tokenizer(string expression); // Constructor that takes in the equation as its only parameter and fills the eqnPieces vector
	string next(); // Function that will return the next item in the vector
	string end(); // Returns the element at the end of the eqnPieces vector
};