#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Envelope {
    int w, h, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cardW, cardH;
    cin >> n >> cardW >> cardH;
    
    vector<Envelope> envelopes;
    for (int i = 0; i < n; i++) {
        int w, h;
        cin >> w >> h;
        if (w > cardW && h > cardH) {
            envelopes.push_back({w, h, i+1}); // store original index (1-indexed)
        }
    }
    
    // If no envelope can contain the card, output 0
    if(envelopes.empty()){
        cout << 0 << "\n";
        return 0;
    }
    
    // Sort the envelopes by width then by height (both ascending)
    sort(envelopes.begin(), envelopes.end(), [](const Envelope &a, const Envelope &b) {
        if(a.w == b.w) return a.h < b.h;
        return a.w < b.w;
    });
    
    int m = envelopes.size();
    vector<int> dp(m, 1), parent(m, -1);
    int best = 0, bestIndex = -1;
    
    // Dynamic programming: for each envelope, try extending chain from previous envelopes.
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            if(envelopes[i].w > envelopes[j].w && envelopes[i].h > envelopes[j].h) {
                if(dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
        if(dp[i] > best) {
            best = dp[i];
            bestIndex = i;
        }
    }
    
    // Reconstruct the chain by following parent pointers.
    vector<int> chain;
    while(bestIndex != -1) {
        chain.push_back(envelopes[bestIndex].idx); // add original index.
        bestIndex = parent[bestIndex];
    }
    
    // Reverse the chain to print from the smallest envelope (that fits the card) upward.
    reverse(chain.begin(), chain.end());
    
    cout << chain.size() << "\n";
    for (int idx : chain)
        cout << idx << " ";
    cout << "\n";
    
    return 0;
}
