#include <bits/stdc++.h>

using namespace std;

template <typename Info, typename Index = int, bool Persistent = false>
class DynamicSimpleSegmentTree {
 public:
  struct Node {
    array<int, 2> c;
    Info d;
  };

  Index n;
  vector<Node> nodes;

  DynamicSimpleSegmentTree() : DynamicSimpleSegmentTree(0, -1) {}
  DynamicSimpleSegmentTree(Index n_) : DynamicSimpleSegmentTree(n_, -1) {}
  DynamicSimpleSegmentTree(const vector<Info>& a) : DynamicSimpleSegmentTree(a, -1) {}

  DynamicSimpleSegmentTree(Index n_, int q) : n(n_) {
    if (q >= 0) {
      nodes.reserve(2 + q * bit_width(make_unsigned_t<Index>(2 * n - 1)));
    }
    nodes.resize(2);
    nodes[1] = {{-1, -1}, Info::GetDefault(0, n)};
  }

  DynamicSimpleSegmentTree(const vector<Info>& a, int q) : n(int(a.size())) {
    if (q >= 0) {
      nodes.reserve(2 * n + q * bit_width(make_unsigned_t<Index>(2 * n - 1)));
    }
    nodes.resize(2 * n);
    auto Build = [&](auto&& self, int id, int nl, int nr) -> void {
      if (nr - nl == 1) {
        nodes[id] = {{-1, -1}, a[nl]};
        return;
      }
      int mid = (nl + nr) >> 1;
      array<int, 2> c = {id + 1, id + 2 * (mid - nl)};
      self(self, c[0], nl, mid);
      self(self, c[1], mid, nr);
      nodes[id] = {c, nodes[c[0]].d.Unite(nodes[c[1]].d)};
    };
    Build(Build, 1, 0, n);
  }

  int SetImpl(int root, Index p, const Info& v, Index nl, Index nr) {
    int me;
    if (root == -1) {
      me = int(nodes.size());
      nodes.push_back({{-1, -1}, Info::GetDefault(nl, nr)});
    } else {
      if (Persistent) {
        me = int(nodes.size());
        nodes.push_back(nodes[root]);
      } else {
        me = root;
      }
    }
    if (nr - nl == 1) {
      nodes[me].d = v;
    } else {
      Index mid = (nl + nr) >> 1;
      if (p < mid) {
        int got = SetImpl(nodes[me].c[0], p, v, nl, mid);
        nodes[me].c[0] = got;
      } else {
        int got = SetImpl(nodes[me].c[1], p, v, mid, nr);
        nodes[me].c[1] = got;
      }
      auto lft = nodes[me].c[0] == -1 ? Info::GetDefault(nl, mid) : nodes[nodes[me].c[0]].d;
      auto rgt = nodes[me].c[1] == -1 ? Info::GetDefault(mid, nr) : nodes[nodes[me].c[1]].d;
      nodes[me].d = lft.Unite(rgt);
    }
    return me;
  }

  int Set(Index p, const Info& v, int root = Persistent ? -1 : 1) {
    assert(0 <= p && p < n && root >= 1);
    return SetImpl(root, p, v, 0, n);
  }

  Info QueryImpl(int root, Index l, Index r, Index nl, Index nr) {
    if (root == -1) {
      return Info::GetDefault(max(l, nl), min(r, nr));
    }
    if (l <= nl && nr <= r) {
      return nodes[root].d;
    }
    Index mid = (nl + nr) >> 1;
    auto lft = l < mid ? QueryImpl(nodes[root].c[0], l, r, nl, mid) : Info();
    auto rgt = r > mid ? QueryImpl(nodes[root].c[1], l, r, mid, nr) : Info();
    return lft.Unite(rgt);
  }

  Info Query(Index l, Index r, int root = Persistent ? -1 : 1) {
    assert(0 <= l && l <= r && r <= n && root >= 1);
    if (l == r) {
      return Info();
    }
    return QueryImpl(root, l, r, 0, n);
  }

  Info Get(Index p, int root = Persistent ? -1 : 1) {
    assert(0 <= p && p < n && root >= 1);
    Index nl = 0;
    Index nr = n;
    while (nr - nl > 1 && root != -1) {
      Index mid = (nl + nr) >> 1;
      if (p < mid) {
        root = nodes[root].c[0];
        nr = mid;
      } else {
        root = nodes[root].c[1];
        nl = mid;
      }
    }
    return root == -1 ? Info::GetDefault(p, p + 1) : nodes[root].d;
  }

  template<int N, typename F>
  Index MaxRight(array<int, N> roots, Index l, F f) {
    assert(0 <= l && l <= n);
    if (l == n) {
      return n;
    }
    Index res = n;
    array<Info, N> sums;
    for (int i = 0; i < N; i++) {
      sums[i] = Info();
    }
    array<Info, N> new_sums;
    auto Dfs = [&](auto&& self, array<int, N> v, Index nl, Index nr) -> void {
      if (res != n) {
        return;
      }
      array<int, N> to;
      if (nl < l) {
        Index mid = (nl + nr) >> 1;
        if (l < mid) {
          for (int i = 0; i < N; i++) {
            to[i] = v[i] == -1 ? -1 : nodes[v[i]].c[0];
          }
          self(self, to, nl, mid);
          if (res != n) {
            return;
          }
        }
        for (int i = 0; i < N; i++) {
          to[i] = v[i] == -1 ? -1 : nodes[v[i]].c[1];
        }
        self(self, to, mid, nr);
        return;
      }
      for (int i = 0; i < N; i++) {
        new_sums[i] = sums[i].Unite(v[i] == -1 ? Info::GetDefault(nl, nr) : nodes[v[i]].d);
      }
      if (f(new_sums)) {
        sums = new_sums;
        return;
      }
      while (nr - nl > 1) {
        Index mid = (nl + nr) >> 1;
        for (int i = 0; i < N; i++) {
          new_sums[i] = sums[i].Unite(v[i] == -1 || nodes[v[i]].c[0] == -1 ? Info::GetDefault(nl, mid) : nodes[nodes[v[i]].c[0]].d);
        }
        if (f(new_sums)) {
          sums = new_sums;
          nl = mid;
          for (int i = 0; i < N; i++) {
            v[i] = v[i] == -1 ? -1 : nodes[v[i]].c[1];
          }
        } else {
          nr = mid;
          for (int i = 0; i < N; i++) {
            v[i] = v[i] == -1 ? -1 : nodes[v[i]].c[0];
          }
        }
      }
      res = nl;
    };
    Dfs(Dfs, roots, 0, n);
    return res;
  }

  template<int N, typename F>
  Index MinLeft(array<int, N> roots, Index r, F f) {
    assert(0 <= r && r <= n);
    if (r == 0) {
      return 0;
    }
    Index res = 0;
    array<Info, N> sums;
    for (int i = 0; i < N; i++) {
      sums[i] = Info();
    }
    array<Info, N> new_sums;
    auto Dfs = [&](auto&& self, array<int, N> v, Index nl, Index nr) -> void {
      if (res != 0) {
        return;
      }
      array<int, N> to;
      if (nr > r) {
        Index mid = (nl + nr) >> 1;
        if (r > mid) {
          for (int i = 0; i < N; i++) {
            to[i] = v[i] == -1 ? -1 : nodes[v[i]].c[1];
          }
          self(self, to, mid, nr);
          if (res != 0) {
            return;
          }
        }
        for (int i = 0; i < N; i++) {
          to[i] = v[i] == -1 ? -1 : nodes[v[i]].c[0];
        }
        self(self, to, nl, mid);
        return;
      }
      for (int i = 0; i < N; i++) {
        new_sums[i] = (v[i] == -1 ? Info::GetDefault(nl, nr) : nodes[v[i]].d).Unite(sums[i]);
      }
      if (f(new_sums)) {
        sums = new_sums;
        return;
      }
      while (nr - nl > 1) {
        Index mid = (nl + nr) >> 1;
        for (int i = 0; i < N; i++) {
          new_sums[i] = (v[i] == -1 || nodes[v[i]].c[1] == -1 ? Info::GetDefault(mid, nr) : nodes[nodes[v[i]].c[1]].d).Unite(sums[i]);
        }
        if (f(new_sums)) {
          sums = new_sums;
          nr = mid;
          for (int i = 0; i < N; i++) {
            v[i] = v[i] == -1 ? -1 : nodes[v[i]].c[0];
          }
        } else {
          nl = mid;
          for (int i = 0; i < N; i++) {
            v[i] = v[i] == -1 ? -1 : nodes[v[i]].c[1];
          }
        }
      }
      res = nr;
    };
    Dfs(Dfs, roots, 0, n);
    return res;
  }
};

struct Info {
  int s = 0;

  Info Unite(const Info& b) const {
    Info res;
    res.s = s + b.s;
    return res;
  }

  static Info GetDefault([[maybe_unused]] int l, [[maybe_unused]] int r) {
    return Info();
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> p(n);
  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    --p[i];
    pos[p[i]] = i;
  }
  set<int> zeros;
  set<int> ones;
  for (int i = 0; i < n; i++) {
    zeros.insert(i);
  }
  zeros.insert(-1);
  zeros.insert(n);
  ones.insert(-1);
  ones.insert(n);
  vector<vector<array<int, 3>>> ev(n + 1);
  auto Add = [&](int xa, int xb, int ya, int yb) {
    assert(0 <= xa && xa <= xb && xb + 1 == ya && ya <= yb && yb < n);
    ev[xa].push_back({ya, yb, +1});
    ev[xb + 1].push_back({ya, yb, -1});
  };
  for (int val = 0; val < n; val++) {
    int i = pos[val];
    zeros.erase(i);
    ones.insert(i);
    auto it = zeros.lower_bound(i);
    int nxt = *it;
    int prv = *prev(it);
    if (nxt < n) {
      int until = *ones.lower_bound(nxt);
      Add(prv + 1, nxt - 1, nxt, until - 1);
    }
    if (prv >= 0) {
      int from = *prev(ones.lower_bound(prv));
      Add(from + 1, prv, prv + 1, nxt - 1);
    }
  }
  DynamicSimpleSegmentTree<Info, int, true> st(n + 1);
  vector<int> roots(n);
  int root = 1;
  for (int i = 0; i < n; i++) {
    for (auto& e : ev[i]) {
      int ya = e[0];
      int yb = e[1];
      int delta = e[2];
      root = st.Set(ya, {st.Get(ya, root).s + delta}, root);
      root = st.Set(yb + 1, {st.Get(yb + 1, root).s - delta}, root);
    }
    roots[i] = root;
  }
  int tt;
  cin >> tt;
  for (int qq = 0; qq < tt; qq++) {
    int l, r;
    cin >> l >> r;
    --l; --r;
    cout << (st.Query(0, r + 1, roots[l]).s > 0 ? "YES" : "NO") << '\n';
    if (qq % 10 == 9) {
      cout.flush();
    }
  }
  return 0;
}
