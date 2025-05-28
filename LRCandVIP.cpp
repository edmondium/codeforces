#include <iostream>
#include <vector>
#include <numeric>  // For std::gcd
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
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // Check if all elements are equal.
        bool allEqual = true;
        for (int i = 1; i < n; i++) {
            if (a[i] != a[0]) {
                allEqual = false;
                break;
            }
        }
        if (allEqual) {
            cout << "No\n";
            continue;
        }
        
        // Find the minimum element.
        int min_val = *min_element(a.begin(), a.end());
        // Choose any index where the value is greater than min_val.
        int chosen = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] != min_val) {
                chosen = i;
                break;
            }
        }
        
        // Because the rest of the group (which has to include at least one occurrence of min_val)
        // will have gcd equal to min_val, and since a[chosen] > min_val, the two gcds differ.
        cout << "Yes\n";
        // Construct the answer assignment:
        // We assign group "1" to the chosen index and group "2" to all other indices.
        // (The roles of 1 and 2 can be swapped arbitrarily.)
        for (int i = 0; i < n; i++) {
            if (i == chosen)
                cout << "1 ";
            else
                cout << "2 ";
        }
        cout << "\n";
    }
    return 0;
}
