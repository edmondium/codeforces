#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double A, B, C;
    cin >> A >> B >> C;

    auto solve = [&](double a, double b, double c) {
        if (a == 0 && b == 0 && c == 0) return tuple{-1, vector<double>{}};
        if (a == 0 && b == 0) return tuple{0, vector<double>{}};
        if (a == 0) return tuple{1, vector<double>{-c / b}};
        double D;
        #pragma acc parallel copyin(a,b,c) copyout(D)
        {
            D = b * b - 4 * a * c;
        }
        if (D < 0) return tuple{0, vector<double>{}};
        if (D == 0) return tuple{1, vector<double>{-b / (2 * a)}};
        double r1, r2;
        #pragma acc parallel copyin(a,b,D) copyout(r1,r2)
        {
            r1 = (-b - sqrt(D)) / (2 * a);
            r2 = (-b + sqrt(D)) / (2 * a);
        }
        if (r1 > r2) swap(r1, r2);
        return tuple{2, vector<double>{r1, r2}};
    };

    auto [cnt, roots] = solve(A, B, C);
    if (cnt == -1) cout << -1 << "\n";
    else {
        cout << cnt << "\n";
        for (auto x : roots)
            cout << fixed << setprecision(5) << x << "\n";
    }
}
