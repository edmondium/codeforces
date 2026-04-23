#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int oddCount = 0, evenCount = 0;
    int* arr = a.data();  

    #pragma acc parallel loop copyin(arr[0:n]) reduction(+:oddCount,evenCount)
    for (int i = 0; i < n; i++) {
        oddCount += (arr[i] % 2);
        evenCount += !(arr[i] % 2);
    }

    auto oddIdx = ranges::find_if(a, [](int x){ return x % 2; }) - a.begin() + 1;
    auto evenIdx = ranges::find_if(a, [](int x){ return x % 2 == 0; }) - a.begin() + 1;

    cout << (oddCount == 1 ? oddIdx : evenIdx);
}
