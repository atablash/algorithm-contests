#define USE_FAST_IO          false
#include "include/template.hpp"

//#include <salgo/graph.hpp> // c++17
//#include <salgo/binomial.hpp>
//#include <salgo/common.hpp>

int rand(int num) { return rand()%num; } // [0,num) exclusive
int rand(int mi, int ma) { return mi + rand(ma-mi+1); } // [mi,ma] inclusive




//
// edit here:
int num_cases = 0;
//
//


struct Test_Case {

	void generate() {
		// cout << "Case #" << icase+1 << ": ";
		int n = 10;
		cout << n << endl;

		FOR(i,n) {
			cout << rand(100) << " ";
		}
		cout << endl;
	}

	int icase = -1;
}; // struct Test_Case








//
// don't edit
//
int main(int argc, char* argv[]) {
	if(argc != 2) { cout << "usage: " << argv[0] << " SEED" << endl; return 1; }
	srand(stoi(argv[1]));

	if(num_cases) cout << num_cases << endl;
	else num_cases = 1;

	FOR(i, num_cases) {
		Test_Case tc;
		tc.icase = i;
		tc.generate();
	}

	return 0;
}

