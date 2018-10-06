#include "Evaluator.h"

void testEvaluator() {
	Evaluator eval;
	string eq = "";
	while (true) {
		getline(cin, eq);
		int result = eval.eval(eq);
		cout << result << endl;
	}
	system("pause");
}

int main() {
	bool testing = false;
	if (testing) testEvaluator();
	else {
		Evaluator eval;
		cout << eval.eval("5*5-25<=3*--12") << endl;
		system("pause");
	}
	return 0;
}
