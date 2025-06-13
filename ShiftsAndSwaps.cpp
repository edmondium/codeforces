#include <bits/stdc++.h>

using namespace std;

template <typename T>
int duval(int n, const T &s) {
  assert(n >= 1);
  int i = 0, ans = 0;
  while (i < n) {
    ans = i;
    int j = i + 1, k = i;
    while (j < n + n && !(s[j % n] < s[k % n])) {
      if (s[k % n] < s[j % n]) {
        k = i;
      } else {
        k++;
      }
      j++;
    }
    while (i <= k) {
      i += j - k;
    }
  }
  return ans;
}

template <typename T>
int duval(const T &s) {
  return duval((int) s.size(), s);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m;
    cin >> n >> m;
    auto Canon = [&](vector<int>& a) {
      vector<vector<int>> at_a(m);
      for (int i = 0; i < n; i++) {
        at_a[a[i]].push_back(i);
      }
      vector<vector<int>> g(n);
      for (int i = 0; i < n; i++) {
        if (a[i] < m - 1) {
          auto& v = at_a[a[i] + 1];
          auto it = lower_bound(v.begin(), v.end(), i);
          if (it == v.end()) {
            it = v.begin();
          }
          g[*it].push_back(i);
        }
      }
      for (int i = 0; i < n; i++) {
        auto it = lower_bound(g[i].begin(), g[i].end(), i);
        rotate(g[i].begin(), it, g[i].end());
      }
      vector<int> b;
      auto Dfs = [&](auto&& self, int v) -> void {
        for (int u : g[v]) {
          self(self, u);
        }
        b.push_back(a[v]);
      };
      for (int i = 0; i < n; i++) {
        if (a[i] == m - 1) {
          Dfs(Dfs, i);
        }
      }
      assert(int(b.size()) == n);
      auto d = duval(b);
      rotate(b.begin(), b.begin() + d, b.end());
      return b;
    };
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      --a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
      cin >> b[i];
      --b[i];
    }
    cout << (Canon(a) == Canon(b) ? "YES" : "NO") << '\n';
  }
  return 0;
}
