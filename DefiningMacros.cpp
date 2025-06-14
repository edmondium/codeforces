#include <bits/stdc++.h>
using namespace std;

struct Macro {
    int mask;    // bit-mask of top-level ops: 1<<0 for '+', 1<<1 for '-', 1<<2 for '*', 1<<3 for '/'
    bool susp;   // true if this macro is already suspicious
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string line;
    getline(cin, line);  // consume end-of-line after n

    unordered_map<string,int> id;     // macro name → index
    vector<string> bodies(n+1);       // bodies[0..n-1] are definitions, bodies[n] is the query
    vector<Macro> macros(n+1);

    // 1) Read the n #define lines
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        istringstream iss(line);
        string token, name, tok, body;

        // skip "#" if present, then skip "define" (or "#define")
        iss >> token;
        if (token == "#")
            iss >> token;  // now token == "define"

        // next token is the macro's name
        iss >> name;

        // collect macro body, stripping all whitespace
        while (iss >> tok)
            body += tok;

        bodies[i] = move(body);
        id[name] = i;
    }

    // 2) Read the final expression (the query)
    {
        getline(cin, line);
        istringstream iss(line);
        string tok, body;
        while (iss >> tok)
            body += tok;
        bodies[n] = move(body);
    }

    // 3) Evaluator: computes (mask, susp) for substring text[a..b)
    function<pair<int,bool>(const string&,int,int)> eval =
    [&](auto const &text, int a, int b) -> pair<int,bool> {
        vector<int> seq;   // sequence: [ operand-mask, op-code, operand-mask, ... ]
        bool susp = false;
        int depth = 0, lastPos = -1;
        string cur;

        for (int j = a; j <= b; j++) {
            char c = (j < b ? text[j] : '\0');
            if (j < b && isalnum(c)) {
                cur.push_back(c);
            } else {
                if (!cur.empty()) {
                    if (depth == 0) {
                        auto it = id.find(cur);
                        if (it != id.end()) {
                            auto &m = macros[it->second];
                            seq.push_back(m.mask);
                            susp |= m.susp;
                        } else {
                            seq.push_back(0);
                        }
                    }
                    cur.clear();
                }
                if (j == b) break;

                c = text[j];
                if (c == '(') {
                    if (depth == 0) lastPos = j + 1;
                    depth++;
                } else if (c == ')') {
                    depth--;
                    if (depth == 0) {
                        auto [innerMask, innerSusp] = eval(text, lastPos, j);
                        seq.push_back(0);   // parentheses act as single operand
                        susp |= innerSusp;
                    }
                } else if (depth == 0) {
                    // record top-level operator
                    if      (c == '+') seq.push_back(0);
                    else if (c == '-') seq.push_back(1);
                    else if (c == '*') seq.push_back(2);
                    else if (c == '/') seq.push_back(3);
                }
            }
        }

        int mask = 0;
        // scan every operator (odd positions in seq)
        for (int k = 1; k + 1 < (int)seq.size(); k += 2) {
            int op = seq[k];
            mask |= (1 << op);
            int L = seq[k-1], R = seq[k+1];
            // detect bad precedence interactions
            if (op == 1 && (R & 3))            // a - (b* or b/)
                susp = true;
            if (op == 2 && ((L & 3) || (R & 3)))// a* (b+ or b-)
                susp = true;
            if (op == 3 && ((L & 3) || R))     // a/(b+ or b-) or a/(0)
                susp = true;
        }
        // if any '+' or '-' appears, drop '*' and '/'
        if (mask & 3) mask &= 3;
        return {mask, susp};
    };

    // 4) Precompute each macro's mask & susp
    for (int i = 0; i <= n; i++) {
        auto [m, s] = eval(bodies[i], 0, bodies[i].size());
        macros[i] = {m, s};
    }

    // 5) Print result for the final expression
    cout << (macros[n].susp ? "Suspicious\n" : "OK\n");
    return 0;
}
