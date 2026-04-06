#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
    ll x,y;
    auto operator+(const Point& o) const { return Point{x+o.x,y+o.y}; }
    auto operator-(const Point& o) const { return Point{x-o.x,y-o.y}; }
    auto operator*(const Point& o) const { return x*o.y - y*o.x; }
    auto operator&(const Point& o) const { return x*o.x + y*o.y; }
    auto len() const { return x*x+y*y; }
    auto operator!=(const Point& o) const { return x!=o.x||y!=o.y; }
};

struct Line { Point a,b; };

bool check2(const Point& v_cut,const Point& v_leg){
    return (v_cut*v_leg)==0 && (v_cut&v_leg)>0 &&
           (v_cut.len()*25>=v_leg.len()) &&
           (v_cut.len()*25<=v_leg.len()*16);
}

bool check(const Line& L1,const Line& L2,const Line& L3){
    auto O=L1.a;
    if(O!=L2.a) return false;
    auto v1=L1.b-O,v2=L2.b-O;
    if((v1&v2)<0) return false;
    return check2(L3.a-O,v1)&&check2(L3.b-O,v2);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    vector<string> out(t);
    #pragma acc parallel loop
    for(int i=0;i<t;i++){
        array<Line,3> seg;
        for(auto& s:seg) cin>>s.a.x>>s.a.y>>s.b.x>>s.b.y;
        bool ok=false;
        for(int f0=0;f0<2&&!ok;f0++){
            for(int f1=0;f1<2&&!ok;f1++){
                for(int f2=0;f2<2&&!ok;f2++){
                    for(int r=0;r<3&&!ok;r++){
                        int s=(r+1)%3,u=(r+2)%3;
                        if(check(seg[r],seg[s],seg[u])) ok=true;
                    }
                    swap(seg[0].a,seg[0].b);
                }
                swap(seg[1].a,seg[1].b);
            }
            swap(seg[2].a,seg[2].b);
        }
        out[i]=ok?"YES\n":"NO\n";
    }
    for(auto& s:out) cout<<s;
}
