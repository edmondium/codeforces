#include <bits/stdc++.h>
using namespace std;

int toMinutes(int h, int m, bool isPM) {
    if (!isPM && h == 12) h = 0;
    if ( isPM && h < 12) h += 12;
    return h * 60 + m;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string line;
    getline(cin, line); // consume newline

    int days = 1;
    int prevTime = -1;
    int sameCount = 0;

    for(int i = 0; i < n; i++){
        getline(cin, line);
        auto close = line.find(']');
        string ts = line.substr(1, close - 1);  // "hh:mm x.m."

        int hh = stoi(ts.substr(0,2));
        int mm = stoi(ts.substr(3,2));
        bool isPM = (ts[6] == 'p');

        int currTime = toMinutes(hh, mm, isPM);

        if (currTime < prevTime) {
            // midnight rollover
            days++;
            sameCount = 1;
        }
        else if (currTime == prevTime) {
            // repeated timestamp
            sameCount++;
            if (sameCount > 10) {
                // too many logs in one minute → new day
                days++;
                sameCount = 1;
            }
        }
        else {
            // strictly later time
            sameCount = 1;
        }

        prevTime = currTime;
    }

    cout << days << "\n";
    return 0;
}
