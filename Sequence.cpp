#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL<<62);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll* a = new ll[N];
    ll* b = new ll[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b, b + N);

    ll* prev = new ll[N];
    ll* cur  = new ll[N];
    for (int k = 0; k < N; k++) {
        prev[k] = llabs(a[0] - b[k]);
        if (k) prev[k] = min(prev[k], prev[k-1]);
    }

    for (int i = 1; i < N; i++) {
        ll best = INF;
        #pragma acc parallel loop copyin(prev[0:N],a[0:N],b[0:N]) copy(best) copyout(cur[0:N])
        for (int k = 0; k < N; k++) {
            best = min(best, prev[k]);
            cur[k] = best + llabs(a[i] - b[k]);
        }
        for (int k = 1; k < N; k++) {
            cur[k] = min(cur[k], cur[k-1]);
        }
        swap(prev, cur);
    }

    cout << prev[N-1] << '\n';

    delete[] a;
    delete[] b;
    delete[] prev;
    delete[] cur;
}
