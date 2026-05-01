#include <iostream>
#include <vector>
#include <algorithm>
#include <openacc.h>

using namespace std;

struct State { int u, v, turn; };

static int dist[505][505][2];
static State par[505][505][2];
static bool adj[505][505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            dist[i][j][0] = dist[i][j][1] = -1;

    dist[1][n][0] = 0;

    #pragma acc data copyin(adj) copy(dist, par)
    for (int d = 0; d < 2 * n * n; ++d) {
        bool changed = false;
        int turn = d % 2;

        #pragma acc parallel loop collapse(2) copy(changed)
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                if (dist[u][v][turn] == d) {
                    if (turn == 0) {
                        for (int nu = 1; nu <= n; ++nu) {
                            if (adj[u][nu]) {
                                if (dist[nu][v][1] == -1) {
                                    dist[nu][v][1] = d + 1;
                                    par[nu][v][1] = {u, v, 0};
                                    changed = true;
                                }
                            }
                        }
                    } else {
                        for (int nv = 1; nv <= n; ++nv) {
                            if (adj[v][nv] && nv != u) {
                                if (dist[u][nv][0] == -1) {
                                    dist[u][nv][0] = d + 1;
                                    par[u][nv][0] = {u, v, 1};
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!changed || dist[n][1][0] != -1) break;
    }

    if (dist[n][1][0] == -1) {
        cout << -1 << endl;
        return 0;
    }

    cout << dist[n][1][0] / 2 << "\n";
    vector<int> p1, p2;
    for (State curr = {n, 1, 0}; curr.u != 0; curr = par[curr.u][curr.v][curr.turn]) {
        if (curr.turn == 0) {
            p1.push_back(curr.u);
            p2.push_back(curr.v);
        }
    }
    
    reverse(p1.begin(), p1.end());
    reverse(p2.begin(), p2.end());

    auto print = [](const auto& path) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << "\n";
    };

    print(p1);
    print(p2);

    return 0;
}