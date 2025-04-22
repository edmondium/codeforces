#include <bits/stdc++.h>
using namespace std;

void test() {
    int n;
    cin >> n;

    map<int, int> cntVer, cntDiag;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cntVer[x]++;
        cntDiag[x + y]++;
    }

    int s;
    for (auto [c, cnt]: cntVer) {
        if (cnt % 2 == 1) {
            s = c;
            break;
        }
    }

    int t;
    for (auto [c, cnt]: cntDiag) {
        if (cnt % 2 == 1) {
            t = c - s;
            break;
        }
    }

    cout << s << " " << t << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        test();
    }
    
    return 0;
}