#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <ranges>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        vector<long long> left(n), right(n);
        
        for (int i = 0; i < n; i++) {
            cin >> left[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> right[i];
        }
        
        long long safeSum = 0;
        vector<long long> extras;
        extras.resize(n);
        
        for (int i = 0; i < n; i++) {
            // "Safe" count is the maximum number from one side.
            long long safe = max(left[i], right[i]);
            safeSum += safe;
            // The "extra" gloves that could contribute to forming a pair.
            extras[i] = (left[i] + right[i]) - safe;
        }
        
        // Sort extras in descending order using C++23 ranges.
        ranges::sort(extras, greater());
        
        // Sum the largest (k - 1) extras.
        long long extraSum = 0;
        int extrasToTake = min(k - 1, n); // Since k <= n, this is safe.
        for (int i = 0; i < extrasToTake; i++) {
            extraSum += extras[i];
        }
        
        // The answer is one more than the maximum number of gloves
        // that can be selected without forcing k distinct pairs.
        long long ans = safeSum + extraSum + 1;
        cout << ans << endl;
    }
    
    return 0;
}
