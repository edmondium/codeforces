#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());

        for (int i = 0; i < n; i++) {
            int x = (i % 2 == 0 ? i / 2 : m - 1 - i / 2);
            int y = m - 1 - x;
            cout << a[x] << " " << a[y] << " " << a[x] << " " 
                 << a[y] << " " << a[x] << " " << a[y] << "\n";
        }
    }
    return 0;
}
