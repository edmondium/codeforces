#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_set<string> active;
    long long totalTraffic = 0;
    string line;
    
    while(getline(cin, line)) {
        if(line.empty()) continue; // Skip any empty input lines
        
        if (line[0] == '+') {
            // Add command: +<name>
            string name = line.substr(1); 
            active.insert(name);
        }
        else if (line[0] == '-') {
            // Remove command: -<name>
            string name = line.substr(1);
            active.erase(name);
        }
        else {
            // Send command: <sender_name>:<message_text>
            // The message text starts after the first ':' character.
            size_t colonPos = line.find(':');
            if (colonPos != string::npos) {
                string message = line.substr(colonPos + 1);
                long long messageLength = static_cast<long long>(message.size());
                // For every send command, server sends l bytes to each active participant.
                totalTraffic += messageLength * active.size();
            }
        }
    }
    
    cout << totalTraffic << "\n";
    return 0;
}
