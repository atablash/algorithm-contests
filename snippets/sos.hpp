////////////////////////////////////////////////////////////////////////////////
//
// snippets/sos.hpp
//
template <class D> struct Sos {
  vec<D> dp;
  Sos(int bits) : dp(1 << bits) {}

  void run() {
    auto bits = log2up(SZ(dp));

    FOR(b, bits)
    FOR(mask, 1 << bits)
    if (mask & (1 << b))
      dp[mask].add(dp[mask ^ (1 << b)]);
  }

  D &operator[](int i) { return dp[i]; }
};

/////

struct DP {
  int sum = 0;

  void add(const DP &o) {
    sum += o.sum;
    //
  }
};

using SOS = Sos<DP>;
////////////////////////////////////////////////////////////////////////////////
