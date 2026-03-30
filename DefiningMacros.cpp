#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

struct Macro { int mask; bool susp; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    string line; getline(cin, line);

    unordered_map<string,int> id;
    vector<string> bodies(n+1);
    vector<Macro> macros(n+1);

    for (int i = 0; i < n; i++) {
        getline(cin, line);
        istringstream iss(line);
        string token, name, tok, body;
        iss >> token;
        if (token == "#") iss >> token;
        iss >> name;
        while (iss >> tok) body += tok;
        bodies[i] = move(body);
        id[name] = i;
    }

    getline(cin, line);
    {
        istringstream iss(line);
        string tok, body;
        while (iss >> tok) body += tok;
        bodies[n] = move(body);
    }

    auto eval = [&](auto&& self, const string& text, int a, int b) -> pair<int,bool> {
        vector<int> seq;
        bool susp = false;
        int depth = 0, lastPos = -1;
        string cur;
        for (int j = a; j <= b; j++) {
            char c = (j < b ? text[j] : '\0');
            if (j < b && isalnum(c)) cur.push_back(c);
            else {
                if (!cur.empty()) {
                    if (depth == 0) {
                        auto it = id.find(cur);
                        if (it != id.end()) {
                            auto& m = macros[it->second];
                            seq.push_back(m.mask);
                            susp |= m.susp;
                        } else seq.push_back(0);
                    }
                    cur.clear();
                }
                if (j == b) break;
                c = text[j];
                if (c == '(') { if (depth == 0) lastPos = j+1; depth++; }
                else if (c == ')') {
                    depth--;
                    if (depth == 0) {
                        auto [innerMask, innerSusp] = self(self, text, lastPos, j);
                        seq.push_back(0);
                        susp |= innerSusp;
                    }
                } else if (depth == 0) {
                    if (c == '+') seq.push_back(0);
                    else if (c == '-') seq.push_back(1);
                    else if (c == '*') seq.push_back(2);
                    else if (c == '/') seq.push_back(3);
                }
            }
        }
        int mask = 0;
        for (int k = 1; k+1 < (int)seq.size(); k += 2) {
            int op = seq[k];
            mask |= (1 << op);
            int L = seq[k-1], R = seq[k+1];
            if (op == 1 && (R & 3)) susp = true;
            if (op == 2 && ((L & 3) || (R & 3))) susp = true;
            if (op == 3 && ((L & 3) || R)) susp = true;
        }
        if (mask & 3) mask &= 3;
        return {mask, susp};
    };

    #pragma omp parallel for
    for (int i = 0; i <= n; i++) {
        auto [m, s] = eval(eval, bodies[i], 0, bodies[i].size());
        macros[i] = {m, s};
    }

    cout << (macros[n].susp ? "Suspicious\n" : "OK\n");
}
