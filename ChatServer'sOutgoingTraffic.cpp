#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    while (getline(cin, line)) if (!line.empty()) lines.push_back(line);

    unordered_set<string> active;
    long long totalTraffic = 0;

    for (auto& l : lines) {
        if (l[0] == '+') active.insert(l.substr(1));
        else if (l[0] == '-') active.erase(l.substr(1));
        else {
            size_t pos = l.find(':');
            if (pos != string::npos) {
                string msg = l.substr(pos + 1);
                long long len = msg.size();
                long long participants = active.size();
                #pragma omp parallel reduction(+:totalTraffic)
                {
                    totalTraffic += len * participants;
                }
            }
        }
    }

    cout << totalTraffic << '\n';
}
