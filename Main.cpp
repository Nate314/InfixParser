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
	bool testing = true;
	if (testing) testEvaluator();
	else {
		Evaluator eval;
		 cout<<eval.eval("( ( 1 + 2 ) - 3 ) - 5") <<endl;
		 system("pause");
	}
	return 0;
}
