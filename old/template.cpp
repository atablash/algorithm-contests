#define READ_NUM_TEST_CASES  false
#define USE_FAST_IO          false
#include "include/template.hpp"

//#include <salgo/graph.hpp> // c++17
//#include <salgo/binomial.hpp>
//#include <salgo/modulo.hpp>
//#include <salgo/common.hpp>


struct Test_Case {

	//int n = RI;
	//int m = RI;
	//int k = RI;

	vector<int> in;

	void solve() {
		// cout << "Case #" << icase+1 << ": ";
		in.resize( RI );
		FOR(i,n) in[i] = RI;
	}

	int icase = -1;
}; // struct Test_Case



int main() {
	int num_cases = READ_NUM_TEST_CASES ? RI : 1;
	
	FOR(i, num_cases) {
		Test_Case tc;
		tc.icase = i;
		tc.solve();
	}

	return 0;
}

