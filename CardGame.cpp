#include <iostream>
#include <string>

using namespace std;

// Function to check if card x beats card y.
// Cards are zero-indexed: card 1 is index 0, card n is index n-1.
constexpr bool beats(int n, int x, int y) {
    if (x == 0)
        return y == n - 1;
    if (x == n - 1)
        return y != 0;
    return x > y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        string owner;
        cin >> owner;
        
        bool good = false;
        // Iterate over every card. If the card belongs to Alice ('A'),
        // check if there's any Bob ('B') card that beats it.
        for (int i = 0; i < n; i++) {
            if (owner[i] != 'A')
                continue;
            bool good_move = true;
            for (int j = 0; j < n; j++) {
                if (owner[j] == 'B' && beats(n, j, i)) {
                    good_move = false;
                    break;
                }
            }
            if (good_move) {
                good = true;
                break;
            }
        }
        
        cout << (good ? "Alice" : "Bob") << "\n";
    }
    
    return 0;
}
