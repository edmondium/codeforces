#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double vb, vs;
    cin >> n >> vb >> vs;

    vector<double> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    double xu, yu;
    cin >> xu >> yu;

    const double EPS = 1e-9;
    vector<pair<double,int>> results(n);

    #pragma omp parallel for
    for (int i = 1; i < n; i++) {
        double t_bus = x[i] / vb;
        double dx = xu - x[i];
        double run = sqrt(dx*dx + yu*yu);
        double t_tot = t_bus + run / vs;
        results[i] = {t_tot * (1 + EPS) + run * 1e-12, i+1};
    }

    auto best = ranges::min_element(results | views::drop(1),
        [](auto a, auto b){ return a.first < b.first; });

    cout << best->second << '\n';
}
