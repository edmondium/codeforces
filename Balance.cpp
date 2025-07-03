#include <bits/stdc++.h>
using namespace std;

static const int MOD = 51123987;

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    int m = (n + 2) / 3;
    // dp arrays: pool[color][u][v][w],  d[color][u][v][w]
    // Dimensions [3][m+1][m+1][m+1]
    vector<vector<vector<vector<int>>>> pool(
        3,
        vector<vector<vector<int>>>(m+1,
          vector<vector<int>>(m+1,
            vector<int>(m+1, 0)))
    );
    vector<vector<vector<vector<int>>>> d = pool;

    // initially, empty prefix: we can 'end' with last=a/b/c all =1
    pool[0][0][0][0] = 1;
    pool[1][0][0][0] = 1;
    pool[2][0][0][0] = 1;

    for(char c : s){
        if(c=='a'){
            // we are appending an 'a'
            // every existing sequence whose last was 'a' (pool[0]) can extend u→u+1
            // also sequences ending in b or c now feed into d[1], d[2] or pool[1], pool[2]
            for(int v=0; v<=m; v++){
                for(int w=0; w<=m; w++){
                    int t=0;
                    for(int u=0; u<=m; u++){
                        // t = sum of pool[0][0..u-1][v][w]
                        //  -> contributes to d[0][u][v][w], pool[1][u][v][w], pool[2][u][v][w]
                        d[0][u][v][w] = add(d[0][u][v][w], t);
                        pool[1][u][v][w] = add(pool[1][u][v][w], t);
                        pool[2][u][v][w] = add(pool[2][u][v][w], t);

                        // now accumulate this cell, then zero it
                        t = add(t, pool[0][u][v][w]);
                        pool[0][u][v][w] = 0;
                    }
                }
            }
        }
        else if(c=='b'){
            for(int u=0; u<=m; u++){
                for(int w=0; w<=m; w++){
                    int t=0;
                    for(int v=0; v<=m; v++){
                        d[1][u][v][w] = add(d[1][u][v][w], t);
                        pool[0][u][v][w] = add(pool[0][u][v][w], t);
                        pool[2][u][v][w] = add(pool[2][u][v][w], t);

                        t = add(t, pool[1][u][v][w]);
                        pool[1][u][v][w] = 0;
                    }
                }
            }
        }
        else { // c=='c'
            for(int u=0; u<=m; u++){
                for(int v=0; v<=m; v++){
                    int t=0;
                    for(int w=0; w<=m; w++){
                        d[2][u][v][w] = add(d[2][u][v][w], t);
                        pool[0][u][v][w] = add(pool[0][u][v][w], t);
                        pool[1][u][v][w] = add(pool[1][u][v][w], t);

                        t = add(t, pool[2][u][v][w]);
                        pool[2][u][v][w] = 0;
                    }
                }
            }
        }
    }

    // Sum up all balanced ends of total length n
    long long answer = 0;
    for(int u=0; u<=m; u++){
        for(int v=0; v<=m; v++){
            int w = n - u - v;
            if(w < 0 || w > m) continue;
            if(abs(u-v)>1 || abs(u-w)>1 || abs(v-w)>1) continue;
            // we can end with last=a (d[0]), b (d[1]) or c (d[2])
            answer = (answer + d[0][u][v][w]) % MOD;
            answer = (answer + d[1][u][v][w]) % MOD;
            answer = (answer + d[2][u][v][w]) % MOD;
        }
    }

    cout << answer << "\n";
    return 0;
}
