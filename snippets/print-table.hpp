#pragma once
#include <bits/stdc++.h>
using namespace std;





//
// snippets/print-table.hpp
//
string pad(string s, int len = 8, char c = ' ') {
	return string(len-s.size(), c) + s;
}

template<class DATA>
void print_table(const DATA& data, int N, int K) {
	FOR(n, N) {
		FOR(k, K) {
			ostringstream ss;
			ss << data[n][k].eval().h;
			cerr << pad(ss.str(), 10, ' ');
		}
		cerr << endl;
	}
}

