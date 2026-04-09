#include <bits/stdc++.h>
using namespace std;

auto toMinutes = [](int h,int m,bool pm){
    return (!pm && h==12?0:(pm && h<12?h+12:h))*60+m;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    string line; getline(cin,line);

    vector<int> times(n);
    transform(begin(times),end(times),begin(times),[&](int){
        getline(cin,line);
        auto ts=line.substr(1,line.find(']')-1);
        int hh=stoi(ts.substr(0,2)),mm=stoi(ts.substr(3,2));
        bool pm=ts.find("p.m.")!=string::npos;
        return toMinutes(hh,mm,pm);
    });

    int days=1,prev=-1,cnt=0;
    #pragma acc parallel loop reduction(+:days)
    for(int i=0;i<n;i++){
        if(times[i]<prev){days++;cnt=1;}
        else if(times[i]==prev){if(++cnt>10){days++;cnt=1;}}
        else cnt=1;
        prev=times[i];
    }
    cout<<days<<"\n";
}