#include <bits/stdc++.h>
using namespace std;

struct Team {
    string name;
    int points = 0;
    int scored = 0;
    int conceded = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Team> teams(n);
    unordered_map<string,int> idx;
    for (int i = 0; i < n; i++) {
        cin >> teams[i].name;
        idx[teams[i].name] = i;
    }

    int matches = n * (n - 1) / 2;
    vector<string> t1(matches), t2(matches);
    vector<int> s1(matches), s2(matches);

    for (int i = 0; i < matches; i++) {
        string line;
        cin >> line;
        auto dash = line.find('-');
        t1[i] = line.substr(0, dash);
        t2[i] = line.substr(dash + 1);
        string score;
        cin >> score;
        auto colon = score.find(':');
        s1[i] = stoi(score.substr(0, colon));
        s2[i] = stoi(score.substr(colon + 1));
    }

    #pragma acc parallel loop
    for (int i = 0; i < matches; i++) {
        int a = idx[t1[i]], b = idx[t2[i]];
        teams[a].scored += s1[i];
        teams[a].conceded += s2[i];
        teams[b].scored += s2[i];
        teams[b].conceded += s1[i];
        if (s1[i] > s2[i]) teams[a].points += 3;
        else if (s1[i] < s2[i]) teams[b].points += 3;
        else { teams[a].points++; teams[b].points++; }
    }

    sort(teams.begin(), teams.end(), [](auto &x, auto &y) {
        if (x.points != y.points) return x.points > y.points;
        int dx = x.scored - x.conceded, dy = y.scored - y.conceded;
        if (dx != dy) return dx > dy;
        if (x.scored != y.scored) return x.scored > y.scored;
        return x.name < y.name;
    });

    vector<string> qualified;
    for (int i = 0; i < n/2; i++) qualified.push_back(teams[i].name);
    sort(qualified.begin(), qualified.end());
    for (auto &q : qualified) cout << q << "\n";
}
