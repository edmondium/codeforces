#include <bits/stdc++.h>
using namespace std;

int main() {
    int Y, W;
    cin >> Y >> W;
    int m = max(Y, W);
    int favorable = 6 - m + 1;
    int total     = 6;
    int g = gcd(favorable, total);
    cout << (favorable / g) << '/' << (total / g) << "\n";
    return 0;
}
