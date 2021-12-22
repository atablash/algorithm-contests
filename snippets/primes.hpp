#pragma once
#include <bits/stdc++.h>
using namespace std;

const int PRIMES_LIMIT = 1e7;

VI lpd; // least prime divisor

VI get_primes(int limit) {
  VI primes;
  lpd.clear();
  lpd.resize(limit);

  FOR(i, 2, limit) {
    if (!lpd[i]) {
      primes.push_back(i);
      lpd[i] = i;
    }
    for (auto &p : primes) {
      if (p > lpd[i] || i * p >= limit)
        break;
      lpd[i * p] = p;
    }
  }

  return primes;
}

VI primes = get_primes(PRIMES_LIMIT);

VI divisors(int x) {
  VI r = {1};
  while (x > 1) {
    int p = lpd[x];
    int cnt = 0;
    while (lpd[x] == p) {
      ++cnt;
      x /= p;
    }
    int sz = SZ(r);
    FOR(i, sz) {
      int mult = 1;
      FOR(jj, cnt) {
        mult *= p;
        { r.push_back(r[i] * mult); }
      }
    }
  }
  return r;
}
