#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

struct Point { double x,y,r; };
array<Point,3> p;
constexpr double eps=1e-5;

double dist(double x,double y,const Point& q){
    return hypot(x-q.x,y-q.y);
}

double cost(double x,double y){
    array<double,3> ang;
    for(int i=0;i<3;i++) ang[i]=dist(x,y,p[i])/p[i].r;
    double ans=0;
    for(int i=0;i<3;i++){
        double d=ang[i]-ang[(i+1)%3];
        ans+=d*d;
    }
    return ans;
}

int main(){
    for(auto& q:p) cin>>q.x>>q.y>>q.r;
    double x=accumulate(p.begin(),p.end(),0.0,[](double acc,const Point& q){return acc+q.x;})/3.0;
    double y=accumulate(p.begin(),p.end(),0.0,[](double acc,const Point& q){return acc+q.y;})/3.0;
    double t=1.0;
    while(t>eps){
        double tp=cost(x,y);
        bool kase=false;
        array<pair<double,double>,4> dirs={{{t,0},{-t,0},{0,-t},{0,t}}};
        #pragma omp parallel for
        for(int i=0;i<4;i++){
            double nx=x+dirs[i].first, ny=y+dirs[i].second;
            if(cost(nx,ny)<tp){
                #pragma omp critical
                { x=nx; y=ny; kase=true; }
            }
        }
        if(!kase) t/=2;
    }
    if(fabs(cost(x,y))<eps) cout<<fixed<<setprecision(5)<<x<<" "<<y<<"\n";
}
