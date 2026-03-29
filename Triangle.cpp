#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    array<int,4> v;
    for (auto &x : v) cin >> x;

    auto tr = [](int a,int b,int c){ return (a+b>c)&&(a+c>b)&&(b+c>a); };
    auto seg = [](int a,int b,int c){ return (a==b+c)||(b==a+c)||(c==a+b); };

    bool normal = false, deg = false;

    #pragma omp parallel for reduction(||:normal,deg)
    for (int i=0;i<4;i++)
        for (int j=i+1;j<4;j++)
            for (int k=j+1;k<4;k++) {
                normal = normal || tr(v[i],v[j],v[k]);
                deg = deg || seg(v[i],v[j],v[k]);
            }

    cout << (normal ? "TRIANGLE" : deg ? "SEGMENT" : "IMPOSSIBLE") << '\n';
}
