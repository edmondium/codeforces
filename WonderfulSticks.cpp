#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    
    vector<int> sticks(n);
    iota(sticks.begin(), sticks.end(), 1); // Fill with 1 to n
    
    vector<int> result(n);
    int min_idx = 0, max_idx = n - 1;
    
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] == '<') {
            result[i + 1] = sticks[min_idx++];
        } else {
            result[i + 1] = sticks[max_idx--];
        }
    }
    result[0] = sticks[min_idx]; // Last remaining stick
    
    for (int x : result) cout << x << ' ';
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
