
// 1-based indices
struct SplayNode {
  //
  int length = 0;
  int length_sum = 0;
  // int x = 0;
  //
  int shift = 0;
  int shift_mod = 0;
  //

  int c[2] = {0, 0}; // children
  int p = 0;         // parent

  void print() {
    P("SplayNode")
    INDENT
    V(length)
    V(length_sum)
    V(shift)
    V(shift_mod)
    // V(x);
    // V(shift);
    // V(shift_mod)
  }
};
struct Splay {

  void aggregate(int v) {
    vs[v].length_sum = vs[v].length;
    // vs[v].num = 0;
    // vs[v].sum = 0;

    if (vs[v].c[0]) {
      vs[v].length_sum += vs[vs[v].c[0]].length_sum;
      //   vs[v].num += vs[vs[v].c[0]].num;
      //   vs[v].sum += vs[vs[v].c[0]].sum;
    }

    if (vs[v].c[1]) {
      vs[v].length_sum += vs[vs[v].c[1]].length_sum;
      //   vs[v].num += vs[vs[v].c[1]].num;
      //   vs[v].sum += vs[vs[v].c[1]].sum;
    }
  }

  void propagate(int v) {
    if (vs[v].c[0]) {
      vs[vs[v].c[0]].shift_mod += vs[v].shift_mod;
      vs[vs[v].c[0]].shift += vs[v].shift_mod;
    }

    if (vs[v].c[1]) {
      vs[vs[v].c[1]].shift_mod += vs[v].shift_mod;
      vs[vs[v].c[1]].shift += vs[v].shift_mod;
    }

    vs[v].shift_mod = 0;
  }

  vector<SplayNode> vs;
  int last_root = 0;

  Splay() : vs(1) {}
  Splay(int size) : vs(size + 1) {
    if (size >= 1)
      last_root = 1;
  }

  int is_ith(int v) const { return vs[vs[v].p].c[1] == v; }

  void rotate(int v) {
    CHECK_GT(v, 0)
    if (!vs[v].p) {
      last_root = v;
      return;
    }

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

    if (!g)
      last_root = v;
  }

  void link(int c, int p, int ith) {
    CHECK(!vs[c].p);
    CHECK(!vs[p].c[ith]);
    propagate(p);
    vs[c].p = p;
    vs[p].c[ith] = c;
    aggregate(p);

    if (!vs[p].p)
      last_root = p;
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
  }

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

  int first(int v) {
    for (;;) {
      int vv = prev(v);
      if (!vv)
        return v;
      v = vv;
    }
  }

  int last(int v) {
    for (;;) {
      int vv = next(v);
      if (!vv)
        return v;
      v = vv;
    }
  }

  int insert(SplayNode &&node = SplayNode()) {
    vs.emplace_back(std::move(node));
    if (!last_root)
      last_root = SZ(vs) - 1;
    return SZ(vs) - 1;
  }

  int insert_after(int v, SplayNode &&node = SplayNode()) {
    int vv = insert(std::move(node));
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

  int insert_before(int v, SplayNode &&node = SplayNode()) {
    int vv = insert(std::move(node));
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

  // find first element that satisfies PRED
  template <class PRED> int find_first(const PRED &pred, int v = 0) {
    // V(last_root)
    if (!v)
      v = last_root;

    if (!v)
      return 0;

    splay(v);

    int last = 0;
    int cand = 0;

    for (;;) {
      last = v;
      propagate(v);
      bool op_result = pred(v);

      if (op_result) {
        cand = v;
        v = vs[v].c[0];
        if (!v)
          break;
      } else {
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

  void print(int v = 0) {
    if (!v)
      v = last_root;

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
  }

  // helpers
  SplayNode &operator[](int v) { return vs[v]; }
};