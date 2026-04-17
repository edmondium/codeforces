#include <bits/stdc++.h>
using namespace std;

auto valid = [](string_view s,int lo,int hi){
    return !s.empty() && s.size()>=lo && s.size()<=hi &&
           ranges::all_of(s,[](char c){return isalnum(c)||c=='_';});
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string x;cin>>x;
    auto at=x.find('@');
    if(at==string::npos) return cout<<"NO\n",0;
    string u=x.substr(0,at);
    auto slash=x.find('/',at+1);
    string h=x.substr(at+1,(slash==string::npos?x.size():slash)-at-1);
    string r=slash==string::npos?"" : x.substr(slash+1);
    if(!valid(u,1,16)) return cout<<"NO\n",0;
    if(h.empty()||h.size()>32) return cout<<"NO\n",0;
    vector<string> parts;string tmp;
    for(char c:h){
        if(c=='.'){
            if(tmp.empty()) return cout<<"NO\n",0;
            parts.push_back(tmp);tmp.clear();
        }else tmp.push_back(c);
    }
    if(tmp.empty()) return cout<<"NO\n",0;
    parts.push_back(tmp);
    bool ok=true;
    #pragma acc parallel loop reduction(&:ok)
    for(int i=0;i<(int)parts.size();i++){
        if(!valid(parts[i],1,16)) ok=false;
    }
    if(!ok) return cout<<"NO\n",0;
    if(slash!=string::npos && !valid(r,1,16)) return cout<<"NO\n",0;
    cout<<"YES\n";
}
