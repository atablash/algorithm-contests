
struct SplayRanges {
  using Node = SplayNode;

  SplayRanges(int a, int b) : x0(a) {
    tree[1].length = tree[1].length_sum = b - a;
  }

  struct R {
    int v = 0;
    int a = 0;
    int b = 0;
  };

  template <class FUN> auto find_first(const FUN &fun) {
    // P("SplayRanges.find_first")
    R cand;
    int x = x0;
    tree.find_first([&](int v) {
      int a = x;
      if (tree[v].c[0])
        a += tree[tree[v].c[0]].length_sum;

      int b = a + tree[v].length;

      if (fun(tree[v], a, b)) {
        cand.v = v;
        cand.a = a;
        cand.b = b;
        return true;
      } else {
        x = b;
        return false;
      }
    });
    // V(cand.v)
    return cand;
  }

  auto find(int x) {
    // cerr << "SplayRanges.find " << x << endl;
    return find_first([x](auto, int, int b) {
      // P("find", x, "in [", a, b, ")");
      return x < b;
    });
  }

  template <class FUN> void process(int fr, int to, const FUN &fun) {
    auto first = find(fr);
    auto last = find(to - 1);
    CHECK(first.v)
    CHECK(last.v)

    // PRINT("process")
    // PRINT(fr)
    // PRINT(to)
    // PRINT(first.a)
    // PRINT(first.b)
    // PRINT(last.a)
    // PRINT(last.b)

    if (first.a < fr) {
      tree.splay(first.v);
      tree[first.v].length = first.b - fr;
      tree.aggregate(first.v);
      int vv = tree.insert_before(first.v);
      tree.splay(vv);
      tree[vv].length = fr - first.a;
      tree[vv].shift = tree[first.v].shift;
      tree.aggregate(vv);
    }

    if (to < last.b) {
      tree.splay(last.v);
      tree[last.v].length = to - last.a;
      tree.aggregate(last.v);
      int vv = tree.insert_after(last.v);
      tree.splay(vv);
      tree[vv].length = last.b - to;
      tree[vv].shift = tree[last.v].shift;
      tree.aggregate(vv);
    }

    tree.splay(first.v);
    int before_first = tree[first.v].c[0];
    // PRINT(before_first)
    if (before_first)
      tree.unlink(before_first);

    tree.splay(last.v);
    int after_last = tree[last.v].c[1];
    if (after_last)
      tree.unlink(after_last);

    fun(last.v, fr, to);
    tree.propagate(last.v);
    tree.aggregate(last.v);

    tree.splay(last.v);
    if (after_last)
      tree.link(after_last, last.v, 1);

    tree.splay(first.v);
    if (before_first)
      tree.link(before_first, first.v, 0);
  }

  int x0;
  Splay tree = Splay(1);
  auto &operator[](int i) { return tree[i]; }
};
