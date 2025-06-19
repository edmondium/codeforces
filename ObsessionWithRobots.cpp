#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    // current coords
    int x = 0, y = 0;
    // map (x,y) -> step index
    unordered_map<long long,int> vis;
    vis.reserve(s.size()*2);

    auto encode = [&](int a, int b){
        return ( (int64_t)a << 32 ) ^ (uint32_t)b;
    };

    // origin is step 0
    vis[encode(x,y)] = 0;

    for(int i = 0; i < (int)s.size(); i++){
        char c = s[i];
        if(c == 'L')      --x;
        else if(c == 'R') ++x;
        else if(c == 'U') ++y;
        else              --y;

        int t = i+1;
        long long h = encode(x,y);

        // 1) revisiting
        if(vis.count(h)){
            cout << "BUG\n";
            return 0;
        }
        // 2) any neighbor (not the immediate predecessor) was already visited?
        static const int dx[4] = {1,-1,0,0};
        static const int dy[4] = {0,0,1,-1};
        for(int d = 0; d < 4; d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            auto it = vis.find(encode(nx,ny));
            if(it != vis.end() && it->second < t-1){
                cout << "BUG\n";
                return 0;
            }
        }

        // record this cell at step t
        vis[h] = t;
    }

    cout << "OK\n";
    return 0;
}
