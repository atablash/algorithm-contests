
////////////////////////////////////////////////////////////////////////////////
//
// snippets/union-find.hpp
//
struct UF {
  struct V {
    int p = 0; // parent
    int size = 1;

    int best = -1;
    int best_arg;

    void aggregate(V &o) {
      size += o.size;
      //
    }
  };

  vec<V> vs;
  int merges = 0;

  int find(int v) {
    if (!range(v, 0, SZ(vs)))
      return v;

    if (vs[v].p == v)
      return v;

    int p = vs[v].p;
    int root = find(p);
    vs[v].p = root;

    return root;
  }

  void access(int a) {
    CHECK_GE(a, 0);
    FOR(i, SZ(vs), a + 1) {
      vs.emplace_back();
      vs.back().p = i;
    }
  }

  bool merge(int a, int b) {
    auto aa = find(a);
    auto bb = find(b);
    if (aa == bb)
      return false;

    access(a);
    access(b);

    if (vs[aa].size > vs[bb].size)
      swap(aa, bb);

    vs[aa].p = bb;
    vs[bb].aggregate(vs[aa]);

    ++merges;
    return true;
  }

  bool same(int a, int b) { return find(a) == find(b); }

  auto &operator[](int v) {
    access(v);
    return vs[find(v)];
  }
};
////////////////////////////////////////////////////////////////////////////////
