#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    array<int, 4> a;
    for (int i = 0; i < 4; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    bool canTriangle = false, canSegment = false;
    // Try every triple of sticks
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            for (int k = j + 1; k < 4; ++k) {
                int x = a[i], y = a[j], z = a[k];
                if      (x + y >  z) canTriangle = true;
                else if (x + y == z) canSegment  = true;
            }
        }
    }

    if      (canTriangle) cout << "TRIANGLE\n";
    else if (canSegment)  cout << "SEGMENT\n";
    else                  cout << "IMPOSSIBLE\n";

    return 0;
}
