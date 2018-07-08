#define USE_FAST_IO
#include "template.hpp"




void test_case(int) {
	int test;
	cin >> test;
	cout << "entered: " << test << endl;
}



int main() {
	int num_test_cases = ri();

	for(int i=0; i < num_test_cases; ++i) {
		test_case(i);
	}

	return 0;
}
