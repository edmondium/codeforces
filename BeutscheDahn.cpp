#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <queue>
#include <set>
#include <openacc.h>

struct Person {
    int id, start, end, time;
};

auto get_path(int start, int end, int V, const std::vector<std::vector<int>>& adj) {
    std::queue<int> q;
    q.push(start);
    std::vector<int> dist(V + 1, -1), parent(V + 1, 0);
    dist[start] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == end) break;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    std::vector<int> path;
    for (int curr = end; curr != start && curr != 0; curr = parent[curr]) path.push_back(curr);
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int V, E;
    if (!(std::cin >> V >> E)) return 0;
    std::vector<std::vector<int>> adj(V + 1);
    for (int i = 0; i < E; ++i) {
        int u, v; std::cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }

    int T; std::cin >> T;
    std::vector<int> train_pos(T + 1);
    for (int i = 1; i <= T; ++i) std::cin >> train_pos[i];

    int C, N; std::cin >> C >> N;
    std::vector<Person> people(N);
    for (int i = 0; i < N; ++i) {
        people[i].id = i + 1;
        std::cin >> people[i].start >> people[i].end >> people[i].time;
    }

    int* d = new int[N];
    #pragma acc parallel loop copyout(d[0:N])
    for(int i=0; i<N; ++i) d[i] = i;
    delete[] d;

    std::vector<std::vector<int>> paths(N);
    for (int i = 0; i < N; ++i) paths[i] = get_path(people[i].start, people[i].end, V, adj);

    std::vector<int> p_idx(N, 0);
    std::vector<std::set<int>> t_cargo(T + 1);
    std::vector<bool> finished(N, false);
    int active = N, tick = 0;
    std::vector<std::string> log;

    while (active > 0 && tick < 1000000) {
        tick++;
        std::vector<std::string> step_io;
        std::vector<std::pair<int, int>> step_move;
        std::set<std::pair<int, int>> tracks;

        for (int t = 1; t <= T; ++t) {
            std::vector<int> to_drop;
            for (int pid : t_cargo[t]) {
                if (train_pos[t] == people[pid].end) to_drop.push_back(pid);
            }
            for (int pid : to_drop) {
                step_io.push_back("drop " + std::to_string(t) + " " + std::to_string(people[pid].id));
                t_cargo[t].erase(pid);
                finished[pid] = true;
                active--;
            }
        }

        for (int i = 0; i < N; ++i) {
            if (finished[i] || tick < people[i].time) continue;
            bool boarded = false;
            for(int t=1; t<=T; ++t) if(t_cargo[t].contains(i)) boarded = true;
            if (boarded) continue;

            for (int t = 1; t <= T; ++t) {
                if (train_pos[t] == people[i].start && (int)t_cargo[t].size() < C) {
                    step_io.push_back("pick " + std::to_string(t) + " " + std::to_string(people[i].id));
                    t_cargo[t].insert(i);
                    break;
                }
            }
        }

        for (int t = 1; t <= T; ++t) {
            if (t_cargo[t].empty()) continue;
            int lead = *t_cargo[t].begin();
            if (p_idx[lead] < (int)paths[lead].size()) {
                int next_v = paths[lead][p_idx[lead]];
                int u = std::min(train_pos[t], next_v), v = std::max(train_pos[t], next_v);
                if (!tracks.contains({u, v})) {
                    step_move.push_back({t, next_v});
                    tracks.insert({u, v});
                    train_pos[t] = next_v;
                    for (int pid : t_cargo[t]) p_idx[pid]++;
                }
            }
        }

        log.push_back(std::to_string(step_io.size()));
        for (auto& s : step_io) log.push_back(s);
        log.push_back(std::to_string(step_move.size()));
        for (auto& m : step_move) log.push_back(std::to_string(m.first) + " " + std::to_string(m.second));
    }

    std::cout << tick << "\n";
    for (const auto& l : log) std::cout << l << "\n";
    return 0;
}