#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int* cnt = new int[n+1]();
    #pragma acc parallel loop copy(cnt[0:n+1])
    for (int i=2;i<=n;i++) if (!cnt[i])
        for (int j=i;j<=n;j+=i) cnt[j]++;
    cout << ranges::count(span(cnt,n+1),2);
    delete[] cnt;
}
