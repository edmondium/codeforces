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
    vector a(n, vector<int>(m, -1));
    auto Print = [&](int i, int j) {
      assert(a[i][j] == -1);
      cout << i + 1 << " " << j + 1 << '\n';
      int m1 = -1, m2 = -1;
      vector<pair<int, int>> cells;
      for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
          if (a[r][c] == -1) {
            continue;
          }
          int d1 = max(abs(i - r), abs(j - c));
          int d2 = abs(i - r) + abs(j - c);
          if (d1 > m1 || (d1 == m1 && d2 > m2)) {
            m1 = d1;
            m2 = d2;
            cells.clear();
          }
          if (d1 == m1 && d2 == m2) {
            cells.emplace_back(r, c);
          }
        }
      }
      for (auto& [mr, mc] : cells) {
        assert(a[mr][mc] < 3);
        a[mr][mc] += 1;
      }
      a[i][j] = 0;
    };
    int i1 = n / 2, i2 = n / 2;
    int j1 = m / 2, j2 = m / 2;
    Print(i1, j1);
    while (i1 > 0 || j1 > 0) {
      if (i1 > 0) {
        i1 -= 1;
        i2 += 1;
        for (int j = m / 2; j >= j1; j--) {
          Print(i1, j);
          Print(i2, j);
          if (j < m / 2) {
            Print(i1, m - 1 - j);
            Print(i2, m - 1 - j);
          }
        }
      }
      if (j1 > 0) {
        j1 -= 1;
        j2 += 1;
        for (int i = n / 2; i >= i1; i--) {
          Print(i, j1);
          Print(i, j2);
          if (i < n / 2) {
            Print(n - 1 - i, j1);
            Print(n - 1 - i, j2);
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        assert(a[i][j] >= 0 && a[i][j] <= 3);
      }
    }
  }
  return 0;
}
