#include <bits/stdc++.h>
 
using namespace std;
 
using pt = pair<int, int>;
 
const int N = 200007;
 
int n, q;
int k[N];
vector<pt> t[4 * N];
int p[N], e[N], rk[N];
int *pos[3 * N];
int val[3 * N];
int csz;
int ans[N];
 
void upd(int v, int l, int r, int L, int R, pt val) {
  if (L >= R) return;
  if (l == L && r == R) {
    t[v].push_back(val);
    return;
  }
  int m = (l + r) / 2;
  upd(v * 2 + 1, l, m, L, min(R, m), val);
  upd(v * 2 + 2, m, r, max(m, L), R, val);
}
 
void rollback(int tsz) {
  while (csz > tsz) {
    --csz;
    (*pos[csz]) = val[csz];
  }
}
 
pt get(int v) {
  if (p[v] == v) return {v, 0};
  auto [u, d] = get(p[v]);
  return {u, d ^ e[v]};
}
 
void assign(int& x, int y) {
  pos[csz] = &x;
  val[csz] = x;
  ++csz;
  x = y;
}
 
pt unite(int x, int y) {
  auto [v, d1] = get(x);
  auto [u, d2] = get(y);
  if (v == u) return {0, d1 ^ d2};
  if (rk[v] > rk[u]) swap(v, u);
  assign(p[v], u);
  assign(e[v], d1 ^ d2 ^ 1);
  assign(rk[u], rk[v] + rk[u]);
  return {1, 0};
}
 
void solve(int v, int l, int r, int cnt) {
  int tsz = csz;
  for (auto [x, y] : t[v]) {
    auto [f, d] = unite(x, y);
    //cerr << l << " " << r << " " << x + 1 << " " << y + 1 << " " << f << " " << d << endl;
    if (!f) cnt ^= d;
  }
  if (l != r - 1) {
    int m = (l + r) / 2;
    solve(v * 2 + 1, l, m, cnt);
    solve(v * 2 + 2, m, r, cnt);
  } else {
    ans[l] = k[l] % 3;
    if (ans[l] == 2) ans[l] = cnt + 1;
  }
  rollback(tsz);
}
 
int main() {
  cin >> n >> q;
  vector<int> g(n), lst(n);
  for (int i = 0; i < n; ++i) {
    cin >> g[i];
    --g[i];
  }
  for (int i = 0; i < q; ++i) {
    int x, y;
    cin >> x >> y >> k[i];
    --x; --y;
    upd(0, 0, q, lst[x], i, {x, g[x]});
    g[x] = y;
    lst[x] = i;
  }
  for (int i = 0; i < n; ++i) {
    upd(0, 0, q, lst[i], q, {i, g[i]});
    p[i] = i;
    rk[i] = 1;
  }
  solve(0, 0, q, n & 1);
  for (int i = 0; i < q; ++i) {
    cout << ans[i] << '\n';
  }
}