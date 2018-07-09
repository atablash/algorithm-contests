#pragma once

#define uint unsigned int

#define ll long long
#define ull unsigned long long


auto ri()   { int r; cin >> r; return r; }
auto rui()  { uint r; cin >> r; return r; }

auto rll()  { ll r;  cin >> r; return r; }
auto rull() { ull r; cin >> r; return r; }

auto rstr() {string s; cin >> s; return s; }


#define REP(i,n) for(int i=0; i<int(n); ++i)
#define FOR(i,a,b) for(int i=(a); i<int(b); ++i)
#define ROF(i,a,b) for(int i=(a)-1; i>=int(b); --i)



#define min(a,b) ((a<b) ? (a) : (b))
#define max(a,b) ((a>b) ? (a) : (b))
