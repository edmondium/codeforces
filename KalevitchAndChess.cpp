#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> g(8);
    for(int i = 0; i < 8; i++){
        cin >> g[i];
    }

    // Precompute which rows/columns can be painted at all:
    bool okRow[8] = {}, okCol[8] = {};
    for(int i = 0; i < 8; i++){
        okRow[i] = (g[i].find('W') == string::npos);
    }
    for(int j = 0; j < 8; j++){
        bool hasW = false;
        for(int i = 0; i < 8; i++){
            if(g[i][j] == 'W'){
                hasW = true;
                break;
            }
        }
        okCol[j] = !hasW;
    }

    int answer = 16;  // worse than 8+8
    for(int mask = 0; mask < (1<<8); mask++){
        int strokes = __builtin_popcount(mask);

        // 1) Check we never paint an illegal row
        bool bad = false;
        for(int i = 0; i < 8; i++){
            if( (mask & (1<<i)) && !okRow[i] ){
                bad = true;
                break;
            }
        }
        if(bad) continue;

        // 2) For every unpainted row, mark columns needed
        bool needCol[8] = {};
        for(int i = 0; i < 8; i++){
            if(mask & (1<<i)) continue;  // row i is covered
            for(int j = 0; j < 8; j++){
                if(g[i][j] == 'B')
                    needCol[j] = true;
            }
        }

        // 3) Check we never force an illegal column
        for(int j = 0; j < 8; j++){
            if(needCol[j] && !okCol[j]){
                bad = true;
                break;
            }
            if(needCol[j]) strokes++;
        }
        if(bad) continue;

        answer = min(answer, strokes);
    }

    cout << answer << "\n";
    return 0;
}
