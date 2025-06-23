#include <bits/stdc++.h>
using namespace std;

// 8‐directional offsets
static constexpr array<pair<int,int>,8> dirs{{
    {0, 1}, {1, 0}, {0,-1}, {-1, 0},
    {1, 1}, {1,-1}, {-1, 1}, {-1,-1}
}};

int n, m;

// Flood‐fill every '1' → '2' and count the size of the component.
void floodFill(vector<string>& grid, int x, int y, int& cnt) {
    if (x < 0 || x >= n || y < 0 || y >= m) return;
    if (grid[x][y] != '1') return;
    grid[x][y] = '2';
    ++cnt;
    for (auto [dx, dy] : dirs) {
        floodFill(grid, x + dx, y + dy, cnt);
    }
}

// Check a “frame edge” of length d+1 along directions [l..r)
// i.e. for each i∈[0..d], check grid[x + dirs[j].first*i][y + dirs[j].second*i]=='2'.
bool checkFrame(const vector<string>& grid,
                int x, int y,
                int d,     // number of steps along each edge
                int l, int r)
{
    for (int i = 0; i <= d; ++i) {
        for (int j = l; j < r; ++j) {
            auto [dx, dy] = dirs[j];
            int xx = x + dx * i;
            int yy = y + dy * i;
            if (xx < 0 || xx >= n || yy < 0 || yy >= m) return false;
            if (grid[xx][yy] != '2') return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }

        int result = 0;
        // Scan for unvisited '1's → flood & then try both square types
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    int s = 0;
                    floodFill(grid, i, j, s);

                    // A valid frame has perimeter 4·d ⇒ s must be divisible by 4
                    if (s % 4) continue;
                    int d = s / 4;
                    if (d == 0 || d > 250) continue;

                    // 1) Axis‐aligned square of side length (d+1)
                    //    walk right/down from top‐left, then left/up from bottom‐right
                    if (checkFrame(grid, i,     j,     d, 0, 2) &&
                        checkFrame(grid, i + d, j + d, d, 2, 4))
                    {
                        result++;
                    }

                    // 2) 45°‐rotated diamond (“radius” d)
                    //    walk down‐right/down‐left from top, then up‐left/up‐right from bottom
                    if (checkFrame(grid, i,       j,     d, 4, 6) &&
                        checkFrame(grid, i + 2*d, j,     d, 6, 8))
                    {
                        result++;
                    }
                }
            }
        }

        cout << result << "\n";
    }
    return 0;
}
