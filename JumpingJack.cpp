#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    cin >> x;
    long long t = llabs(x);

    long long k = 0, S = 0;
    // Keep going until S >= t and parity matches
    while (S < t || ((S - t) & 1)){
        ++k;
        S += k;
    }

    cout << k << "\n";
    return 0;
}
