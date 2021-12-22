
// miller-rabin
// p_max == 4,759,123,141 ( > 2^32)
bool is_prime(const unsigned int p) {
  if ((p & 1) == 0)
    return false;
  if (p < 2)
    return false;

  unsigned int d = p - 1;
  int s = 0;
  while ((d & 1) == 0) {
    ++s;
    d >>= 1;
  }

  array<unsigned int, 3> tt = {2, 7, 61};

  for (auto t : tt) {
    if (p <= t)
      continue;

    H1X a(p, t); // mod p
    // int a = rand()%(p-2) + 2;
    H1X x = bin_pow(a, d);
    if (x == 1 || x == p - 1)
      continue;

    int j;
    for (j = 0; j < s - 1; ++j) {
      x *= x; // mod p
      if (x == 1)
        return false;
      if (x == p - 1)
        break;
    }

    if (j == s - 1)
      return false;
  }

  return true;
}
