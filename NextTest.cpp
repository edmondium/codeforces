#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    int* vis = new int[3002]();
    #pragma acc parallel loop copyin(a[0:n]) copy(vis[0:3002])
    for (int i = 0; i < n; i++) vis[a[i]] = 1;
    auto it = ranges::find_if(ranges::iota_view(1, 3002), [&](int x){return !vis[x];});
    cout << *it << '\n';
    delete[] a;
    delete[] vis;
}
