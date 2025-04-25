#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int T, n, p;
int getans() {
    int mul = 1, res = 0;
    while (mul < n) mul *= 3, res++;
    return res;
}

int t[N][25];
unordered_map<int, int> id;

int b[25];
void get(int pos, int num) {
    int lst = 0, x = num;
    for (int i = 1; i <= p; i++) b[i] = x % 3, x /= 3;
    for (int i = 1; i <= p; i++) {
        if (b[i] <= 1) continue;
        b[i] -= 3, b[i + 1]++;
    }
    for (int i = 1; i <= p; i++) t[pos][i] = b[i], t[pos + 1][i] = -b[i];
}

void clr() {
    id.clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= p + 1; j++) t[i][j] = 0;
}

void init() {
    clr();
    for (int i = 1; i < n; i += 2) {
        int x = (i + 1) >> 1;
        get(i, x);
    }
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= p; j++) sum += t[i][j];
        while (sum < -1) sum += 3; while (sum > 1) sum -= 3;
        t[i][p + 1] = sum;
    }
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = p; j >= 1; j--) sum = sum * 3 + t[i][j];
        id[sum] = i;
    }
}

vector<int> l, r;
char s[N]; int ans[N];
void print() {
    printf("%d\n", p + 1);
    for (int i = 1; i <= p + 1; i++) {
        l.clear(), r.clear();
        for (int j = 1; j <= n; j++)
            if (t[j][i] == -1) l.push_back(j);
            else if (t[j][i] == 1) r.push_back(j);
        printf("%d ", (int)l.size() + (int)r.size());
        for (int it : l) printf("%d ", it);
        for (int it : r) printf("%d ", it); puts("");
    }
    fflush(stdout), scanf("\n %s", s + 1);
}

void solve() {
    int pos = 0;
    for (int i = 1; i <= p + 1; i++) ans[i] = 0;
    for (int i = 1; i <= p + 1; i++) {
        if (s[i] == '?') pos = i;
        else {
            if (s[i] == 'L') ans[i] = -1;
            if (s[i] == 'N') ans[i] = 0;
            if (s[i] == 'R') ans[i] = 1;
        }
    }
    if (pos) {
        int sum = ans[p + 1];
        for (int i = 1; i <= p; i++)
            if (i != pos) sum -= ans[i];
        while (sum < -1) sum += 3; while (sum > 1) sum -= 3;
        ans[pos] = sum;
    }
    int x = 0;
    for (int i = p; i >= 1; i--) x *= 3, x += ans[i];
    // cout << '\t' << x << endl;
    printf("%d\n", id[x]);
}

void mian() {
    fflush(stdout), scanf("%d", &n), p = getans();
    init();
    print();
    solve();
}

int main() {
    fflush(stdout), scanf("%d", &T);
    while (T--) mian();
    return 0;
}
