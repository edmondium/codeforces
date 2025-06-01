#include <bits/stdc++.h>
using namespace std;
 
// The modulus we work with
const long long MOD = 998244353;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    // Since maximum n across any test is up to 1e5, precompute 2^x mod MOD up to max n.
    const int maxPow = 100000 + 5;
    vector<long long> pow2(maxPow);
    pow2[0] = 1;
    for (int i = 1; i < maxPow; i++){
        pow2[i] = (pow2[i-1] * 2) % MOD;
    }
    
    while(t--){
        int n;
        cin >> n;
        vector<int> p(n), q(n);
        for (int i = 0; i < n; i++){
            cin >> p[i];
        }
        for (int i = 0; i < n; i++){
            cin >> q[i];
        }
 
        // Build prefix maximum array for p: bestP[i] is max_{0<=j<=i} p[j]
        // and bestPIdx[i] is the index where that maximum occurs.
        vector<int> bestP(n), bestPIdx(n);
        bestP[0] = p[0];
        bestPIdx[0] = 0;
        for (int i = 1; i < n; i++){
            if(p[i] > bestP[i-1]){
                bestP[i] = p[i];
                bestPIdx[i] = i;
            } else {
                bestP[i] = bestP[i-1];
                bestPIdx[i] = bestPIdx[i-1];
            }
        }
 
        // Similarly build the prefix maximum array for q.
        vector<int> bestQ(n), bestQIdx(n);
        bestQ[0] = q[0];
        bestQIdx[0] = 0;
        for (int i = 1; i < n; i++){
            if(q[i] > bestQ[i-1]){
                bestQ[i] = q[i];
                bestQIdx[i] = i;
            } else {
                bestQ[i] = bestQ[i-1];
                bestQIdx[i] = bestQIdx[i-1];
            }
        }
 
        // We now compute the answer for each i in [0, n-1]
        // For candidate from p-side:
        // Let j = bestPIdx[i], candidate pair = ( bestP[i], q[i-j] ).
        // For the q–side:
        // Let k = bestQIdx[i], candidate pair = ( p[i-k], bestQ[i] ).
        // In each case we “sort” the pair in descending order.
        vector<long long> ans(n, 0);
        for (int i = 0; i < n; i++){
            int j = bestPIdx[i];
            int cand1_a = bestP[i], cand1_b = q[i - j];
            if(cand1_a < cand1_b)
                swap(cand1_a, cand1_b);
 
            int k = bestQIdx[i];
            int cand2_a = bestQ[i], cand2_b = p[i - k];
            if(cand2_a < cand2_b)
                swap(cand2_a, cand2_b);
 
            // Compare lexicographically: first compare the larger values then the smaller ones.
            int final_a, final_b;
            if(cand1_a > cand2_a || (cand1_a == cand2_a && cand1_b >= cand2_b)){
                final_a = cand1_a;
                final_b = cand1_b;
            } else {
                final_a = cand2_a;
                final_b = cand2_b;
            }
 
            // The answer for position i is 2^(final_a) + 2^(final_b) modulo MOD.
            ans[i] = ( pow2[final_a] + pow2[final_b] ) % MOD;
        }
 
        // Output the answers
        for (int i = 0; i < n; i++){
            cout << ans[i] << (i + 1 < n ? " " : "\n");
        }
    }
    return 0;
}
