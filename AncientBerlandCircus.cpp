#include <bits/stdc++.h>
#include <format>
#include <omp.h>
using namespace std;

using Point = array<double,2>;
using Triangle = array<Point,3>;

auto gcd_angle = [](double a, double b) {
    function<double(double,double)> f = [&](double x,double y){
        return fabs(y) <= 1e-2 ? x : f(y,fmod(x,y));
    };
    return f(a,b);
};

auto dist = [](const Point& p1,const Point& p2){
    return hypot(p2[0]-p1[0],p2[1]-p1[1]);
};

int main(){
    Triangle point;
    array<double,3> dis,angle;
    double sum=0,area,r,res;
    res = acos(-1.0);

    for(auto& p:point) cin>>p[0]>>p[1];

    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<3;i++){
        dis[i]=dist(point[i],point[(i+1)%3]);
        sum+=dis[i];
    }

    double p=sum/2;
    area=sqrt(p*(p-dis[0])*(p-dis[1])*(p-dis[2]));
    r=(dis[0]*dis[1]*dis[2])/(4*area);

    #pragma omp parallel for
    for(int i=0;i<3;i++){
        double v=1-dis[i]*dis[i]/(2*r*r);
        v=clamp(v,-1.0,1.0);
        angle[i]=acos(v);
    }

    angle[2]=2*res-angle[0]-angle[1];
    for(int i=1;i<3;i++) angle[i]=gcd_angle(angle[i-1],angle[i]);

    cout<<format("{:.6f}\n",r*r*sin(angle[2])*res/angle[2]);
}
