#include <bits/stdc++.h>
using namespace std;

const int oo = 1000000000;
struct Point { int x,y; };
inline bool operator<(const Point&A,const Point&B){return A.x!=B.x?A.x<B.x:A.y<B.y;}
struct Request { int type; Point p; };

vector<Point> P;
vector<int> topmost;
Point ret{-oo,-oo};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin>>n;
    vector<Request> R;
    for(int i=0;i<n;i++){
        string cmd; int x,y; cin>>cmd>>x>>y;
        int t=(cmd[0]=='a'?1:(cmd[0]=='r'?2:3));
        R.push_back({t,{x,y}});
        if(t!=3) P.push_back({x,y});
    }
    sort(P.begin(),P.end());
    if(P.empty()) P.push_back({0,0});
    int N=(int)P.size();
    topmost.assign(1<<19,-oo);

    auto addPoint=[&](auto&& self,int i,int lo,int hi,int x)->void{
        if(x<lo||x>=hi) return;
        if(lo+1==hi) topmost[i]=P[x].y;
        else{
            int mid=(lo+hi)/2;
            self(self,2*i,lo,mid,x);
            self(self,2*i+1,mid,hi,x);
            topmost[i]=max(topmost[2*i],topmost[2*i+1]);
        }
    };
    auto removePoint=[&](auto&& self,int i,int lo,int hi,int x)->void{
        if(x<lo||x>=hi) return;
        if(lo+1==hi) topmost[i]=-oo;
        else{
            int mid=(lo+hi)/2;
            self(self,2*i,lo,mid,x);
            self(self,2*i+1,mid,hi,x);
            topmost[i]=max(topmost[2*i],topmost[2*i+1]);
        }
    };
    auto findPoint=[&](auto&& self,int i,int lo,int hi,const Point&p)->void{
        if(p.x>=P[hi-1].x||topmost[i]<=p.y) return;
        if(lo+1==hi){
            if(P[lo].x>p.x&&P[lo].y>p.y) ret=P[lo];
        }else{
            int mid=(lo+hi)/2;
            self(self,2*i,lo,mid,p);
            if(ret.x==-oo) self(self,2*i+1,mid,hi,p);
        }
    };

    #pragma acc parallel loop
    for(int i=0;i<n;i++){
        if(R[i].type==1){
            int x=(int)(lower_bound(P.begin(),P.end(),R[i].p)-P.begin());
            addPoint(addPoint,1,0,N,x);
        }else if(R[i].type==2){
            int x=(int)(lower_bound(P.begin(),P.end(),R[i].p)-P.begin());
            removePoint(removePoint,1,0,N,x);
        }else{
            ret={-oo,-oo};
            findPoint(findPoint,1,0,N,R[i].p);
            if(ret.x==-oo) cout<<"-1\n";
            else cout<<ret.x<<" "<<ret.y<<"\n";
        }
    }
}
