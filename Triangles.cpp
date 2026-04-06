#include <bits/stdc++.h>
using namespace std;

static int a[505][505];
static long long rx[505], ry[505], bx[505], by[505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> rx[i] >> ry[i];
    for (int i = 0; i < m; i++) cin >> bx[i] >> by[i];

    #pragma acc parallel loop collapse(2) copyin(rx[0:n], ry[0:n], bx[0:m], by[0:m]) copyout(a)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (rx[i] < rx[j]) {
                long long A = ry[j] - ry[i];
                long long B = rx[i] - rx[j];
                long long C = -A * rx[i] - B * ry[i];
                int cnt = 0;
                for (int k = 0; k < m; k++) {
                    if (bx[k] >= rx[i] && bx[k] < rx[j] && A * bx[k] + B * by[k] + C > 0) cnt++;
                }
                a[i][j] = cnt;
                a[j][i] = -cnt;
            }
        }
    }

    long long ans = 0;
    #pragma acc parallel loop reduction(+:ans) copyin(a)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (a[i][j] + a[j][k] + a[k][i] == 0) ans++;
            }
        }
    }

    cout << ans << "\n";
}
