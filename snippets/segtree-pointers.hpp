
////////////////////////////////////////////////////////////////////////////////

struct Mod {
  F mult = 1;
  F add_each = 0;
};

struct Agg {
  F sum = 0;

  void apply(const Mod &mod, int a, int b) {
    sum = sum * mod.mult + mod.add_each * (b - a);
  }
};

Mod combine(const Mod &a, const Mod &b) {
  Mod r;
  r.mult = a.mult * b.mult;
  r.add_each = a.add_each * b.mult + b.add_each;
  return r;
}

Agg combine(const Agg &a, const Agg &b) {
  Agg r;
  r.sum = a.sum + b.sum;
  //   P("combine", a.sum, '+', b.sum, '=', r.sum)
  return r;
}

template <class AGG, class MOD> struct SegTree {
  struct V {
    AGG agg;
    MOD mod;
    int c[2] = {0, 0};
  };

  vector<V> vs = vector<V>(2);

  SegTree(int a, int b) : x0(a), x1(b) {}

  template <class FUN>
  void iter(int fr, int to, const FUN &fun, int v = 1, int a = 0, int b = 0) {
    if (v == 1) {
      a = x0;
      b = x1;
    }

    if (fr <= a && b <= to) {
      fun(vs[v], a, b);
      return;
    }

    CHECK_GE(b - a, 2)

    if (!vs[v].c[0])
      FOR(c, 2) {
        vs[v].c[c] = SZ(vs);
        vs.emplace_back();
      }

    int mid = (a + b) / 2;

    FOR(c, 2) vs[vs[v].c[c]].mod = combine(vs[vs[v].c[c]].mod, vs[v].mod);
    vs[vs[v].c[0]].agg.apply(vs[v].mod, a, mid);
    vs[vs[v].c[1]].agg.apply(vs[v].mod, mid, b);
    vs[v].mod = MOD();

    if (fr < mid)
      iter(fr, to, fun, vs[v].c[0], a, mid);

    if (mid < to)
      iter(fr, to, fun, vs[v].c[1], mid, b);

    vs[v].agg = combine(vs[vs[v].c[0]].agg, vs[vs[v].c[1]].agg);
  }

  AGG agg(int fr, int to) {
    AGG r;
    iter(fr, to, [&](auto &vv, int, int) { r = combine(r, vv.agg); });
    return r;
  }

  void mod(int fr, int to, const MOD &mod) {
    // V(fr, to, mod.mult, mod.add_each)
    iter(fr, to, [&](auto &vv, int a, int b) {
      //   P("MOD", a, b, mod.mult, mod.add_each)
      vv.mod = combine(vv.mod, mod);
      vv.agg.apply(mod, a, b);
    });
  }

  //   // find first range that satisfies PRED
  //   template <class PRED>
  //   auto find_first(const PRED &pred, int v = 1, int a = 0, int b = 0) {
  //     if (v == 1) {
  //       a = x0;
  //       b = x1;
  //     }

  //     struct R {
  //       V *pv = 0;
  //       int a = 0;
  //       int b = 0;
  //     };

  //     if (!pred(vs[v], a, b))
  //       return R{0};

  //     if (!vs[v].l)
  //       return R{&vs[v], a, b};

  //     propagate(v);

  //     int mid = (a + b) / 2;

  //     auto r = find_first(pred, vs[v].l, a, mid);
  //     if (r.pv)
  //       return r;

  //     return find_first(pred, vs[v].r, mid, b);
  //   }

  //   auto find(int x) {
  //     return find_first([&](auto, int a, int b) { return a <= x && x < b;
  //     });
  //   }

  int x0, x1;
};

using Tree = SegTree<Agg, Mod>;

////////////////////////////////////////////////////////////////////////////////
