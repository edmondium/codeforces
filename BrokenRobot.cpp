#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;
using namespace std::ranges;

auto tridiagonal_solve = [](auto a, auto b, auto c, auto d) {
    int n = b.size();
    vector<double> x(n);
    c[0] /= b[0];
    d[0] /= b[0];
    #pragma acc parallel loop
    for (int i = 1; i < n; i++) {
        double id = 1.0 / (b[i] - c[i - 1] * a[i]);
        c[i] *= id;
        d[i] = (d[i] - d[i - 1] * a[i]) * id;
    }
    x[n - 1] = d[n - 1];
    #pragma acc parallel loop
    for (int i = n - 2; i >= 0; i--) x[i] = d[i] - c[i] * x[i + 1];
    return x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, row, col;
    cin >> n >> m >> row >> col;
    n -= row;
    col--;

    vector<double> a(m, 0.0);

    for (int step = 0; step < n; step++) {
        vector<double> l(m), b(m), r(m), d(m);

        #pragma acc parallel loop
        for (int i = 0; i < m; i++) {
            int moves = 2 + (i > 0) + (i < m - 1);
            l[i] = (i > 0 ? -1.0/moves : 0.0);
            b[i] = 1.0 - 1.0/moves;
            r[i] = (i < m-1 ? -1.0/moves : 0.0);
            d[i] = 1.0 + a[i]/moves;
        }

        a = tridiagonal_solve(l, b, r, d);
    }

    cout << fixed << setprecision(10) << a[col] << "\n";
}
