#include <bits/stdc++.h>
using namespace std;
using ll  = long long;
using pii = pair<int,int>;
using pip = pair<ll,pii>;

static constexpr int N = 1005;
bool v[N][N];
int n, m, h, w;
int a[N][N], b[N][N];
ll  s[N][N];
vector<pip> p, ans;

// fast integer reader
template<typename T>
inline T readInt() {
    T x = 0;
    bool neg = false;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') neg = true;
        c = getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return neg ? -x : x;
}

// variadic overload
template<typename T, typename... Ts>
inline void readInt(T& x, Ts&... xs) {
    x = readInt<T>();
    (readInt(xs), ...);
}

// fast integer writer
template<typename T>
inline void writeInt(T x) {
    if (x < 0) {
        putchar('-');
        writeInt(-x);
    } else {
        if (x >= 10) writeInt(x / 10);
        putchar(char('0' + x % 10));
    }
}

int main() {
    readInt(n, m, h, w);

    // build prefix-sum
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            a[i][j] = readInt<int>();
            s[i][j] = s[i-1][j] + s[i][j-1]
                    - s[i-1][j-1] + a[i][j];
        }
    }

    // row-wise sliding min of width w → b[i][j]
    for (int i = 1; i <= n; ++i) {
        deque<int> dq;
        for (int j = 1; j <= m; ++j) {
            while (!dq.empty() && dq.front() <= j - w) 
                dq.pop_front();
            while (!dq.empty() && a[i][dq.back()] >= a[i][j]) 
                dq.pop_back();
            dq.push_back(j);
            b[i][j] = a[i][dq.front()];
        }
    }

    // column-wise sliding min of height h over b → collect p
    for (int j = 1; j <= m; ++j) {
        deque<int> dq;
        for (int i = 1; i <= n; ++i) {
            while (!dq.empty() && dq.front() <= i - h) 
                dq.pop_front();
            while (!dq.empty() && b[dq.back()][j] >= b[i][j]) 
                dq.pop_back();
            dq.push_back(i);
            if (i >= h && j >= w) {
                // removal cost
                ll sum = s[i][j] - s[i-h][j]
                       - s[i][j-w] + s[i-h][j-w];
                ll mn  = b[dq.front()][j];
                ll rem = sum - mn * h * (ll)w;
                p.emplace_back(rem, pii{i-h+1, j-w+1});
            }
        }
    }

    // sort by (cost, row, col)
    sort(p.begin(), p.end());

    // greedily pick non-overlapping
    for (auto const &x : p) {
        auto [rem, pos] = x;
        auto [ri, ci]   = pos;
        if (v[ri][ci]) continue;
        ans.push_back(x);
        // your original marking loop
        for (int di = 1 - min(h, ri); di <= h - 1; ++di)
            for (int dj = 1 - min(w, ci); dj <= w - 1; ++dj)
                v[ri + di][ci + dj] = true;
    }

    // output
    writeInt(ans.size());
    putchar('\n');
    for (auto const &x : ans) {
        auto [rem, pos] = x;
        auto [ri, ci]   = pos;
        writeInt(ri);  putchar(' ');
        writeInt(ci);  putchar(' ');
        writeInt(rem); putchar('\n');
    }
    return 0;
}
