#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<string, int>> rounds(n);
    unordered_map<string, int> scores;
    for (auto &[name, score] : rounds) {
        cin >> name >> score;
        scores[name] += score;
    }

    int max_score = max_element(scores.begin(), scores.end(),
        [](const auto &a, const auto &b) { return a.second < b.second; })->second;

    unordered_map<string, int> cumulative_scores;
    for (const auto &[name, score] : rounds) {
        cumulative_scores[name] += score;
        if (cumulative_scores[name] >= max_score && scores[name] == max_score) {
            cout << name << endl;
            break;
        }
    }

    return 0;
}
