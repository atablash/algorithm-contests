////////////////////////////////////////////////////////////////////////////////
//
// snippets/splay.hpp
//
struct Mod {};

struct Agg {
  //   int id = 0;
  int size = 0;

  void apply(const Mod &mod) {
    UNUSED(mod)
    //
  }
};

Agg combine(const Agg &a, const Agg &b) {
  Agg r;
  //   r.id = MIN(a.id, b.id);
  r.size = a.size + b.size;
  return r;
}

Mod combine(const Mod &a, const Mod &b) {
  UNUSED(a, b)
  Mod r;
  //
  return r;
}

// 1-based indices
template <class AGG, class MOD> struct Splay {

  int index_of(int v) {
    splay(v);
    return vs[v].c[0] ? vs[vs[v].c[0]].agg.size : 0;
  }
  int ith(int v, int ith) {
    return find_first(v, [&](auto &agg, auto &) {
      //   V(agg.size, ith);
      return agg.size >= ith;
    });
  }

  struct SplayNode {
    //
    AGG val;
    AGG agg;
    MOD mod;
    //
    //   int shift = 0;
    //   int shift_mod = 0;
    //

    int c[2] = {0, 0}; // children
    int p = 0;         // parent

    void print() {
      P("SplayNode")
      INDENT
      V(val.id, val.size, agg.size)
    }
  };

  // subtree did change
  void aggregate(int v) {
    auto &vv = vs[v];
    vv.agg = vv.val;

    auto l = vv.c[0];
    if (l)
      vv.agg = combine(vs[l].agg, vv.agg);

    auto r = vv.c[1];
    if (r)
      vv.agg = combine(vv.agg, vs[r].agg);

    // CHECK(vv.mod == MOD()); // todo?
    // vv.agg.apply(vv.mod);
  }

  // will enter subtree
  void propagate(int v) {
    auto &vv = vs[v];
    FOR(c, 2) if (vv.c[c]) {
      auto &cc = vs[vv.c[c]];
      cc.mod = combine(cc.mod, vv.mod);
      cc.agg.apply(vv.mod);
    }
    vv.mod = MOD();
  }

  vector<SplayNode> vs;

  Splay() : vs(1) {}
  Splay(int size) : vs(1) { FOR(i, size) insert(); }

  int is_ith(int v) const { return vs[vs[v].p].c[1] == v; }

  void rotate(int v) {
    CHECK_GT(v, 0)
    CHECK_GT(vs[v].p, 0)
    // if (!vs[v].p) {
    //   return;
    // }

    int ith = is_ith(v);
    int p = vs[v].p;       // parent
    int g = vs[p].p;       // grand-parent
    int i = vs[v].c[!ith]; // inner child

    // if (g)
    //   propagate(g);

    propagate(p);
    propagate(v);

    vs[v].p = g;
    if (g) {
      vs[g].c[is_ith(p)] = v;
    }

    vs[v].c[!ith] = p;
    vs[p].p = v;

    vs[p].c[ith] = i;
    vs[i].p = p;

    aggregate(p);
    aggregate(v);
  }

  void splay(int v) {
    CHECK_GT(v, 0)
    for (;;) {
      int p = vs[v].p; // parent
      if (!p)
        break;

      int g = vs[p].p;
      if (!g) {
        rotate(v);
        break;
      }

      if (is_ith(v) == is_ith(p)) {
        rotate(p);
        rotate(v);
      } else {
        rotate(v);
        rotate(v);
      }
    }
    CHECK_EQ(vs[v].p, 0)
  }

  void link(int c, int p, int ith) {
    CHECK_NE(c, p)
    CHECK(!vs[c].p);
    CHECK(!vs[p].c[ith]);
    propagate(p);
    vs[c].p = p;
    vs[p].c[ith] = c;
    aggregate(p);
  }

  void unlink(int c) {
    CHECK(c);
    CHECK(vs[c].p);
    int p = vs[c].p;
    propagate(p);
    int ith = is_ith(c);
    vs[c].p = 0;
    vs[p].c[ith] = 0;
    aggregate(p);
  }

  int merge(int a, int b) {
    CHECK_NE(a, b)
    CHECK(!same(a, b))
    a = last(a);
    b = first(b);

    link(a, b, 0);
    return b;
  }

  int cut_after(int v, bool after = true) {
    splay(v);
    int c = vs[v].c[after];
    if (!c)
      return 0;
    unlink(c);
    return c;
  }

  int cut_before(int v) { return cut_after(v, false); }

  // does not splay
  int next(int v, bool forward = true) {
    propagate(v);
    if (vs[v].c[forward]) {
      v = vs[v].c[forward];
      propagate(v);
      while (vs[v].c[!forward]) {
        v = vs[v].c[!forward];
        propagate(v);
      }
      return v;
    } else
      for (;;) {
        int p = vs[v].p;
        if (!p)
          return 0;

        if (is_ith(v) != forward)
          return p;
        v = p;
        propagate(v);
      }
  }

  // does not splay
  int prev(int x) { return next(x, false); }

  int last(int v, bool forward = true) {
    splay(v);
    while (vs[v].c[forward])
      v = vs[v].c[forward];
    splay(v);
    return v;
  }

  int first(int v) { return last(v, false); }

  int insert() {
    vs.emplace_back();
    vs.back().val.size = 1;
    // vs.back().val.id = SZ(vs) - 1;
    aggregate(SZ(vs) - 1);
    return SZ(vs) - 1;
  }

  int insert_after(int v) {
    int vv = insert();
    splay(v);
    if (!vs[v].c[1])
      link(vv, v, 1);
    else {
      v = next(v);
      link(vv, v, 0);
    }
    splay(vv);
    return vv;
  }

  int insert_before(int v) {
    int vv = insert();
    splay(v);
    if (!vs[v].c[0])
      link(vv, v, 0);
    else {
      v = prev(v);
      link(vv, v, 1);
    }
    splay(vv);
    return vv;
  }

  AGG &agg(int v) {
    splay(v);
    return vs[v].agg;
  }

  bool same(int a, int b) {
    if (a == b)
      return true;
    splay(a);
    splay(b);
    return vs[a].p;
  }

  // find first element that satisfies PRED(AGG smaller, AGG self)
  template <class PRED> int find_first(int v, const PRED &pred) {
    CHECK(v)
    splay(v);

    int last = 0;
    int cand = 0;

    AGG agg0;

    for (;;) {
      last = v;
      propagate(v);
      AGG agg1 = agg0;
      int l = vs[v].c[0];
      if (l)
        agg1 = combine(agg0, vs[l].agg);
      bool op_result = pred(agg1, vs[v].val);

      if (op_result) {
        cand = v;
        v = vs[v].c[0];
        if (!v)
          break;
      } else {
        agg0 = combine(agg1, vs[v].val);
        v = vs[v].c[1];
        if (!v)
          break;
      }
    }

    if (last)
      splay(last);

    if (cand)
      splay(cand);

    return cand;
  }

  void print(int v = 1) {
#ifdef LOCAL
    CHECK(v)
    if (!v)
      P("Splay empty")
    else {
      vs[v].print();

      P("|")
      P("+- CHILD L")
      if (vs[v].c[0]) {
        INDENT
        print(vs[v].c[0]);
      }

      P("|")
      P("+- CHILD R")
      if (vs[v].c[1]) {
        INDENT
        print(vs[v].c[1]);
      }
    }
#endif
  }

  // helpers
  SplayNode &operator[](int v) { return vs[v]; }
};

using Tree = Splay<Agg, Mod>;
////////////////////////////////////////////////////////////////////////////////
