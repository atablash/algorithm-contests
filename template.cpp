#define READ_NUM_TEST_CASES  false
#define USE_FAST_IO          false
#include "include/template.hpp"

//#include <salgo/graph.hpp>
//#include <salgo/binomial.hpp>

struct Test_Case {

	int n, m, k;
	vector<int> in;

	void solve() {
		// cout << "Case #" << icase+1 << ": ";
		in.resize( ri() );
		FOR(i,n) cin >> in[i];
	}

	int icase = -1;
}; // struct Test_Case



int main() {
	int num_cases = READ_NUM_TEST_CASES ? ri() : 1;
	
	FOR(i, num_cases) {
		Test_Case tc;
		tc.icase = i;
		tc.solve();
	}

	return 0;
}

