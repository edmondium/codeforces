#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> a(3);
    for (auto &row : a) {
        if (!(cin >> row) || row.size() != 3) 
            return 0;  // invalid input guard
    }

    bool symmetric = true;
    for (int i = 0; i < 3 && symmetric; i++) {
        for (int j = 0; j < 3; j++) {
            if ((a[i][j] == 'X') != (a[2 - i][2 - j] == 'X')) {
                symmetric = false;
                break;
            }
        }
    }

    cout << (symmetric ? "YES\n" : "NO\n");
    return 0;
}
