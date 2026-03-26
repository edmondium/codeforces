#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int64_t v;
    cin >> n >> v;

    vector<pair<int,int>> kayaks, catamarans;
    ranges::for_each(views::iota(0,n), [&](int i){
        int t,p; cin>>t>>p;
        (t==1?kayaks:catamarans).emplace_back(p,i+1);
    });

    ranges::sort(kayaks,greater{},&pair<int,int>::first);
    ranges::sort(catamarans,greater{},&pair<int,int>::first);

    vector<int64_t> prefixKayaks(kayaks.size()+1), prefixCat(catamarans.size()+1);
    ranges::for_each(views::iota(0,(int)kayaks.size()),[&](int i){prefixKayaks[i+1]=prefixKayaks[i]+kayaks[i].first;});
    ranges::for_each(views::iota(0,(int)catamarans.size()),[&](int i){prefixCat[i+1]=prefixCat[i]+catamarans[i].first;});

    int bestCat=0,bestKayak=0;
    int64_t bestTotal=0;

    #pragma omp parallel for
    for(int x=0;x<=catamarans.size();x++){
        int64_t used=2LL*x;
        if(used>v) continue;
        int y=min<int64_t>(kayaks.size(),v-used);
        int64_t total=prefixCat[x]+prefixKayaks[y];
        #pragma omp critical
        if(total>bestTotal){bestTotal=total;bestCat=x;bestKayak=y;}
    }

    cout<<bestTotal<<"\n";
    ranges::for_each(views::iota(0,bestCat),[&](int i){cout<<catamarans[i].second<<" ";});
    ranges::for_each(views::iota(0,bestKayak),[&](int i){cout<<kayaks[i].second<<" ";});
}
