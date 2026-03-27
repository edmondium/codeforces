#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> names(n);
    for (int i = 0; i < n; i++) cin >> names[i];

    unordered_map<string,int> db;
    vector<string> results(n);

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        string name = names[i];
        #pragma omp critical
        {
            if (db[name] == 0) {
                results[i] = "OK";
                db[name] = 1;
            } else {
                string newName = name + to_string(db[name]++);
                results[i] = newName;
                db[newName] = 1;
            }
        }
    }

    for (auto &r : results) cout << r << '\n';
}
