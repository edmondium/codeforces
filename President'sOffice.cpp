#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    char c;
    cin >> n >> m >> c;
    vector<string> room(n);
    for (auto &row : room) cin >> row;

    set<char> deputies;
    #pragma omp parallel
    {
        set<char> local;
        #pragma omp for collapse(2)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (room[i][j] == c) {
                    auto check = [&](int x, int y) {
                        if (x >= 0 && x < n && y >= 0 && y < m) {
                            char d = room[x][y];
                            if (d != c && d != '.') local.insert(d);
                        }
                    };
                    check(i-1, j);
                    check(i+1, j);
                    check(i, j-1);
                    check(i, j+1);
                }
        #pragma omp critical
        deputies.insert(local.begin(), local.end());
    }

    cout << deputies.size() << '\n';
}
