#include <bits/stdc++.h>
#include <complex>
#include <omp.h>
using namespace std;

using point = complex<double>;
using circle = pair<point,double>;
constexpr double eps = 1e-10;
double T1,T2;
point cinema,shop,home;

auto dist = [](const point&a,const point&b){return abs(a-b);};
auto readPoint=[](){double x,y;cin>>x>>y;return point(x,y);};
auto isIn=[](const circle&a,const circle&b){return dist(a.first,b.first)+a.second<b.second+eps;};
auto isInPoint=[](const point&p,const circle&c){return dist(p,c.first)<c.second+eps;};
auto doesIntersect=[](const circle&a,const circle&b){return dist(a.first,b.first)<a.second+b.second+eps;};

auto getNewCoords=[](point e1prime,point e2prime,point P,point A){
    double c1=A.real()-P.real(),c2=A.imag()-P.imag();
    return point(c1*e1prime.real()+c2*e2prime.real(),c1*e1prime.imag()+c2*e2prime.imag());
};
auto getOldCoords=[](point e1prime,point e2prime,point P,point A){
    double x=A.real()*e1prime.real()+A.imag()*e2prime.real()+P.real();
    double y=A.real()*e1prime.imag()+A.imag()*e2prime.imag()+P.imag();
    return point(x,y);
};

auto getIntersectedPoints=[](const circle&C1,const circle&C2){
    point P=C1.first;
    point e1prime=(C2.first-C1.first)/abs(C2.first-C1.first);
    point e2prime=point(e1prime.imag(),-e1prime.real());
    point B=getNewCoords(e1prime,e2prime,P,C2.first);
    double R1=C1.second*C1.second,R2=C2.second*C2.second,b=B.real();
    double x=(b*b+R1-R2)/(2.0*b),Y=R1-x*x;
    if(Y<0.0)Y=0.0;
    vector<point>ret;
    if(Y<eps)ret.push_back(point(x,Y));
    else ret={point(x,sqrt(Y)),point(x,-sqrt(Y))};
    for(auto&i:ret)i=getOldCoords(e1prime,e2prime,P,i);
    return ret;
};

auto my_comp=[](const circle&c1,const circle&c2){
    if(c1.first.real()!=c2.first.real())return c1.first.real()<c2.first.real();
    if(c1.first.imag()!=c2.first.imag())return c1.first.imag()<c2.first.imag();
    return c1.second<c2.second;
};

auto intersect3Circles=[](vector<circle>circles){
    sort(circles.begin(),circles.end(),my_comp);
    do{
        if(!doesIntersect(circles[0],circles[1]))return false;
        if(isIn(circles[0],circles[1]))return doesIntersect(circles[0],circles[2]);
    }while(next_permutation(circles.begin(),circles.end(),my_comp));
    sort(circles.begin(),circles.end(),my_comp);
    do{
        auto pts=getIntersectedPoints(circles[0],circles[1]);
        if(ranges::any_of(pts,[&](auto&p){return isInPoint(p,circles[2]);}))return true;
    }while(next_permutation(circles.begin(),circles.end(),my_comp));
    return false;
};

auto check=[](double Q){
    vector<circle>circles(3);
    circles[0]={cinema,Q};
    circles[1]={shop,max(0.0,T1-dist(shop,home)-Q)};
    circles[2]={home,max(0.0,T2-Q)};
    return intersect3Circles(circles);
};

int main(){
    cout.setf(ios::fixed);cout.precision(9);
    double t1,t2;cin>>t1>>t2;
    cinema=readPoint();home=readPoint();shop=readPoint();
    T2=t2+dist(cinema,home);
    T1=t1+dist(cinema,shop)+dist(shop,home);
    if(dist(cinema,shop)+dist(shop,home)<T2+eps){cout<<min(T1,T2)<<endl;return 0;}
    double L=0.0,R=min(T1,T2);
    #pragma omp parallel for reduction(max:L) reduction(min:R)
    for(int step=1;step<=40;++step){
        double Q=(L+R)/2.0;
        if(check(Q))L=Q;else R=Q;
    }
    cout<<(L+R)/2.0<<endl;
}
