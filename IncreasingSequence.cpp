#include <bits/stdc++.h>
#include <ranges>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long d;
    cin >> n >> d;
    vector<long long> b(n);
    for (auto &x : b) cin >> x;

    long long moves = 0;

    #pragma omp parallel for reduction(+:moves)
    for (int i = 1; i < n; i++) {
        if (b[i] <= b[i-1]) {
            long long need = b[i-1] - b[i];
            long long k = need / d + 1;
            moves += k;
            b[i] += k * d;
        }
    }

    cout << moves << "\n";
}
