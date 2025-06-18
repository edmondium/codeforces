#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<int> A(n*m);
        int M = 0;
        for(int i = 0; i < n*m; i++){
            cin >> A[i];
            M = max(M, A[i]);
        }

        // collect positions of all max-cells
        vector<pair<int,int>> S;
        S.reserve(n*m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(A[i*m + j] == M)
                    S.emplace_back(i, j);
            }
        }

        // if there's only one max-cell, you can always hit it
        if(S.size() == 1){
            cout << M-1 << "\n";
            continue;
        }

        // col_owner[j] = the (unique) row index owning all M's in col j, or -1 if none
        // col_multi[j] = 1 if column j has M's in ≥2 different rows
        vector<int>  col_owner(m, -1);
        vector<char> col_multi(m,  0);
        for(auto &p : S){
            int r = p.first, c = p.second;
            if(col_owner[c] == -1){
                col_owner[c] = r;
            }
            else if(col_owner[c] != r){
                col_multi[c] = 1;
            }
        }

        // total distinct columns that contain at least one M
        int C = 0;
        for(int j = 0; j < m; j++){
            if(col_owner[j] != -1) C++;
        }

        // for each row r: excl[r] = how many columns have M only in row r
        vector<int> excl(n, 0), has_row(n, 0);
        for(auto &p : S) has_row[p.first] = 1;
        for(int j = 0; j < m; j++){
            if(col_owner[j] >= 0 && !col_multi[j]){
                excl[col_owner[j]]++;
            }
        }

        // check if there's a row r such that after removing excl[r] cols,
        // at most 1 column remains to be covered by your single c
        bool canCover = false;
        for(int r = 0; r < n; r++){
            if(!has_row[r]) continue;
            if(C - excl[r] <= 1){
                canCover = true;
                break;
            }
        }

        cout << (canCover ? M-1 : M) << "\n";
    }
    return 0;
}
