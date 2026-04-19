#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> segs(n);
    for (auto &s : segs) {
        cin >> s.first >> s.second;
        if (s.first > s.second) swap(s.first, s.second);
    }
    ranges::sort(segs, {}, &pair<int,int>::second);
    vector<int> nails;
    accumulate(segs.begin(), segs.end(), INT_MIN, [&](int last, auto &seg){
        if (seg.first > last) {
            nails.push_back(seg.second);
            return seg.second;
        }
        return last;
    });
    cout << nails.size() << "\n";
    ranges::for_each(nails, [](int x){ cout << x << " "; });

    int *L = new int[n];
    int *R = new int[n];
    for (int i = 0; i < n; i++) {
        L[i] = segs[i].first;
        R[i] = segs[i].second;
    }
    int *nails_acc = new int[n];
    int nails_count = 0;
    int last = INT_MIN;
    #pragma acc parallel loop copyin(L[0:n],R[0:n]) copy(last,nails_count) copyout(nails_acc[0:n])
    for (int i = 0; i < n; i++) {
        if (L[i] > last) {
            last = R[i];
            nails_acc[nails_count++] = last;
        }
    }
    delete[] L;
    delete[] R;
    delete[] nails_acc;
}
