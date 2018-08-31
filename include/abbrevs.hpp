#pragma once

#define UI unsigned int

#define LL long long
#define ULL unsigned long long

#define PII pair<int,int>


#define RI ri()
#define RUI rui()

#define RLL rll()
#define RULL rull()

#define RSTR rstr()



#define FOR(i,n) for(int i=0, _end=(n); i<_end; ++i)
#define FO(i,a,b) for(int i=(a); i<int(b); ++i)
#define OF(i,a,b) for(int i=(b)-1; i>=int(a); --i)



#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((b)<(a) ? (a) : (b))

#define REMIN(a,b) ((a) = min(a,b))
#define REMAX(a,b) ((a) = max(a,b))

#define ALL(c) (c).begin(),(c).end()

#define SQR(x) ((x)*(x))



bool is_pow(int x) {
	return (x&(x-1)) == 0;
}

