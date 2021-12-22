
template <class INT> struct Ranges {
  map<INT, INT> m;

  bool have(INT x) const {
    auto itr = m.upper_bound(x);
    return (itr != m.begin() && x < prev(itr)->second);
  }

  bool add(INT x) {
    auto itr = m.upper_bound(x);
    if (itr != m.begin() && x < prev(itr)->second)
      return false; // already have

    bool merge_with_left = itr != m.begin() && prev(itr)->second == x;
    bool merge_with_right = itr != m.end() && x + 1 == itr->first;

    if (merge_with_left && merge_with_right) {
      prev(itr)->second = itr->second;
      m.erase(itr);
    } else if (merge_with_left) {
      prev(itr)->second = x + 1;
    } else if (merge_with_right) {
      m[x] = itr->second;
      m.erase(itr);
    } else
      m[x] = x + 1;

    return true;
  }

  bool remove(INT x) {
    auto itr = m.upper_bound(x);
    if (itr == m.begin() || prev(itr)->second <= x)
      return false;

    auto p = prev(itr);

    if (p->second != x + 1)
      m[x + 1] = p->second;

    if (p->first != x)
      p->second = x;
    else
      m.erase(p);

    return true;
  }

  INT first_free(INT x0) const {
    auto itr = m.upper_bound(x0);
    if (itr == m.begin())
      return x0;
    return max(x0, prev(itr)->second);
  }
};
