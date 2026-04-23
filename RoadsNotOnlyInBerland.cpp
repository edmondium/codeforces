#include <bits/stdc++.h>
using namespace std;

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> p(n+1);
    iota(p.begin(), p.end(), 0);
    function<int(int)> f = [&](int x){return p[x]==x?x:p[x]=f(p[x]);};
    vector<array<int,2>> close, build;
    #pragma acc parallel loop copy(p)
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        int fa=f(a), fb=f(b);
        if(fa==fb) close.push_back({a,b});
        else p[fa]=fb;
    }
    for(int i=2;i<=n;i++){
        int fi=f(i), f1=f(1);
        if(fi!=f1){
            p[fi]=f1;
            build.push_back({1,i});
        }
    }
    cout<<close.size()<<"\n";
    for(size_t i=0;i<close.size();i++)
        cout<<close[i][0]<<" "<<close[i][1]<<" "<<build[i][0]<<" "<<build[i][1]<<"\n";
}
