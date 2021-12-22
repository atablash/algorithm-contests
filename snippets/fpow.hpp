#pragma once

template <class T, class E> T fpow(T a, E exp) {
  T r = 1;
  while (exp) {
    if (exp & 1) {
      r *= a;
      --exp;
    } else {
      exp >>= 1;
      a *= a;
    }
  }
  return r;
}
