#pragma once
#include <bits/stdc++.h>
using namespace std;






//
// snippets/linalg/2/vector.hpp
//
using F = long double;

struct Vec {
	array<F,2> pos = {{0, 0}};

	Vec() = default;
	Vec(const F& x, const F& y) : pos{{x,y}} {}

	F& operator[](int i) { return pos[i]; }
	const F& operator[](int i) const { return pos[i]; }

	Vec operator-() const {
		return {-pos[0], -pos[1]};
	}
};

F operator*(const Vec& a, const Vec& b) {
	return a[0] * b[0]  +  a[1] * b[1];
}

Vec operator+(const Vec& a, const Vec& b) {
	return Vec(a[0] + b[0], a[1] + b[1]);
}

Vec operator-(const Vec& a, const Vec& b) {
	return Vec(a[0] - b[0], a[1] - b[1]);
}


bool operator==(const Vec& a, const Vec& b) {
	return a.pos == b.pos;
}

ostream& operator<<(ostream& os, const Vec& vec) {
	os.precision(2);
	return os << "[" << vec.pos[0] << ", " << vec.pos[1] << "]";
}



F det(const Vec& a, const Vec& b) {
	return a[0] * b[1]  -  a[1] * b[0];
}

F orient(const Vec& a, const Vec& b, const Vec& c) {
	return det(b-a, c-a);
}


Vec operator*(const Vec& v, F alpha) {
	return {v[0] * alpha, v[1] * alpha};
}


Vec operator*(F alpha, const Vec& v) {
	return {v[0] * alpha, v[1] * alpha};
}

