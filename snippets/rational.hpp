#pragma once




//
// snippets/rational.hpp
//
template<class T>
struct R {
	T numer = T(0);
	T denom = T(1);

	R() = default;
	R(T x) : numer(x) {}
	R(T n, T d) : numer(n), denom(d) {}

	R& gcd() {
		//auto g = __gcd(denom, numer);
		//numer /= g;
		//denom /= g;
		//if(denom < 0) {
		//	numer *= -1;
		//	denom *= -1;
		//}

		// rounding...
		//while(fabs(numer) > 2 * 1000 * 1000 * 1000  ||  fabs(denom) > 2 * 1000 * 1000 * 1000) {
		//	numer /= 2;
		//	denom /= 2;
		//	if(denom == 0) cerr << "asd " << numer << endl;
		//}

		//assert(denom > 0);

		return *this;
	}

	const R& operator+() const { return *this; }

	R operator-() const {
		return R{ -numer, denom };
	}

	T eval() const {
		return numer / denom;
	}

	R& operator+=(const R& o) {
		return *this = *this + o;
	}

	R& operator-=(const R& o) {
		return *this = *this - o;
	}

	R& operator*=(const R& o) {
		return *this = *this * o;
	}

	R& operator/=(const R& o) {
		return *this = *this / o;
	}
};

template<class T>
ostream& operator<<(ostream& os, const R<T>& r) {
	return os << r.numer << "/" << r.denom;
}

template<class T>
R<T> operator*(const R<T>& a, const R<T>& b) {
	R<T> r = {a.numer * b.numer, a.denom * b.denom};
	return r.gcd();
}

template<class T>
R<T> operator/(const R<T>& a, const R<T>& b) {
	R<T> r = {a.numer * b.denom, a.denom * b.numer};
	return r.gcd();
}


template<class T>
R<T> operator+(const R<T>& a, const R<T>& b) {
	R<T> r = {
		a.numer * b.denom + b.numer * a.denom,
		a.denom * b.denom
	};
	return r.gcd();
}

template<class T>
R<T> operator-(const R<T>& a, const R<T>& b) {
	R<T> r = {
		a.numer * b.denom - b.numer * a.denom,
		a.denom * b.denom
	};
	return r.gcd();
}


template<class T>
bool isnan(const R<T>& r) {
	return r.numer == 0 && r.denom == 0;
}

