#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int year = stoi(s);

        bool found = false;
        for (int a = 0; a < 100 && !found; ++a) {
            for (int b = 0; b < 100; ++b) {
                if ((a + b) * (a + b) == year) {
                    cout << a << ' ' << b << "\n";
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            cout << -1 << "\n";
        }
    }

    return 0;
}
