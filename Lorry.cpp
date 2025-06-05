#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    // Use a 64-bit variable for v because v can be as large as 10^9.
    int64_t v;
    cin >> n >> v;

    // We will store pairs (capacity, index). There are two groups: type==1 (kayaks) and type==2 (catamarans)
    vector<pair<int, int>> kayaks;      // (p, original_index)
    vector<pair<int, int>> catamarans;  // (p, original_index)

    for (int i = 0; i < n; i++) {
        int t, p;
        cin >> t >> p;
        if (t == 1) {
            kayaks.push_back({p, i + 1});
        } else {
            catamarans.push_back({p, i + 1});
        }
    }

    // Sort both lists in descending order (largest p first)
    sort(kayaks.begin(), kayaks.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first > b.first;
    });
    sort(catamarans.begin(), catamarans.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first > b.first;
    });

    // Precompute prefix sums to quickly sum the best x waterborne vehicles from each list.
    int kayakSize = kayaks.size(), catSize = catamarans.size();
    vector<int64_t> prefixKayaks(kayakSize + 1, 0);
    vector<int64_t> prefixCat(catSize + 1, 0);
    
    for (int i = 0; i < kayakSize; i++) {
        prefixKayaks[i + 1] = prefixKayaks[i] + kayaks[i].first;
    }
    for (int i = 0; i < catSize; i++) {
        prefixCat[i + 1] = prefixCat[i] + catamarans[i].first;
    }
    
    // Now decide how many catamarans (each takes 2 cubic metres) to take.
    // For each possible count, fill the remaining capacity with the best kayaks.
    int bestCatCount = 0, bestKayakCount = 0;
    int64_t bestTotal = 0;
    
    // x is the number of catamarans taken.
    for (int x = 0; x <= catSize; x++) {
        // All catamarans take 2*x volume.
        int64_t usedVolume = 2LL * x;
        if (usedVolume > v)
            break;
        // The remaining capacity can hold that many kayaks (each occupies 1).
        int y = min((int64_t)kayakSize, v - usedVolume);
        int64_t currentTotal = prefixCat[x] + prefixKayaks[y];
        if (currentTotal > bestTotal) {
            bestTotal = currentTotal;
            bestCatCount = x;
            bestKayakCount = y;
        }
    }
    
    // Output the optimal total carrying capacity.
    cout << bestTotal << "\n";
    // Output the indices of the vehicles making up the optimal set.
    // Here the catamarans (first bestCatCount) and then kayaks (first bestKayakCount) from the sorted order.
    for (int i = 0; i < bestCatCount; i++)
        cout << catamarans[i].second << " ";
    for (int i = 0; i < bestKayakCount; i++)
        cout << kayaks[i].second << " ";
    
    return 0;
}
