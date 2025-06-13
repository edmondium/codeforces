#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    cout << 2 * n - 1 << '\n';
    cout << 1 << " " << 1 << " " << n << '\n';
    for (int i = 2; i <= n; i++) {
      cout << i << " " << 1 << " " << i - 1 << '\n';
      cout << i << " " << i << " " << n << '\n';
    }
  }
  return 0;
}
