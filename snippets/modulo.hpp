////////////////////////////////////////////////////////////////////////////////

const int MOD = 1e9 + 7;
const int MOD = 998'244'353;

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

class F {
public:
  using H = int;
  H h = 0;

public:
  F() = default;

  F(H x)
      : h((x + MOD) % MOD){CHECK_GE(x + MOD, 0)}

        F(const F &) = default;

public:
  F &operator+=(const F &o) {
    h += o.h;
    if (h >= MOD)
      h -= MOD;
    return *this;
  }

  F &operator-=(const F &o) {
    h = MOD + h - o.h;
    if (h >= MOD)
      h -= MOD;
    return *this;
  }

  F &operator*=(const F &o) {
    h = (1ULL * h * o.h) % MOD;
    return *this;
  }

  F &operator/=(const F &o) {
    const auto TOTIENT = MOD - 1;
    *this *= fpow(o, TOTIENT - 1);
    return *this;
  }

  bool operator==(const F &o) const { return h == o.h; }
  bool operator!=(const F &o) const { return h != o.h; }

  F operator+(const F &o) const { return F(*this) += o; }
  F operator-(const F &o) const { return F(*this) -= o; }
  F operator*(const F &o) const { return F(*this) *= o; }
  F operator/(const F &o) const { return F(*this) /= o; }

  F &operator--() {
    if (h == 0)
      h = MOD;
    --h;
    return *this;
  }
  F &operator++() {
    ++h;
    if (h == MOD)
      h = 0;
    return *this;
  }
  F operator--(int) {
    auto m = *this;
    --(*this);
    return m;
  }
  F operator++(int) {
    auto m = *this;
    ++(*this);
    return m;
  }

  explicit operator H() const { return h; }
};

ostream &operator<<(ostream &os, const F &modulo) { return os << modulo.h; }

////////////////////////////////////////////////////////////////////////////////
