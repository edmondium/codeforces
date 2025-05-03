#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            mp[x]++;
        }

        bool ok = false;
        int lst = -1;
        bool flag = false;
        for (auto& [k, v] : mp) {
            if (v >= 4) {
                ok = true;
            }
            if (k != lst + 1) {
                lst = k;
                flag = false;
            }
            if (v >= 2) {
                if (flag) {
                    ok = true;
                } else {
                    flag = true;
                }
            }
            lst = k;
        }
        if (ok) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}