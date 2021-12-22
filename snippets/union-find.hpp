#pragma once

struct UF {
  struct V {
    int p = 0; // parent
    int size = 1;

    void aggregate(V &o) {
      size += o.size;
      //
    }
  };

  vector<V> vs;

  int find(int v) {
    CHECK_GE(v, 0);
    FOR(i, SZ(vs), v + 1) {
      vs.emplace_back();
      vs.back().p = i;
    };
    if (vs[v].p == v)
      return v;

    int p = vs[v].p;
    int root = find(p);
    vs[v].p = root;

    return root;
  }

  void merge(int a, int b) {
    auto aa = find(a);
    auto bb = find(b);
    if (aa == bb)
      return;

    if (vs[aa].size > vs[bb].size) {
      swap(aa, bb);
    }

    vs[aa].p = bb;
    vs[bb].aggregate(vs[aa]);
  }

  auto &operator[](int v) { return vs[find(v)]; }
};
