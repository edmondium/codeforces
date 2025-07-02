#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<char> row_color(n);
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        // Check row uniformity
        for (int j = 1; j < m; j++) {
            if (s[j] != s[0]) {
                cout << "NO\n";
                return 0;
            }
        }
        row_color[i] = s[0];
    }

    // Check adjacent rows differ
    for (int i = 1; i < n; i++) {
        if (row_color[i] == row_color[i - 1]) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}
