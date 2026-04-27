#include <bits/stdc++.h>
using namespace std;

struct Truck {
    int id,v,c,l,r,prev;
    void read(int i){ id=i; cin>>v>>c>>l>>r; }
    int total() const { return c+l+r; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    map<int, vector<Truck>> gr;
    for(int i=0;i<n;i++){
        Truck t; t.read(i);
        gr[t.total()].push_back(t);
    }

    int best = 0;
    vector<int> ans;

    for(auto &g : gr){
        auto &a = g.second;
        map<int, pair<int,int>> dp;
        dp.emplace(0, make_pair(0,-1));
        int m = a.size();

        #pragma acc parallel loop independent
        for(int i=0;i<m;i++){
            auto it = dp.find(a[i].l);
            if(it == dp.end()) continue;
            a[i].prev = it->second.second;
            int newcost = it->second.first + a[i].v;
            int key = a[i].l + a[i].c;
            auto it2 = dp.find(key);
            if(it2 == dp.end() || it2->second.first < newcost)
                dp[key] = {newcost, i};
        }

        int total = g.first;
        auto it = dp.find(total);
        if(it == dp.end()) continue;
        if(it->second.first <= best) continue;

        best = it->second.first;
        int last = it->second.second;
        vector<int> cur;
        while(last != -1){
            cur.push_back(a[last].id);
            last = a[last].prev;
        }
        reverse(cur.begin(), cur.end());
        ans = move(cur);
    }

    cout<<ans.size()<<"\n";
    for(int i=0;i<(int)ans.size();i++){
        if(i) cout<<" ";
        cout<<ans[i]+1;
    }
    cout<<"\n";
}
