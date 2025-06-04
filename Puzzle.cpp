#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    int p, s;
    cin >> p >> s;
    bool found = false;
    for (int h = 1; h <= 200; h++) {
      for (int w = 1; w <= 200; w++) {
        if (found || abs(h - w) > 1) {
          continue;
        }
        int per = 2 * (h + w);
        int low = h + w - 1;
        int high = h * w;
        for (int area = low; area <= high; area++) {
          if (per * s == p * area) {
            cout << area << '\n';
            for (int i = 0; i < h; i++) {
              cout << 0 << " " << i << '\n';
            }
            for (int j = 1; j < w; j++) {
              cout << j << " " << 0 << '\n';
            }
            int need = area - low;
            for (int i = 1; i < w; i++) {
              for (int j = 1; j < h; j++) {
                if (need > 0) {
                  cout << i << " " << j << '\n';
                  need -= 1;
                }
              }
            }
            found = true;
            break;
          }
        }
      }
    }
    if (!found) {
      cout << -1 << '\n';
    }
  }
  return 0;
}
