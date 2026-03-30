#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, m;
    cin >> t >> m;
    vector<int> mem(m, 0);
    unordered_map<int, pair<int,int>> blocks;
    int next_id = 1;

    while (t--) {
        string op;
        cin >> op;
        if (op == "alloc") {
            int n; cin >> n;
            atomic<int> pos(-1);
            #pragma omp parallel for
            for (int i = 0; i < m - n + 1; ++i) {
                if (pos.load() != -1) continue;
                bool ok = true;
                for (int j = i; j < i + n; ++j)
                    if (mem[j] != 0) { ok = false; break; }
                if (ok) pos.store(i);
            }
            if (pos.load() == -1) {
                cout << "NULL\n";
            } else {
                int id = next_id++;
                ranges::for_each(views::iota(pos.load(), pos.load() + n),
                    [&](int j){ mem[j] = id; });
                blocks[id] = {pos.load(), n};
                cout << id << "\n";
            }
        } else if (op == "erase") {
            int id; cin >> id;
            if (!blocks.contains(id)) {
                cout << "ILLEGAL_ERASE_ARGUMENT\n";
            } else {
                auto [st, len] = blocks[id];
                ranges::for_each(views::iota(st, st + len),
                    [&](int j){ mem[j] = 0; });
                blocks.erase(id);
            }
        } else if (op == "defragment") {
            vector<int> newmem(m, 0);
            vector<pair<int,int>> order;
            for (auto &b : blocks) order.emplace_back(b.second.first, b.first);
            ranges::sort(order);
            int cur = 0;
            for (auto &[old_st, id] : order) {
                auto [_, len] = blocks[id];
                ranges::for_each(views::iota(0, len),
                    [&](int j){ newmem[cur + j] = id; });
                blocks[id].first = cur;
                cur += len;
            }
            mem.swap(newmem);
        }
    }
}
