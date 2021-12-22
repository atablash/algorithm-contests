
////////////////////////////////////////////////////////////////////////////////

struct Mod {
  //   F mult = 1;
  //   F add_each = 0;
};

struct Agg {
  //   F sum = 0;
  PII mx;

  void apply(const Mod &mod, int a, int b) {
    UNUSED(mod, a, b)
    // sum = sum * mod.mult + mod.add_each * (b - a);
  }
};

Mod combine(const Mod &a, const Mod &b) {
  UNUSED(a, b)
  Mod r;
  //   r.mult = a.mult * b.mult;
  //   r.add_each = a.add_each * b.mult + b.add_each;
  return r;
}

Agg combine(const Agg &a, const Agg &b) {
  Agg r;
  //   r.sum = a.sum + b.sum;
  r.mx = MAX(a.mx, b.mx);
  //   P("combine", a.sum, '+', b.sum, '=', r.sum)
  return r;
}

template <class AGG, class MOD> struct SegTree {
  struct V {
    AGG agg;
    MOD mod;
  };

  int x0;
  vector<V> vs;

  SegTree(int a, int b) : x0(a), vs(round_up_pow2(b - a) * 2) {
    CHECK_LT(a, b);
    V(SZ(vs))
  }

  SegTree() : SegTree(0, 2) {}

  void set(int x, Agg &&val) { vs[SZ(vs) / 2 + x].agg = move(val); }
  void build() {
    FORR(i, 1, SZ(vs) / 2)
    vs[i].agg = combine(vs[i * 2].agg, vs[i * 2 + 1].agg);
  }

  template <class FUN>
  void iter(int fr, int to, const FUN &fun, int v = 1, int a = 0, int b = 0) {
    if (v == 1) {
      a = x0;
      b = a + SZ(vs) / 2;
    }

    if (fr <= a && b <= to) {
      fun(vs[v], a, b);
      return;
    }

    CHECK_GE(b - a, 2)

    int mid = (a + b) / 2;

    FOR(c, 2) vs[v * 2 + c].mod = combine(vs[v * 2 + c].mod, vs[v].mod);
    vs[v * 2 + 0].agg.apply(vs[v].mod, a, mid);
    vs[v * 2 + 1].agg.apply(vs[v].mod, mid, b);
    vs[v].mod = MOD();

    if (fr < mid)
      iter(fr, to, fun, v * 2 + 0, a, mid);

    if (mid < to)
      iter(fr, to, fun, v * 2 + 1, mid, b);

    vs[v].agg = combine(vs[v * 2 + 0].agg, vs[v * 2 + 1].agg);
  }

  AGG agg(int fr, int to) {
    AGG r;
    iter(fr, to, [&](auto &vv, int a, int b) {
      V(a, b, vv.agg.mx)
      r = combine(r, vv.agg);
    });
    return r;
  }

  void mod(int fr, int to, const MOD &mod) {
    iter(fr, to, [&](auto &vv, int a, int b) {
      vv.mod = combine(vv.mod, mod);
      vv.agg.apply(mod, a, b);
    });
  }
};

using Tree = SegTree<Agg, Mod>;

////////////////////////////////////////////////////////////////////////////////
