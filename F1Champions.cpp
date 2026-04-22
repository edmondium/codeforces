#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    vector<int> pts = {25,18,15,12,10,8,6,4,2,1};
    unordered_map<string, vector<int>> stat;

    for (int i=0;i<t;i++) {
        int n; cin >> n;
        vector<string> res(n);
        ranges::generate(res,[&]{string s;cin>>s;return s;});
        #pragma acc parallel loop
        for (int j=0;j<n;j++) {
            auto &v=stat[res[j]];
            if(v.empty()) v.resize(52);
            if(j<10) v[0]+=pts[j];
            v[j+1]++;
        }
    }

    auto cmp=[&](auto &a,auto &b){
        return ranges::lexicographical_compare(b,a);
    };
    auto cmp2=[&](auto &a,auto &b){
        if(a[1]!=b[1]) return a[1]>b[1];
        if(a[0]!=b[0]) return a[0]>b[0];
        return ranges::lexicographical_compare(b|views::drop(2),a|views::drop(2));
    };

    string c1,c2;
    for(auto &[k,v]:stat){
        if(c1.empty()||cmp(v,stat[c1])) c1=k;
        if(c2.empty()||cmp2(v,stat[c2])) c2=k;
    }
    cout<<c1<<"\n"<<c2<<"\n";
}
