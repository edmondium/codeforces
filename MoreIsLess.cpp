#include <iostream>
#include <algorithm>
using namespace std;

void solve() {
    int n, a, b, x;
    cin >> n >> a >> b >> x;
    
    int safeLeft = 0, safeRight = 0;
    
    // For stones lighter than x.
    if(x > 1) {
        // There are (x-1) stones; using internal eliminations you can remove up to min(a, x-2) of them.
        safeLeft = (x - 1) - min(a, x - 2);
    }
    
    // For stones heavier than x.
    if(x < n) {
        // There are (n-x) stones; by internal maximizer moves you can remove up to min(b, n-x-1).
        safeRight = (n - x) - min(b, n - x - 1);
    }
    
    // For a valid strategy, the safe moves required for the left side must be performed with the available maximizer moves,
    // and similarly, safe moves required for the right side must fit within the remaining minimizer moves.
    if (safeLeft <= b && safeRight <= a)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    
    return 0;
}
