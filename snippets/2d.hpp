#pragma once






template<class T, int dim>
class Point {
	array<T,dim> v = {};

public:
	template<class... TT, class = std::enable_if_t<sizeof...(TT) == dim>>
	Point(TT&&... args) : v{ std::forward<TT>(args)... } {}

	Point() = default;
	Point(const Point&) = default;

	auto& operator[](int i) { return v[i]; }

	auto& operator+=(const Point& o) { FOR(i,v.size()) v[i] += o.v[i]; return *this; }
	auto& operator-=(const Point& o) { FOR(i,v.size()) v[i] -= o.v[i]; return *this; }

	auto operator+(const Point& o) const { return Point(*this) += o; }
	auto operator-(const Point& o) const { return Point(*this) -= o; }
};




auto det(Point<int,2> a, Point<int,2> b) {
	//DBG << "det (" << a[0] << "," << a[1] << ") (" << b[0] << "," << b[1] << ")" << endl;
	return 1LL*a[0] * b[1]  -  1LL*a[1] * b[0];
}



template<class PT>
auto orient(const PT& a, const PT& b, const PT& c) {
	//DBG << "is_turning_left: " << det(b-a, c-a) << endl;
	return det(b-a, c-a);
}

