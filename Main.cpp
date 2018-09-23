#include "Evaluator.h"

int main() {
	Evaluator eval;
	int result = eval.eval("3 >= (5 != 18)");
	return 0;
}
