#pragma once

#define LSB(S) (S & (-S)) // least significant bit

// 1-indexed
template <class T> struct FW {
  vector<T> v;

  FW(int n) : v(n + 1) {}

  // range [1..x]
  int sum(int x) {
    int sum = 0;
    for (; x; x -= LSB(x))
      sum += v[x];
    return sum;
  }

  void update(int x, int change) {
    for (; x <= SZ(v) - 1; x += LSB(x))
      v[x] += change;
  }
};
