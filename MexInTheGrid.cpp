#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        vector<vector<int>> arr(n, vector<int>(n, -1));
        int x, y;
        if (n % 2 == 0) {
            x = n / 2 - 1;
            y = n / 2 - 1;
        } else {
            x = n / 2;
            y = n / 2;
        }
        
        arr[x][y] = 0;
        int value = 1;
        int step = 1;

        const array<pair<int,int>, 4> dir = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

        while (value < n * n) {
            for (int d = 0; d < 4 && value < n * n; ++d) {
                int steps = step;
                if (d % 2 == 1) {
                    ++step;
                }
                auto [dx, dy] = dir[d];

                for (int i = 0; i < steps && value < n * n; ++i) {
                    x += dx;
                    y += dy;
                    if (x >= 0 && x < n && y >= 0 && y < n && arr[x][y] == -1) {
                        arr[x][y] = value++;
                    }
                }
            }
        }

        // Output the spiral
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << arr[i][j] << (j + 1 < n ? ' ' : '\n');
            }
        }
        cout << '\n';
    }

    return 0;
}
