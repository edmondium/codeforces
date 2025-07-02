#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> prefMin(n), sufMax(n);
        prefMin[0] = a[0];
        for (int i = 1; i < n; i++) {
            prefMin[i] = min(prefMin[i - 1], a[i]);
        }

        sufMax[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            sufMax[i] = max(sufMax[i + 1], a[i]);
        }

        string ans(n, '0');
        for (int i = 0; i < n; i++) {
            if (a[i] == prefMin[i] || a[i] == sufMax[i]) {
                ans[i] = '1';
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
