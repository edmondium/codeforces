#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 51123987;

auto add = [](int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;
    int m = (n + 2) / 3;

    auto make4D = [&](int val) {
        return vector(3, vector(m+1, vector(m+1, vector<int>(m+1, val))));
    };

    auto pool = make4D(0);
    auto d = make4D(0);

    ranges::for_each(pool, [&](auto &x){ x[0][0][0] = 1; });
    pool[1][0][0][0] = 1;
    pool[2][0][0][0] = 1;

    for (char c : s) {
        if (c == 'a') {
            #pragma acc parallel loop collapse(2)
            for (int v = 0; v <= m; v++)
                for (int w = 0; w <= m; w++) {
                    int t = 0;
                    for (int u = 0; u <= m; u++) {
                        d[0][u][v][w] = add(d[0][u][v][w], t);
                        pool[1][u][v][w] = add(pool[1][u][v][w], t);
                        pool[2][u][v][w] = add(pool[2][u][v][w], t);
                        t = add(t, pool[0][u][v][w]);
                        pool[0][u][v][w] = 0;
                    }
                }
        } else if (c == 'b') {
            #pragma acc parallel loop collapse(2)
            for (int u = 0; u <= m; u++)
                for (int w = 0; w <= m; w++) {
                    int t = 0;
                    for (int v = 0; v <= m; v++) {
                        d[1][u][v][w] = add(d[1][u][v][w], t);
                        pool[0][u][v][w] = add(pool[0][u][v][w], t);
                        pool[2][u][v][w] = add(pool[2][u][v][w], t);
                        t = add(t, pool[1][u][v][w]);
                        pool[1][u][v][w] = 0;
                    }
                }
        } else {
            #pragma acc parallel loop collapse(2)
            for (int u = 0; u <= m; u++)
                for (int v = 0; v <= m; v++) {
                    int t = 0;
                    for (int w = 0; w <= m; w++) {
                        d[2][u][v][w] = add(d[2][u][v][w], t);
                        pool[0][u][v][w] = add(pool[0][u][v][w], t);
                        pool[1][u][v][w] = add(pool[1][u][v][w], t);
                        t = add(t, pool[2][u][v][w]);
                        pool[2][u][v][w] = 0;
                    }
                }
        }
    }

    long long ans = 0;
    #pragma acc parallel loop reduction(+:ans) collapse(2)
    for (int u = 0; u <= m; u++)
        for (int v = 0; v <= m; v++) {
            int w = n - u - v;
            if (w < 0 || w > m) continue;
            if (abs(u-v) > 1 || abs(u-w) > 1 || abs(v-w) > 1) continue;
            ans = (ans + d[0][u][v][w] + d[1][u][v][w] + d[2][u][v][w]) % MOD;
        }

    cout << ans << '\n';
}
