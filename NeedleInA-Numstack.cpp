#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

// Performs an interactive query at 0-indexed position `pos`
// Note: the interactive protocol expects 1-indexed positions.
ll ask(ll pos) {
    cout << "? " << pos + 1 << "\n" << flush;
    ll value;
    cin >> value;
    return value;
}

// Reports that there is no unique answer.
void noans() {
    cout << "! -1" << "\n" << flush;
}

// Reports the found lengths a and b.
void ans(ll a, ll b) {
    cout << "! " << a << " " << b << "\n" << flush;
}

void solve() {
    ll n, k;
    cin >> n >> k;
    
    // Read the first k elements from the start and last k elements from the end.
    // Here the arrays A and B represent the queried snapshots from the beginning and end of C.
    vector<ll> A(k), B(k);
    for (ll i = 0; i < k; ++i)
        A[i] = ask(i);
    for (ll i = n - k; i < n; ++i)
        B[i % k] = ask(i);

    // ui will store the positions in [0, k-1] where the two arrays differ.
    vector<ll> ui;
    for (ll i = 0; i < k; ++i)
        if (A[i] != B[i])
            ui.push_back(i);
    
    // If there is no discrepancy in the first and last k queried elements,
    // then the only possibility is that the arrays are exactly of size k.
    if (ui.empty()) {
        if (n == k * 2)
            ans(k, k);
        else
            noans();
        return;
    }
    
    // Let low = ui[0] (the first index where A and B differ)
    // and define hi such that hi = ui[0] + (n - 1)/k * k,
    // essentially spanning the maximum number of k-steps up to n - 1.
    ll le = ui[0];
    ll multiplier = (n - 1) / k;
    ll ri = ui[0] + multiplier * k;
    
    // Binary search on the positions (in jumps of size k) to determine
    // the boundary between arrays A and B in the concatenated array.
    while (le + k != ri) {
        ll diffSteps = (ri - le) / k;
        ll midSteps = diffSteps / 2;
        ll mid = le + midSteps * k;
        if (ask(mid) == A[ui[0]])
            le = mid;
        else
            ri = mid;
    }
    
    // Now binary search on the discrepancy positions stored in ui.
    ll lee = 0, rii = ui.size();
    while (lee + 1 != rii) {
        ll mid = (lee + rii) / 2;
        // Check using the offset (le - ui[0]) applied to the corresponding ui element.
        if (ask(le - ui[0] + ui[mid]) == A[ui[mid]])
            lee = mid;
        else
            rii = mid;
    }
    
    // Define two candidate positions based on the binary searches.
    ll pos1 = max(le - ui[0] + ui[lee], k - 1);
    ll candidate = (rii == ui.size() ? ui[0] + k : ui[rii]);
    ll pos2 = min(le - ui[0] + candidate, n - k);
    
    // If these candidate positions cannot form a single split point, then answer is ambiguous.
    if (pos1 + 1 != pos2) {
        noans();
        return;
    }
    // Otherwise, pos2 gives the length of the first array, and (n - pos2) the length of the second.
    ans(pos2, n - pos2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
