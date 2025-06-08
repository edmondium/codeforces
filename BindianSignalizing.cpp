#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int &value : a) {
        std::cin >> value;
    }
    
    // Identify the maximum hill and its position.
    int globalVal = a.front();
    int pos = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] > globalVal) {
            globalVal = a[i];
            pos = i;
        }
    }
    
    // Rotate the circle so that the global maximal hill is at index 0.
    std::vector<int> b(n + 1);
    for (int i = 0; i < n; ++i) {
        b[i] = a[(pos + i) % n];
    }
    b[n] = b[0]; // explicitly preserve circularity

    // Prepare arrays for "next" pointers (r), "previous" pointers (l), and 
    // for counting equal adjacent hills (s). 
    // Here, l and r are computed to jump through the sequence similarly to 
    // a monotonic stack approach.
    std::vector<int> l(n), r(n + 1), s(n + 1, 0);
    s[n] = 0;
    
    for (int i = n - 1; i >= 0; --i) {
        r[i] = i + 1;
        // Jump over hills lower than b[i]
        while (r[i] < n && b[i] > b[r[i]]) {
            r[i] = r[r[i]];
        }
        // Compress equal-valued hills and count them in s[]
        while (r[i] < n && b[i] == b[r[i]]) {
            s[i] = s[r[i]] + 1;
            r[i] = r[r[i]];
        }
    }
    
    l[0] = 0;
    for (int i = 1; i < n; ++i) {
        l[i] = i - 1;
        while (l[i] > 0 && b[i] >= b[l[i]]) {
            l[i] = l[l[i]];
        }
    }
    
    // Finally, count the number of pairs of hills that are able to see each other.
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += s[i];
        if (b[i] < b[0]) {
            if (l[i] == 0 && r[i] == n)
                ans += 1;
            else
                ans += 2;
        }
    }
    
    std::cout << ans << "\n";
    return 0;
}
