//#define READ_NUM_TEST_CASES
//#define USE_FAST_IO
#include "template.hpp"




void test_case(int) {
	
}



int main() {
	#ifdef READ_NUM_TEST_CASES
		int num_test_cases = ri();

		for(int i=0; i < num_test_cases; ++i) {
			test_case(i);
		}
	#else
		test_case(0);
	#endif

	return 0;
}
