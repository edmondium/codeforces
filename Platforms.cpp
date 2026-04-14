#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d, m, l;
    if (!(cin >> n >> d >> m >> l)) return 0;

    long long r = 1LL * (n - 1) * m + l;
    long long res = (r / d) * d;
    while (res <= r) res += d;

    vector<char> used(m, 0);
    int pos = 0;
    long long x = 0;
    int stop = 0;

    char* used_ptr = used.data();

    #pragma acc parallel loop reduction(min:res) copy(used_ptr[0:m]) private(pos,x,stop)
    for (int i = 0; i < m; ++i) {
        if (!stop) {
            if (used_ptr[pos]) stop = 1;
            else if (pos > l) { res = min(res, x); stop = 1; }
            else {
                used_ptr[pos] = 1;
                pos = (pos + d) % m;
                x += d;
            }
        }
    }

    cout << res << "\n";
}
