#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<string,int>> rounds(n);
    for (auto &[name, score] : rounds) cin >> name >> score;

    unordered_map<string,int> scores;
    #pragma omp parallel
    {
        unordered_map<string,int> local;
        #pragma omp for nowait
        for (int i = 0; i < n; i++) local[rounds[i].first] += rounds[i].second;
        #pragma omp critical
        for (auto &[k,v] : local) scores[k] += v;
    }

    int max_score = ranges::max_element(scores,
        {}, [](auto &p){ return p.second; })->second;

    unordered_map<string,int> cumulative;
    for (auto &[name, score] : rounds) {
        cumulative[name] += score;
        if (cumulative[name] >= max_score && scores[name] == max_score) {
            cout << name << '\n';
            break;
        }
    }
}
