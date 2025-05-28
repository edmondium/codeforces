#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        // Frequency array for numbers [1..50]
        vector<int> freq(51, 0);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            freq[arr[i]]++;
        }
        
        // Build prefix sum: prefix[i] = count of numbers <= i.
        vector<int> prefix(52, 0);
        for (int i = 1; i <= 50; i++) {
            prefix[i] = prefix[i - 1] + freq[i];
        }
        
        int bestSubsetSize = 0;
        // Try all candidate pairs (l, r) where l and r are between 1 and 50
        for (int l = 1; l <= 50; l++) {
            if (freq[l] == 0) continue;  // l must appear in the array
            for (int r = l; r <= 50; r++) {
                if (freq[r] == 0) continue;  // r must appear in the array
                // Check if l and r have the same parity
                if ((l + r) % 2 == 0) {
                    // Count numbers in [l, r]
                    int countInRange = prefix[r] - prefix[l - 1];
                    bestSubsetSize = max(bestSubsetSize, countInRange);
                }
            }
        }
        
        // The answer is the number of removals required.
        cout << n - bestSubsetSize << "\n";
    }
    
    return 0;
}
