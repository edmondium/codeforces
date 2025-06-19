#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // Special case:
    if (n < 1) {
        cout << 0 << "\n";
        return 0;
    }

    ll count = 0;
    queue<ll> q;
    q.push(1);

    while (!q.empty()) {
        ll x = q.front(); 
        q.pop();

        if (x > n) 
            continue;
        // x is a valid “0/1-digit” number ≤ n
        ++count;

        // Try to append a 0 or 1 in decimal:
        // x * 10  and  x * 10 + 1
        if (x * 10 <= n) {
            q.push(x * 10);
        }
        if (x * 10 + 1 <= n) {
            q.push(x * 10 + 1);
        }
    }

    cout << count << "\n";
    return 0;
}
