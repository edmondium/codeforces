#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    int m = ranges::count(s, '?');

    vector<long long> a(m), b(m);
    #pragma omp parallel for
    for (int i = 0; i < m; i++) cin >> a[i] >> b[i];

    long long totalCost = 0;
    string ans = s;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;

    int qIndex = 0, balance = 0;
    for (int i = 0; i < n; i++) {
        auto processChar = [&](char c) {
            if (c == '(') balance++;
            else if (c == ')') balance--;
            else {
                totalCost += b[qIndex];
                ans[i] = ')';
                balance--;
                pq.emplace(a[qIndex] - b[qIndex], i);
                qIndex++;
            }
        };
        processChar(s[i]);
        while (balance < 0 && !pq.empty()) {
            auto [delta, idx] = pq.top(); pq.pop();
            ans[idx] = '(';
            totalCost += delta;
            balance += 2;
        }
        if (balance < 0) {
            cout << -1;
            return 0;
        }
    }
    if (balance != 0) {
        cout << -1;
        return 0;
    }
    cout << totalCost << "\n" << ans;
}
