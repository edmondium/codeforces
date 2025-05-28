#include <bits/stdc++.h>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m;
    cin >> n >> m;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
      cin >> s[i];
    }
    const int inf = int(1.5e9);
    vector<int> f(1 << n);
    for (int t = 0; t < (1 << n); t++) {
      for (int i = 0; i < n; i++) {
        if (!(t & (1 << i))) {
          f[t] += s[i];
        }
      }
    }
    for (int it = 0; it < m; it++) {
      vector<int> a(n);
      vector<int> b(n);
      vector<int> c(n);
      for (int j = 0; j < n; j++) {
        cin >> a[j];
      }
      for (int j = 0; j < n; j++) {
        cin >> b[j];
      }
      for (int j = 0; j < n; j++) {
        cin >> c[j];
      }
      vector<int> aux(1 << (n + 2), inf);
      for (int t = 0; t < (1 << n); t++) {
        for (int x = 0; x < 2; x++) {
          int nt = x + (t << 1) + ((t & 1) << (n + 1));
          int val = f[t];
          if (x == 0) {
            if (t & 1) val += b[0];
            if (t & 2) val += a[1];
            if (t & (1 << (n - 1))) val += c.back();
          }
          aux[nt] = min(aux[nt], val);
        }
      }
      for (int j = 1; j < n; j++) {
        int nj = (j + 1) % n;
        for (int t = 0; t < (1 << (n + 2)); t++) {
          if (t & (1 << j)) {
            continue;
          }
          int f1 = aux[t];
          int f2 = aux[t + (1 << j)];
          int val1 = min(f1, f2);
          int common = ((t >> (j + 1)) & 1) * b[j] + ((t >> (j + 2)) & 1) * a[nj];
          f1 += common;
          f2 += common + c[j - 1];
          aux[t] = min(f1, f2);
          aux[t + (1 << j)] = val1;
        }
      }
      fill(f.begin(), f.end(), inf);
      for (int t = 0; t < (1 << (n + 2)); t++) {
        f[t & ((1 << n) - 1)] = min(f[t & ((1 << n) - 1)], aux[t]);
      }
      cout << f[0] << '\n';
    }
  }
  return 0;
}
