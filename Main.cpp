#include "Evaluator.h"

int main() {
	Evaluator eval;
	int result = eval.eval("!(++5+--7)*9<=9+--3*4");
	return 0;
}
