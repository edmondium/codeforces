#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int x = 0, y = 0;
    unordered_map<long long,int> vis;
    vis.reserve(s.size()*2);

    auto encode = [](int a, int b) {
        return ( (int64_t)a << 32 ) ^ (uint32_t)b;
    };

    vis[encode(x,y)] = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        x += (c == 'R') - (c == 'L');
        y += (c == 'U') - (c == 'D');

        int t = i+1;
        long long h = encode(x,y);

        if (vis.contains(h)) {
            cout << "BUG\n";
            return 0;
        }

        static const int dx[4] = {1,-1,0,0};
        static const int dy[4] = {0,0,1,-1};
        bool bug = false;

        #pragma omp parallel for reduction(|:bug)
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            auto it = vis.find(encode(nx,ny));
            if (it != vis.end() && it->second < t-1) bug = true;
        }

        if (bug) {
            cout << "BUG\n";
            return 0;
        }

        vis[h] = t;
    }

    cout << "OK\n";
    return 0;
}
