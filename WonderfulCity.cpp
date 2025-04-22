#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;
 
using ll = long long;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        // Read grid of heights – using 0-indexing.
        vector<vector<ll>> h(n, vector<ll>(n));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> h[i][j];
            }
        }
 
        // Read costs for company A (rows) and B (columns)
        vector<ll> a(n), b(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int j = 0; j < n; j++){
            cin >> b[j];
        }
 
        // Precompute allowed transitions for adjacent rows.
        // For each adjacent row pair i and i+1, compute:
        // validSame[i]: if we assign same value (both 0 or both 1) then for every column j: h[i][j] != h[i+1][j]
        // validInc[i]: if we have (r[i], r[i+1]) = (0,1) then for every column: h[i+1][j] != h[i][j] - 1.
        // validDec[i]: if we have (r[i], r[i+1]) = (1,0) then for every column: h[i+1][j] != h[i][j] + 1.
        vector<bool> validSame(n-1, true), validInc(n-1, true), validDec(n-1, true);
        for (int i = 0; i < n-1; i++){
            for (int j = 0; j < n; j++){
                if(h[i+1][j] == h[i][j])
                    validSame[i] = false;
                if(h[i+1][j] == h[i][j] - 1)
                    validInc[i] = false;
                if(h[i+1][j] == h[i][j] + 1)
                    validDec[i] = false;
            }
        }
 
        // Similarly, precompute allowed transitions for adjacent columns.
        vector<bool> validSameCol(n-1, true), validIncCol(n-1, true), validDecCol(n-1, true);
        for (int j = 0; j < n-1; j++){
            for (int i = 0; i < n; i++){
                if(h[i][j+1] == h[i][j])
                    validSameCol[j] = false;
                if(h[i][j+1] == h[i][j] - 1)
                    validIncCol[j] = false;
                if(h[i][j+1] == h[i][j] + 1)
                    validDecCol[j] = false;
            }
        }
 
        // Use DP to pick the row adjustments.
        const ll INF = numeric_limits<ll>::max()/2;
        // dp[i][b] = minimal cost to assign rows 0..i with row i's assignment equal to b.
        vector<vector<ll>> dpRows(n, vector<ll>(2, INF));
        // Base: row 0 can be 0 (cost 0) or 1 (cost a[0])
        dpRows[0][0] = 0;
        dpRows[0][1] = a[0];
 
        for (int i = 0; i < n-1; i++){
            for (int curVal = 0; curVal < 2; curVal++){
                if(dpRows[i][curVal] == INF) continue;
                for (int nxtVal = 0; nxtVal < 2; nxtVal++){
                    int d = nxtVal - curVal;
                    bool valid = false;
                    if(d == 0){
                        valid = validSame[i];
                    } else if(d == 1){
                        valid = validInc[i];
                    } else if(d == -1){
                        valid = validDec[i];
                    }
                    if(valid){
                        dpRows[i+1][nxtVal] = min(dpRows[i+1][nxtVal], dpRows[i][curVal] + (nxtVal == 1 ? a[i+1] : 0));
                    }
                }
            }
        }
        ll bestRows = min(dpRows[n-1][0], dpRows[n-1][1]);
 
        // DP for columns.
        vector<vector<ll>> dpCols(n, vector<ll>(2, INF));
        dpCols[0][0] = 0;
        dpCols[0][1] = b[0];
 
        for (int j = 0; j < n-1; j++){
            for (int curVal = 0; curVal < 2; curVal++){
                if(dpCols[j][curVal] == INF) continue;
                for (int nxtVal = 0; nxtVal < 2; nxtVal++){
                    int d = nxtVal - curVal;
                    bool valid = false;
                    if(d == 0){
                        valid = validSameCol[j];
                    } else if(d == 1){
                        valid = validIncCol[j];
                    } else if(d == -1){
                        valid = validDecCol[j];
                    }
                    if(valid){
                        dpCols[j+1][nxtVal] = min(dpCols[j+1][nxtVal], dpCols[j][curVal] + (nxtVal==1 ? b[j+1] : 0));
                    }
                }
            }
        }
        ll bestCols = min(dpCols[n-1][0], dpCols[n-1][1]);
 
        // If one of the parts is impossible, print -1.
        if(bestRows == INF || bestCols == INF)
            cout << -1 << endl;
        else
            cout << bestRows + bestCols << endl;
    }
    return 0;
}
