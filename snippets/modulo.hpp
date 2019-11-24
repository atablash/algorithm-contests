#pragma once
#include <bits/stdc++.h>
using namespace std;




//
// snippets/modulo.hpp
//
uint32_t MOD=1234;

class Modulo {
public:
	using H = uint32_t;
	H h = 0;

public:
	Modulo() = default;
	Modulo(H x) : h( x % MOD ) {}

	Modulo(const Modulo&) = default;

public:
	Modulo& operator+=(const Modulo& o) {
		h += o.h;
		if(h >= MOD) h -= MOD;
		return *this;
	}

	Modulo& operator-=(const Modulo& o) {
		h = MOD + h - o.h;
		if(h >= MOD) h -= MOD;
		return *this;
	}

	Modulo& operator*=(const Modulo& o) {
		h = (1ULL * h * o.h) % MOD;
		return *this;
	}

	Modulo& operator/=(const Modulo& o) {
		const auto TOTIENT = MOD-1;
		*this *= int_pow(o, TOTIENT-1);
		return *this;
	}

	bool operator==(const Modulo& o) const { return h == o.h; }
	bool operator!=(const Modulo& o) const { return h != o.h; }


	Modulo operator+(const Modulo& o) const { return Modulo(*this) += o; }
	Modulo operator-(const Modulo& o) const { return Modulo(*this) -= o; }
	Modulo operator*(const Modulo& o) const { return Modulo(*this) *= o; }
	Modulo operator/(const Modulo& o) const { return Modulo(*this) /= o; }



	Modulo& operator--()    { if(h == 0) h = MOD; --h; return *this; }
	Modulo& operator++()    { ++h; if(h == MOD) h = 0; return *this; }
	Modulo  operator--(int) { auto m = *this; --(*this); return m; }
	Modulo  operator++(int) { auto m = *this; ++(*this); return m; }



	explicit operator H() const { return h; }
};

ostream& operator<<(ostream& os, const Modulo& modulo) {
	return os << modulo.h;
}

