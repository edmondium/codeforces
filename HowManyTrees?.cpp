#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using i128 = __int128_t;

int main(){
    int n, h;
    if(!(cin >> n >> h)) return 0;

    // 1) Precompute Catalan numbers up to n
    vector<ull> cat(n+1, 0);
    cat[0] = 1;
    for(int i = 1; i <= n; i++){
        i128 sum = 0;
        for(int r = 1; r <= i; r++){
            sum += (i128)cat[r-1] * cat[i-r];
        }
        cat[i] = (ull)sum;
    }

    // 2) DP: dp[i][k] = # BST's with i nodes and height ≤ k
    int K = h - 1;  // we only need heights up to h-1
    vector<vector<ull>> dp(n+1, vector<ull>(K+1, 0));
    // base: empty tree has height 0 ≤ any k
    for(int k = 0; k <= K; k++)
        dp[0][k] = 1;

    // build up
    for(int i = 1; i <= n; i++){
        for(int k = 1; k <= K; k++){
            i128 ways = 0;
            for(int r = 1; r <= i; r++){
                ways += (i128)dp[r-1][k-1] * dp[i-r][k-1];
            }
            dp[i][k] = (ull)ways;
        }
    }

    // 3) Answer = all BST's on n nodes − those of height ≤ (h−1)
    ull answer = cat[n] - dp[n][K];
    cout << answer << "\n";
    return 0;
}
