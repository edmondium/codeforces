#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> t(n);
    for (auto &x : t) 
        cin >> x;

    int i = 0, j = n - 1;
    long long timeA = 0, timeB = 0;
    int cntA = 0, cntB = 0;

    while (i <= j) {
        if (timeA <= timeB) {
            timeA += t[i++];
            cntA++;
        } else {
            timeB += t[j--];
            cntB++;
        }
    }

    cout << cntA << " " << cntB << "\n";
    return 0;
}
