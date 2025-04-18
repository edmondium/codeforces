#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

struct Cell {
    int count;
    char move;
};

pair<int, string> findPath(vector<vector<int>> &grid, int n) {
    vector<vector<Cell>> dp2(n, vector<Cell>(n, {INF, ' '}));
    vector<vector<Cell>> dp5(n, vector<Cell>(n, {INF, ' '}));

    auto factorCount = [](int num, int factor) {
        int count = 0;
        while (num && num % factor == 0) {
            num /= factor;
            count++;
        }
        return count;
    };

    bool hasZero = false;
    int zeroX = -1, zeroY = -1;

    dp2[0][0].count = factorCount(grid[0][0], 2);
    dp5[0][0].count = factorCount(grid[0][0], 5);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0) {
                hasZero = true;
                zeroX = i;
                zeroY = j;
            }
            int twos = factorCount(grid[i][j], 2);
            int fives = factorCount(grid[i][j], 5);

            if (i > 0 && dp2[i - 1][j].count + twos < dp2[i][j].count) {
                dp2[i][j] = {dp2[i - 1][j].count + twos, 'D'};
            }
            if (j > 0 && dp2[i][j - 1].count + twos < dp2[i][j].count) {
                dp2[i][j] = {dp2[i][j - 1].count + twos, 'R'};
            }

            if (i > 0 && dp5[i - 1][j].count + fives < dp5[i][j].count) {
                dp5[i][j] = {dp5[i - 1][j].count + fives, 'D'};
            }
            if (j > 0 && dp5[i][j - 1].count + fives < dp5[i][j].count) {
                dp5[i][j] = {dp5[i][j - 1].count + fives, 'R'};
            }
        }
    }

    int minZeros = min(dp2[n - 1][n - 1].count, dp5[n - 1][n - 1].count);
    string path;

    if (hasZero && minZeros > 1) {
        minZeros = 1;
        for (int i = 0; i < zeroX; ++i) path += 'D';
        for (int j = 0; j < zeroY; ++j) path += 'R';
        for (int i = zeroX; i < n - 1; ++i) path += 'D';
        for (int j = zeroY; j < n - 1; ++j) path += 'R';
    } else {
        auto &trace = (dp2[n - 1][n - 1].count < dp5[n - 1][n - 1].count) ? dp2 : dp5;
        int x = n - 1, y = n - 1;
        while (x > 0 || y > 0) {
            path += trace[x][y].move;
            if (trace[x][y].move == 'D') x--;
            else y--;
        }
        reverse(path.begin(), path.end());
    }

    return {minZeros, path};
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));

    for (auto &row : grid)
        for (auto &cell : row)
            cin >> cell;

    auto [minZeros, path] = findPath(grid, n);
    cout << minZeros << endl << path << endl;
    return 0;
}
