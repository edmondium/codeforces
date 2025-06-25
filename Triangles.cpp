#include <bits/stdc++.h>
using namespace std;

static int a[505][505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> rx(n), ry(n), bx(m), by(m);
    for(int i = 0; i < n; i++) 
        cin >> rx[i] >> ry[i];
    for(int i = 0; i < m; i++) 
        cin >> bx[i] >> by[i];

    // Precompute for every ordered pair (i,j) how many blues lie to the left of i→j 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(rx[i] < rx[j]){
                long long A = ry[j] - ry[i];
                long long B = rx[i] - rx[j];
                long long C = -A * rx[i] - B * ry[i];  // line: A·x + B·y + C = 0

                int cnt = 0;
                for(int k = 0; k < m; k++){
                    // check if B[k] is between x_i and x_j and satisfies A·x+B·y+C > 0
                    if(bx[k] >= rx[i] && bx[k] < rx[j] 
                       && A * bx[k] + B * by[k] + C > 0) {
                        cnt++;
                    }
                }
                a[i][j] = cnt;
                a[j][i] = -cnt;  // opposite direction sees M-cnt to the left
            }
        }
    }

    // Count triples (i<j<k) such that a[i][j] + a[j][k] + a[k][i] == 0
    long long ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            for(int k = j+1; k < n; k++){
                if(a[i][j] + a[j][k] + a[k][i] == 0)
                    ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
