#pragma once


//
// snippets/int-pow.hpp
//
template<class T, class E, class OP>
T int_pow(T a, E exp, const OP& op, const T& neutral) {

	auto r = neutral;
	while(exp != 0) {
		if((exp & 1) != 0) {
			op(r, a);
			--exp;
		}
		else{
			exp >>= 1;
			op(a, a);
		}
	}
	return r;
}

template<class T, class E>
T int_pow(const T& a, const E& exp) {
	auto lambda = [](T& aa, const T& bb){ aa *= bb; };
	return int_pow<T,E,decltype(lambda)>(a, exp, lambda, T(1));
}

