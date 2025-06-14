#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    vector<int> dp(n+1, 0);
    // rolling‐hash parameters
    const ull B = 1315423911ULL;  
    ull hf = 0, hr = 0, powB = 1;

    long long answer = 0;
    for(int i = 1; i <= n; i++){
        unsigned char c = s[i-1];
        // update forward and reverse hashes
        hf = hf * B + c;
        hr = hr + powB * c;
        powB = powB * B;

        // if full prefix is palindrome
        if(hf == hr){
            dp[i] = dp[i/2] + 1;
        }
        // else dp[i] stays 0
        answer += dp[i];
    }

    cout << answer << "\n";
    return 0;
}
