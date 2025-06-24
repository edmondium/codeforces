#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> price(n);
    for (int &p : price)
        cin >> p;

    // 1) Count how often each fruit name appears
    unordered_map<string,int> freqMap;
    string name;
    for (int i = 0; i < m; i++) {
        cin >> name;
        freqMap[name]++;
    }

    // 2) Build a freq vector of size n (pad with zeros)
    vector<int> freq;
    freq.reserve(n);
    for (auto &kv : freqMap)
        freq.push_back(kv.second);
    while ((int)freq.size() < n)
        freq.push_back(0);

    // 3) Sort prices ascending, freq descending
    sort(price.begin(), price.end());
    sort(freq.begin(), freq.end(), greater<int>());

    // 4) Compute min & max
    long long minCost = 0, maxCost = 0;

    // min: largest freq × smallest price
    for (int i = 0; i < n; i++)
        minCost += 1LL * freq[i] * price[i];

    // max: largest freq × largest price
    for (int i = 0; i < n; i++)
        maxCost += 1LL * freq[i] * price[n - 1 - i];

    cout << minCost << " " << maxCost << "\n";
    return 0;
}
