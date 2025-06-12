#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    vector<long long> h(n);
    for(int i = 0; i < n; i++)
        cin >> h[i];

    deque<int> maxDQ, minDQ;  // store indices of potential max / min in current window
    int l = 0;                // left bound of window
    int best = 0;             // best window length found so far
    vector<pair<int,int>> ans;

    for(int r = 0; r < n; r++){
        // 1) Extend right end: maintain monotonicity
        while(!maxDQ.empty() && h[maxDQ.back()] <= h[r])
            maxDQ.pop_back();
        maxDQ.push_back(r);

        while(!minDQ.empty() && h[minDQ.back()] >= h[r])
            minDQ.pop_back();
        minDQ.push_back(r);

        // 2) Shrink from left while invalid (max - min > k)
        while(h[maxDQ.front()] - h[minDQ.front()] > k){
            if(maxDQ.front() == l) maxDQ.pop_front();
            if(minDQ.front() == l) minDQ.pop_front();
            l++;
        }

        // 3) Record current window [l..r]
        int len = r - l + 1;
        if(len > best){
            best = len;
            ans.clear();
            ans.emplace_back(l + 1, r + 1);  // convert to 1-based
        }
        else if(len == best){
            ans.emplace_back(l + 1, r + 1);
        }
    }

    // Output
    cout << best << " " << ans.size() << "\n";
    for(auto [L, R] : ans)
        cout << L << " " << R << "\n";

    return 0;
}
