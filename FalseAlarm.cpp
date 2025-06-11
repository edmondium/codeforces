#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        vector<int> doors(n);
        for (int i = 0; i < n; i++) {
            cin >> doors[i];
        }
        
        bool buttonUsed = false;
        int effectRemaining = 0;
        bool canPass = true;
        
        for (int i = 0; i < n; i++) {
            if (effectRemaining > 0) {
                // Under the effect, the door (regardless of initial state) is open.
                effectRemaining--;
            } else if (doors[i] == 0) {
                // The door is already open.
            } else { 
                // Door is closed and no active effect.
                if (!buttonUsed) {
                    // Use the button and activate the effect.
                    buttonUsed = true;
                    // One second spent passing the door, so the remaining effect is x-1.
                    effectRemaining = x - 1;
                } else {
                    // Button already used and door is closed.
                    canPass = false;
                    break;
                }
            }
        }
        
        cout << (canPass ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
