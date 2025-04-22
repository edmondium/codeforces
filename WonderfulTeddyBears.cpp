#include <bits/stdc++.h>
using namespace std;

void test() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    long long x = 0;
    int a = 0;
    int b = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'B') {
            a++;
            if ((i + 1) % 2 == 0) {
                b++;
            }
        }
        if (s[i] == 'P') {
            x += a;
        }
    }

    int d = abs(a / 2 - b);
    cout << (x + d) / 2 << endl;
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