#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    // A stack to store indices. We start with -1 as a sentinel.
    stack<int> st;
    st.push(-1);

    int maxLength = 0;
    long long count = 0;  // Use long long for counting occurrences

    // Process each character in the string.
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            st.push(i);
        } else { // When s[i] == ')'
            st.pop();
            if (st.empty()) {
                // If stack is empty, push the current index as new start.
                st.push(i);
            } else {
                int length = i - st.top();
                if (length > maxLength) {
                    maxLength = length;
                    count = 1;
                } else if (length == maxLength) {
                    count++;
                }
            }
        }
    }

    // According to the problem statement, if no valid substring found,
    // the answer should be "0 1".
    if (maxLength == 0) {
        count = 1;
    }
    cout << maxLength << " " << count << "\n";
    return 0;
}
