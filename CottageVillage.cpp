#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    vector<pair<int,int>> H(n);
    for(auto &h : H){
        cin >> h.first >> h.second;
        h.first *= 2;      // work in “double” space
        // h.second is side length; half-side in double space = h.second
    }
    t *= 2;                // required gap in double space

    sort(H.begin(), H.end());

    int ans = 2;  // one on the far left, one on the far right
    for(int i = 0; i + 1 < n; i++){
        int right_i = H[i].first + H[i].second;
        int left_j  = H[i+1].first - H[i+1].second;
        int gap = left_j - right_i;
        if(gap == t)      ans += 1;  // exactly fits touching both
        else if(gap > t)  ans += 2;  // can slide to touch either
    }

    cout << ans << "\n";
    return 0;
}
