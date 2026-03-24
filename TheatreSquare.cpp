#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    int64_t n, m, a;
    cin >> n >> m >> a;

    vector<int64_t> dims = {
        (n + a - 1) / a,
        (m + a - 1) / a
    };

    int64_t result = 1;
    #pragma omp parallel for reduction(*:result)
    for (int i = 0; i < (int)dims.size(); ++i)
        result *= dims[i];

    cout << result << '\n';
}
