#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, m;
    cin >> t >> m;
    vector<int> mem(m, 0);           // mem[i]=0 if free, else holds block-id
    unordered_map<int, pair<int,int>> blocks;
    int next_id = 1;

    while (t--) {
        string op;
        cin >> op;
        if (op == "alloc") {
            int n; cin >> n;
            bool placed = false;
            // scan for a free segment of length n
            for (int i = 0; i + n <= m; ++i) {
                bool ok = true;
                for (int j = i; j < i + n; ++j) {
                    if (mem[j] != 0) { ok = false; break; }
                }
                if (!ok) continue;
                // allocate
                int id = next_id++;
                for (int j = i; j < i + n; ++j) mem[j] = id;
                blocks[id] = {i, n};
                cout << id << "\n";
                placed = true;
                break;
            }
            if (!placed) {
                cout << "NULL\n";
            }

        } else if (op == "erase") {
            int id; cin >> id;
            auto it = blocks.find(id);
            if (it == blocks.end()) {
                cout << "ILLEGAL_ERASE_ARGUMENT\n";
            } else {
                auto [st, len] = it->second;
                for (int j = st; j < st + len; ++j)
                    mem[j] = 0;
                blocks.erase(it);
            }

        } else if (op == "defragment") {
            vector<int> newmem(m, 0);
            // gather blocks in increasing order of their current start
            vector<pair<int,int>> order; // (old start, id)
            for (auto &b : blocks)
                order.emplace_back(b.second.first, b.first);
            sort(order.begin(), order.end());

            int cur = 0;
            for (auto &[old_st, id] : order) {
                auto [_, len] = blocks[id];
                // move block to new position
                for (int j = 0; j < len; ++j)
                    newmem[cur + j] = id;
                blocks[id].first = cur;  // update start
                cur += len;
            }
            mem.swap(newmem);
        }
    }

    return 0;
}
