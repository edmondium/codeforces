#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int mn = *min_element(a.begin(), a.end());
    int res = INT_MAX;

    #pragma acc parallel loop reduction(min:res)
    for (int i = 0; i < n; ++i)
        if (a[i] > mn && a[i] < res) res = a[i];

    if (res == INT_MAX) cout << "NO\n";
    else cout << res << "\n";
}
