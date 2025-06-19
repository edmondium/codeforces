#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double vb, vs;
    cin >> n >> vb >> vs;

    vector<double> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    double xu, yu;
    cin >> xu >> yu;

    const double EPS = 1e-9;
    int bestIdx = 2;                 // We'll start checking from stop 2
    // Compute for stop 2 as initial best
    double dx = xu - x[1];
    double bestRun = sqrt(dx*dx + yu*yu);
    double bestTime = x[1] / vb + bestRun / vs;

    for (int i = 2; i < n; i++) {
        double t_bus = x[i] / vb;
        double dx_i = xu - x[i];
        double run_dist = sqrt(dx_i*dx_i + yu*yu);
        double t_tot = t_bus + run_dist / vs;

        if (t_tot + EPS < bestTime
            || (fabs(t_tot - bestTime) < EPS && run_dist < bestRun)) {
            bestTime = t_tot;
            bestRun  = run_dist;
            bestIdx  = i + 1;  // convert 0-based to 1-based
        }
    }

    cout << bestIdx << "\n";
    return 0;
}
