#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<bool>> occ(k + 1, vector<bool>(k + 1));
    int xc = (k + 1) / 2, yc = (k + 1) / 2;
    vector<long long> ypref(k + 1);
    ranges::for_each(views::iota(1, k + 1), [&](int y){ ypref[y] = ypref[y - 1] + abs(y - yc); });

    ranges::for_each(views::iota(0, n), [&](int){
        int m; cin >> m;
        long long best = LLONG_MAX;
        int bx = -1, byl = -1;

        #pragma omp parallel for schedule(dynamic)
        for (int x = 1; x <= k; ++x) {
            int free = 0;
            for (int y = 1; y <= k; ++y) {
                free = occ[x][y] ? 0 : free + 1;
                if (free >= m) {
                    int yl = y - m + 1, yr = y;
                    long long rem = 1LL * m * abs(x - xc) + (ypref[yr] - ypref[yl - 1]);
                    #pragma omp critical
                    {
                        if (rem < best || (rem == best && (x < bx || (x == bx && yl < byl)))) {
                            best = rem; bx = x; byl = yl;
                        }
                    }
                }
            }
        }

        if (bx == -1) cout << -1 << '\n';
        else {
            int byr = byl + m - 1;
            cout << bx << " " << byl << " " << byr << '\n';
            ranges::for_each(views::iota(byl, byr + 1), [&](int y){ occ[bx][y] = true; });
        }
    });
}
