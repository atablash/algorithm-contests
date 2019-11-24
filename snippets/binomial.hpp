#pragma once


//
// snippets/binomial.hpp
//
template<class VAL>
struct Binomial {
	int n = 0;
	int k = 0;
	VAL val = (VAL)1;

public:
	Binomial() = default;

	// hack
	Binomial(int nn, int kk, const VAL& vv) : n(nn), k(kk), val(vv) {}


	VAL operator()(int nn, int kk) {
		if(outside(nn,kk)) return VAL(0);

		while(k > kk) move_l();
		while(n > nn) move_u();
		while(n < nn) move_d();
		while(k < kk) move_r();

		return val;
	}

	static bool outside(int nn, int kk) {
		return nn < 0 || kk < 0 || kk > nn;
	}

	void move_l() {
		--k;
		val *= VAL(k+1);
		val /= VAL(n-k);
	}

	void move_r() {
		++k;
		val *= VAL(n-k+1);
		val /= VAL(k);
	}

	void move_d() {
		++n;
		val *= VAL(n);
		val /= VAL(n-k);
	}

	void move_u() {
		--n;
		val *= VAL(n-k+1);
		val /= VAL(n+1);
	}
};
