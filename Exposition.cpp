#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    int best = 0;
    vector<pair<int,int>> ans;

    #pragma omp parallel
    {
        int local_best = 0;
        vector<pair<int,int>> local_ans;
        deque<int> maxDQ, minDQ;
        int l = 0;

        #pragma omp for schedule(dynamic)
        for (int r = 0; r < n; r++) {
            while (!maxDQ.empty() && h[maxDQ.back()] <= h[r]) maxDQ.pop_back();
            maxDQ.push_back(r);
            while (!minDQ.empty() && h[minDQ.back()] >= h[r]) minDQ.pop_back();
            minDQ.push_back(r);
            while (h[maxDQ.front()] - h[minDQ.front()] > k) {
                if (maxDQ.front() == l) maxDQ.pop_front();
                if (minDQ.front() == l) minDQ.pop_front();
                l++;
            }
            int len = r - l + 1;
            if (len > local_best) {
                local_best = len;
                local_ans.clear();
                local_ans.emplace_back(l + 1, r + 1);
            } else if (len == local_best) {
                local_ans.emplace_back(l + 1, r + 1);
            }
        }

        #pragma omp critical
        {
            if (local_best > best) {
                best = local_best;
                ans = move(local_ans);
            } else if (local_best == best) {
                ans.insert(ans.end(), local_ans.begin(), local_ans.end());
            }
        }
    }

    cout << best << " " << ans.size() << "\n";
    ranges::for_each(ans, [](auto &p) {
        cout << p.first << " " << p.second << "\n";
    });
}
