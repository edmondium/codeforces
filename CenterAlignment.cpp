#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<string> lines;
    string s;
    int maxLength = 0;

    // Read all lines from the input
    while(getline(cin, s)) {
        lines.push_back(s);
        maxLength = max(maxLength, (int)s.size());
    }
    
    // Prepare the top/bottom border
    string border(maxLength + 2, '*');
    cout << border << "\n";
    
    bool toggle = false; // false means extra space goes on the right, true means extra space goes on the left
    for(auto &line : lines) {
        int gap = maxLength - line.size();
        int leftSpaces, rightSpaces;
        
        if(gap % 2 == 0) {
            // Even difference: symmetric
            leftSpaces = rightSpaces = gap / 2;
        } else {
            // Odd difference: alternate allocation.
            if(!toggle) {
                // Start with extra space on the right: left gets floor(gap/2)
                leftSpaces = gap / 2;
                rightSpaces = gap - leftSpaces;
            } else {
                // Afterwards, extra space on the left: left gets ceil(gap/2)
                leftSpaces = gap - gap / 2;
                rightSpaces = gap / 2;
            }
            toggle = !toggle;
        }
        cout << "*" 
             << string(leftSpaces, ' ') << line << string(rightSpaces, ' ')
             << "*" << "\n";
    }
    cout << border;
    
    return 0;
}
