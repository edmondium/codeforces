#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    unordered_map<string, int> db;
    while (n--) {
        string name;
        cin >> name;
        // If the name is new, output "OK" and mark it as seen.
        if (db[name] == 0) {
            cout << "OK" << "\n";
            db[name] = 1;
        } else {
            // Otherwise, generate a new username by appending the smallest available number.
            int count = db[name];
            string newName = name + to_string(count);
            // Although logically, this inner loop is not normally needed thanks to our counting strategy,
            // we check in case a generated name has been added earlier independently.
            while (db[newName] != 0) {
                count++;
                newName = name + to_string(count);
            }
            // Update the base name count and mark the new name as registered.
            db[name] = count + 1;
            db[newName] = 1;
            cout << newName << "\n";
        }
    }
    return 0;
}
