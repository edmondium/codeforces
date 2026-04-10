#include <bits/stdc++.h>
using namespace std;

static constexpr int MOD = 51123987;

auto add = [](int a, int b){ return (a += b) >= MOD ? a - MOD : a; };
auto subm = [](int a, int b){ return (a -= b) < 0 ? a + MOD : a; };
auto mul = [](long long a, long long b){ return int((a * b) % MOD); };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; string s;
    cin >> n >> s;

    vector<int> d1(n), d2(n);
    for (int i=0,l=0,r=-1;i<n;i++){
        int k=(i>r?1:min(d1[l+r-i],r-i+1));
        while(i-k>=0&&i+k<n&&s[i-k]==s[i+k]) k++;
        d1[i]=k--;
        if(i+k>r){ l=i-k; r=i+k; }
    }
    for (int i=0,l=0,r=-1;i<n;i++){
        int k=(i>r?0:min(d2[l+r-i+1],r-i+1));
        while(i-k-1>=0&&i+k<n&&s[i-k-1]==s[i+k]) k++;
        d2[i]=k--;
        if(i+k>r){ l=i-k-1; r=i+k; }
    }

    vector<int> startDiff(n+2), endDiff(n+2);
    for (int idx=1;idx<=n;idx++){
        int i=idx-1;
        int l=idx-d1[i]+1, r=idx+d1[i]-1;
        startDiff[l]=add(startDiff[l],1);
        startDiff[idx+1]=subm(startDiff[idx+1],1);
        endDiff[idx]=add(endDiff[idx],1);
        endDiff[r+1]=subm(endDiff[r+1],1);
        if(d2[i]>0){
            l=idx-d2[i]; r=idx+d2[i]-1;
            startDiff[l]=add(startDiff[l],1);
            startDiff[idx]=subm(startDiff[idx],1);
            endDiff[idx]=add(endDiff[idx],1);
            endDiff[r+1]=subm(endDiff[r+1],1);
        }
    }

    vector<int> startCount(n+2), endCount(n+2);
    long long totalPals=0;
    for(int i=1;i<=n;i++){
        startCount[i]=add(startCount[i-1],startDiff[i]);
        endCount[i]=add(endCount[i-1],endDiff[i]);
        totalPals=(totalPals+startCount[i])%MOD;
    }

    int totalPairs=mul(totalPals,(totalPals-1+MOD)%MOD);
    totalPairs=mul(totalPairs,(MOD+1)/2);

    vector<int> suffixStart(n+3);
    for(int i=n;i>=1;i--) suffixStart[i]=add(startCount[i],suffixStart[i+1]);

    int disj=0;
    #pragma acc parallel loop reduction(+:disj)
    for(int j=1;j<n;j++) disj=add(disj,mul(endCount[j],suffixStart[j+1]));

    int answer=subm(totalPairs,disj);
    cout<<answer<<"\n";
}
