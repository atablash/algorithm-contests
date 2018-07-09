//#define READ_NUM_TEST_CASES
//#define USE_FAST_IO
#include "template.hpp"


struct Test_Case {


	void solve() {
		// cout << "Case #" << icase+1 << ": ";
	}

	int icase = 0;
}; // struct Test_Case



int main() {
	#ifdef READ_NUM_TEST_CASES
		int num_test_cases = ri();

		for(int i=0; i < num_test_cases; ++i) {
			Test_Case tc;
			tc.icase = i;
			tc.solve();
		}
	#else
		test_case(0);
	#endif

	return 0;
}
