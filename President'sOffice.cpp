#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    char president;
    cin >> n >> m >> president;

    vector<string> office(n);
    for (auto &row : office) {
        cin >> row;
    }

    // Offsets for up, right, down, left
    array<pair<int,int>, 4> dirs{{{-1,0}, {0,1}, {1,0}, {0,-1}}};
    set<char> neighbors;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (office[i][j] != president) 
                continue;

            for (auto [di, dj] : dirs) {
                int ni = i + di, nj = j + dj;
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) 
                    continue;

                char c = office[ni][nj];
                if (c != '.' && c != president) 
                    neighbors.insert(c);
            }
        }
    }

    cout << neighbors.size() << "\n";
    return 0;
}
