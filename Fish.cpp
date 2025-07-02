#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n));
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        cin >> a[i][j];

    int N = 1<<n;
    vector<double> dp(N, 0.0);
    dp[N-1] = 1.0;

    // Precompute popcounts for all masks
    vector<int> pc(N);
    for(int m = 1; m < N; m++)
        pc[m] = pc[m>>1] + (m&1);

    // Process masks in decreasing order of popcount
    for(int mask = N-1; mask >= 0; mask--){
        int k = pc[mask];
        if(k < 2) continue;

        double pairs = k*(k-1)/2.0;
        double Pmeet = 1.0 / pairs;

        // Enumerate all i<j inside mask
        for(int i = 0; i < n; i++){
            if(!(mask & (1<<i))) continue;
            for(int j = i+1; j < n; j++){
                if(!(mask & (1<<j))) continue;

                int m_without_j = mask ^ (1<<j);
                dp[m_without_j] += dp[mask] * Pmeet * a[i][j];

                int m_without_i = mask ^ (1<<i);
                dp[m_without_i] += dp[mask] * Pmeet * a[j][i];
            }
        }
    }

    // Output answer: probability fish i is last => mask == (1<<i)
    cout << fixed << setprecision(6);
    for(int i = 0; i < n; i++){
        cout << dp[1<<i] << (i+1==n? '\n' : ' ');
    }
    return 0;
}
