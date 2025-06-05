#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    string start, target;
    cin >> start >> target;
    
    // Map chess notation to numeric coordinates
    int sx = start[0] - 'a' + 1;
    int sy = start[1] - '0';
    int tx = target[0] - 'a' + 1;
    int ty = target[1] - '0';
    
    int moves = max(abs(tx - sx), abs(ty - sy));
    cout << moves << "\n";
    
    // Construct each step ensuring horizontal letter is first
    while (sx != tx || sy != ty) {
        string move = "";
        // Decide horizontal movement
        if (tx > sx) {
            move += "R";
            sx++;
        } else if (tx < sx) {
            move += "L";
            sx--;
        }
        // Decide vertical movement (appended after the horizontal letter)
        if (ty > sy) {
            move += "U";
            sy++;
        } else if (ty < sy) {
            move += "D";
            sy--;
        }
        cout << move << "\n";
    }
    
    return 0;
}
