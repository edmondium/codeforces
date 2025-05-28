#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int balance = 0;
        bool possible = false;
        // We only need to check until the second last character.
        for (size_t i = 0; i < s.size() - 1; i++) {
            if (s[i] == '(')
                balance++;
            else
                balance--;
            if (balance == 0) { // Found a point before the end where segments meet.
                possible = true;
                break;
            }
        }
        cout << (possible ? "YES" : "NO") << "\n";
    }
    return 0;
}
