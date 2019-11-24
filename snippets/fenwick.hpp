#pragma once





//
// snippets/fenwick.hpp
//
#define LSOne(S) (S & (-S))

class BIT {
	int* ft, size;
public:
	// initialize a BIT of n elements to zero
	BIT(int n) {
		size = n;
		ft = new int[n+1];
	}

	~BIT()	{
		delete [] ft;
	}

	// returns sum of the range [1...b]
	int sum(int b) {
		int sum = 0;
		for (; b; b -= LSOne(b)) sum += ft[b];
		return sum;
	}

	// update value of the k-th element by v (v can be +ve/inc or -ve/dec)
	// i.e., increment or decrement kth element by a value v
	void update(int k) {
		for (; k <= size; k += LSOne(k)) ++ft[k];
	}
};

