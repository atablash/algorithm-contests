//#define READ_NUM_TEST_CASES
//#define USE_FAST_IO
#include "template.hpp"


struct Test_Case {


	void solve() {
		// cout << "Case #" << icase+1 << ": ";
	}

	int icase = -1;
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
		Test_Case tc;
		tc.icase = -1;
		tc.solve();
	#endif

	return 0;
}
