#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int T, n, m, q, pre[N];
struct node { int opt, l, r; } a[N];

int L, R;

struct Tree {
    int l, r, Max, Min, flag; 
    multiset<int> st;
} tr[N << 2];
void pushup(int u) {
    tr[u].Max = max(tr[u << 1].Max, tr[u << 1 | 1].Max);
    tr[u].Min = min(tr[u << 1].Min, tr[u << 1 | 1].Min);
}
void pushdown(int u) {
    if (tr[u].flag) {
        tr[u << 1].flag += tr[u].flag, tr[u << 1 | 1].flag += tr[u].flag;
        tr[u << 1].Min += tr[u].flag, tr[u << 1 | 1].Min += tr[u].flag;
        tr[u].flag = 0;
    }
}

void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r, tr[u].flag = 0;
    if (l == r) return tr[u].st.clear(), tr[u].st.insert(0), tr[u].Max = tr[u].Min = 0, void();
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void cover(int u, int l, int r, int d) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].Min += d, tr[u].flag += d, void();
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) cover(u << 1, l, r, d);
    if (r > mid) cover(u << 1 | 1, l, r, d);
    pushup(u);
}
void change(int u, int x, int d, int opt) {
    if (tr[u].l == tr[u].r) {
        if (opt) tr[u].st.insert(d);
        else tr[u].st.erase(tr[u].st.find(d));
        auto it = tr[u].st.end(); it--;
        tr[u].Max = *it;
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (x <= mid) change(u << 1, x, d, opt);
    else change(u << 1 | 1, x, d, opt);
    pushup(u);
}

int querymax(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].Max;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1, res = 0;
    if (l <= mid) res = querymax(u << 1, l, r);
    if (r > mid) res = max(res, querymax(u << 1 | 1, l, r));
    return res;
}
int querymin(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].Min;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1, res = 0x3f3f3f3f;
    if (l <= mid) res = querymin(u << 1, l, r);
    if (r > mid) res = min(res, querymin(u << 1 | 1, l, r));
    return res;
}

void add(int id) {
    if (a[id].opt == 0) cover(1, a[id].l, a[id].r, 1);
    else change(1, a[id].r, a[id].l, 1);
}
void del(int id) {
    if (a[id].opt == 0) cover(1, a[id].l, a[id].r, -1);
    else change(1, a[id].r, a[id].l, 0);
}

int getl(int u, int x) {
    if (tr[u].r <= x && tr[u].Min > 0) return tr[u].l;
    if (tr[u].l == tr[u].r) return tr[u].l + (tr[u].Min == 0);
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (x <= mid) return getl(u << 1, x);
    int rt = getl(u << 1 | 1, x);
    if (rt == mid + 1) return getl(u << 1, x);
    else return rt;
}
int getr(int u, int x) {
    if (tr[u].l >= x && tr[u].Min > 0) return tr[u].r;
    if (tr[u].l == tr[u].r) return tr[u].l - (tr[u].Min == 0);
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (x > mid) return getr(u << 1 | 1, x);
    int lt = getr(u << 1, x);
    if (lt == mid) return getr(u << 1 | 1, x);
    else return lt;
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i].opt, &a[i].l, &a[i].r);
    build(1, 1, n);
    L = 1, R = 0;
    while (R + 1 <= m) {
        add(++R);
        if (a[R].opt == 0) {
            while (1) {
                int l = min(a[R].l, getl(1, a[R].l) ), r = max(a[R].r, getr(1, a[R].r) );
                if (querymax(1, l, r) >= l) del(L++);
                else break;
            }
        } else {
            int l = a[R].l, r = a[R].r;
            while (querymin(1, l, r) > 0) del(L++);
        }
        pre[R] = L;
    }
    scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        puts(l >= pre[r] ? "Yes" : "No");
    }
    for (int i = 1; i <= m; i++) pre[i] = 0;
}

int main() {
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
