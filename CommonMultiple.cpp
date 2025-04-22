#include <iostream>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        // Use a set to store unique elements.
        set<int> uniqueElements;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            uniqueElements.insert(x);
        }
        // The maximum beautiful subsequence size is the number of distinct elements.
        cout << uniqueElements.size() << endl;
    }
    
    return 0;
}
