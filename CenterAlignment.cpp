#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string s;
    int maxLength = 0;
    while (getline(cin, s)) {
        lines.push_back(s);
        maxLength = max(maxLength, (int)s.size());
    }

    string border(maxLength + 2, '*');
    cout << border << "\n";

    vector<string> output(lines.size());
    bool toggle = false;

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < (int)lines.size(); i++) {
        int gap = maxLength - (int)lines[i].size();
        int leftSpaces, rightSpaces;
        if (gap % 2 == 0) {
            leftSpaces = rightSpaces = gap / 2;
        } else {
            bool localToggle;
            #pragma omp critical
            {
                localToggle = toggle;
                toggle = !toggle;
            }
            if (!localToggle) {
                leftSpaces = gap / 2;
                rightSpaces = gap - leftSpaces;
            } else {
                leftSpaces = gap - gap / 2;
                rightSpaces = gap / 2;
            }
        }
        output[i] = "*" + string(leftSpaces, ' ') + lines[i] + string(rightSpaces, ' ') + "*";
    }

    for (auto &line : output) cout << line << "\n";
    cout << border;
}
