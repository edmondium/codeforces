#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        // Bob wins only when n is divisible by 4
        cout << (n % 4 == 0 ? "Bob\n" : "Alice\n");
    }

    return 0;
}
